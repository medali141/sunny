import serial
import time
import logging
import oracledb
import json

# Active le mode thick avec Oracle Instant Client
oracledb.init_oracle_client(
    lib_dir=r"C:\Users\Rayen\Downloads\instantclient-basic-windows.x64-19.29.0.0.0dbru\instantclient_19_29"
)

# --- CONFIG ---
SERIAL_PORT = 'COM5'
BAUD_RATE = 9600

DB_USER = 'Rayensql'
DB_PASSWORD = 'esprit25'
DB_DSN = 'localhost:1521/xe'

# Ligne SPONSOR qui représente le capteur
ID_SPONSOR_FIXE = 'SENSOR1'
# ---------------

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)


def connect_db():
    try:
        conn = oracledb.connect(
            user=DB_USER,
            password=DB_PASSWORD,
            dsn=DB_DSN
        )
        logging.info("Connecté à Oracle")
        return conn
    except oracledb.Error as e:
        logging.error(f"Erreur connexion Oracle: {e}")
        return None


def connect_serial():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        logging.info(f"Connecté au port série {SERIAL_PORT}")
        return ser
    except serial.SerialException as e:
        logging.error(f"Erreur connexion série: {e}")
        return None


def update_sponsor(cursor, connection, id_sponsor, count, status):
    sql = """
        UPDATE SPONSOR
        SET COUNT = :count,
            STATUS = :status
        WHERE ID_SPONSOR = :id_sponsor
    """
    try:
        # COUNT est VARCHAR2 en base, on envoie du texte
        cursor.execute(sql, [str(count), status, id_sponsor])

        if cursor.rowcount == 0:
            logging.warning(f"Aucune ligne SPONSOR avec ID_SPONSOR={id_sponsor}")

        connection.commit()
        logging.info(f"MAJ SPONSOR {id_sponsor}: COUNT={count}, STATUS={status}")
    except oracledb.Error as e:
        logging.error(f"Échec UPDATE: {e}")
        try:
            connection.rollback()
        except:
            pass


def main():
    db_conn = None
    ser = None
    cursor = None

    while True:
        # Connexion DB si nécessaire
        if db_conn is None:
            db_conn = connect_db()
            if db_conn:
                cursor = db_conn.cursor()
            else:
                logging.warning("Nouvel essai DB dans 5 secondes...")
                time.sleep(5)
                continue

        # Connexion série si nécessaire
        if ser is None:
            ser = connect_serial()
            if ser is None:
                logging.warning("Nouvel essai série dans 5 secondes...")
                time.sleep(5)
                continue

        try:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8', errors='ignore').strip()
                if not line:
                    continue

                logging.info(f"Reçu: {line}")

                status = None
                count = None

                # 1) Si c'est du JSON (cas actuel de ton Arduino)
                if line.startswith('{'):
                    try:
                        data = json.loads(line)
                        # On récupère les champs JSON
                        status = str(data.get("status", "")).upper()
                        count = int(data.get("count", 0))
                    except Exception as e:
                        logging.warning(f"JSON invalide: {e} - ligne: {line}")
                        continue
                else:
                    # 2) Ancien format "STATUS,COUNT" (on garde en fallback)
                    try:
                        status_str, count_str = line.split(',', 1)
                        status = status_str.strip().upper()
                        count = int(count_str.strip())
                    except ValueError:
                        logging.warning(
                            f"Format invalide (attendu JSON ou STATUS,COUNT): {line}"
                        )
                        continue

                # Vérification finale
                if status is None or count is None:
                    logging.warning(f"Données inexploitables: {line}")
                    continue

                update_sponsor(cursor, db_conn, ID_SPONSOR_FIXE, count, status)

        except serial.SerialException:
            logging.error("Connexion série perdue")
            if ser:
                ser.close()
            ser = None

        except oracledb.Error:
            logging.error("Connexion DB perdue")
            if db_conn:
                try:
                    db_conn.close()
                except:
                    pass
            db_conn = None

        except Exception as e:
            logging.error(f"Erreur inattendue: {e}")
            time.sleep(1)


if __name__ == "__main__":
    main()
