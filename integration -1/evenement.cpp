#include "evenement.h"
#include <QDebug>
#include <QDate>

Evenement::Evenement()
{
    IDEVENT = 0;
    NOMEVENT = "";
    DATEVENT = QDate::currentDate();
    HEURE = "";
    RESPONSABLE = "";
    STATUT = "";
    REMARQUE = "";
}

Evenement::Evenement(int idevent, const QString &nomevent, const QDate &datevent,
                     const QString &heure, const QString &responsable,
                     const QString &statut, const QString &remarque)
{
    IDEVENT = idevent;
    NOMEVENT = nomevent;
    DATEVENT = datevent;
    HEURE = heure;
    RESPONSABLE = responsable;
    STATUT = statut;
    REMARQUE = remarque;
}

bool Evenement::AjouterEvenement()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EVENEMENT (NOMEVENT, DATEVENT, HEURE, RESPONSABLE, STATUT, REMARQUE) "
                  "VALUES (:NOMEVENT, :DATEVENT, :HEURE, :RESPONSABLE, :STATUT, :REMARQUE)");
    query.bindValue(":NOMEVENT", NOMEVENT);
    query.bindValue(":DATEVENT", DATEVENT);
    query.bindValue(":HEURE", HEURE);
    query.bindValue(":RESPONSABLE", RESPONSABLE);
    query.bindValue(":STATUT", STATUT);
    query.bindValue(":REMARQUE", REMARQUE);

    if (!query.exec()) {
        qDebug() << "Erreur ajout:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel *Evenement::AfficherEvenements()
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    modal->setQuery("SELECT IDEVENT, NOMEVENT, TO_CHAR(DATEVENT, 'DD/MM/YYYY') as DATEVENT, "
                    "HEURE, RESPONSABLE, STATUT, REMARQUE FROM EVENEMENT ORDER BY IDEVENT DESC");

    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom Événement"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure"));
    modal->setHeaderData(4, Qt::Horizontal, QObject::tr("Responsable"));
    modal->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));
    modal->setHeaderData(6, Qt::Horizontal, QObject::tr("Remarque"));

    if (modal->lastError().isValid()) {
        qDebug() << "Erreur affichage:" << modal->lastError().text();
    }
    return modal;
}

bool Evenement::ModifierEvenement()
{
    QSqlQuery query;
    query.prepare("UPDATE EVENEMENT SET NOMEVENT = :NOMEVENT, DATEVENT = :DATEVENT, "
                  "HEURE = :HEURE, RESPONSABLE = :RESPONSABLE, "
                  "STATUT = :STATUT, REMARQUE = :REMARQUE "
                  "WHERE IDEVENT = :IDEVENT");
    query.bindValue(":NOMEVENT", NOMEVENT);
    query.bindValue(":DATEVENT", DATEVENT);
    query.bindValue(":HEURE", HEURE);
    query.bindValue(":RESPONSABLE", RESPONSABLE);
    query.bindValue(":STATUT", STATUT);
    query.bindValue(":REMARQUE", REMARQUE);
    query.bindValue(":IDEVENT", IDEVENT);

    if (!query.exec()) {
        qDebug() << "Erreur modification:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Evenement::SupprimerEvenement(const QString &IDEVENT)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EVENEMENT WHERE IDEVENT = :IDEVENT");
    query.bindValue(":IDEVENT", IDEVENT);

    if (!query.exec()) {
        qDebug() << "Erreur suppression:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Evenement::RechercherEvenements(const QString &searchText)
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT IDEVENT, NOMEVENT, TO_CHAR(DATEVENT, 'DD/MM/YYYY') as DATEVENT, "
                  "HEURE, RESPONSABLE, STATUT, REMARQUE FROM EVENEMENT "
                  "WHERE UPPER(NOMEVENT) LIKE UPPER(:search) "
                  "OR UPPER(RESPONSABLE) LIKE UPPER(:search) "
                  "OR UPPER(STATUT) LIKE UPPER(:search) "
                  "OR UPPER(REMARQUE) LIKE UPPER(:search) "
                  "OR TO_CHAR(DATEVENT, 'DD/MM/YYYY') LIKE :search "
                  "OR UPPER(HEURE) LIKE UPPER(:search) "
                  "ORDER BY IDEVENT DESC");

    query.bindValue(":search", "%" + searchText + "%");
    query.exec();
    modal->setQuery(std::move(query));

    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom Événement"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure"));
    modal->setHeaderData(4, Qt::Horizontal, QObject::tr("Responsable"));
    modal->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));
    modal->setHeaderData(6, Qt::Horizontal, QObject::tr("Remarque"));

    if (modal->lastError().isValid()) {
        qDebug() << "Erreur recherche:" << modal->lastError().text();
    }
    return modal;
}

QMap<int, int> Evenement::getStatistiquesParMois(int annee)
{
    QMap<int, int> stats;

    // Initialiser tous les mois à 0
    for (int i = 1; i <= 12; i++) {
        stats[i] = 0;
    }

    // Si annee = 0, utiliser l'année courante
    if (annee == 0) {
        annee = QDate::currentDate().year();
    }

    QSqlQuery query;
    query.prepare("SELECT EXTRACT(MONTH FROM DATEVENT) as MOIS, COUNT(*) as NOMBRE "
                  "FROM EVENEMENT "
                  "WHERE EXTRACT(YEAR FROM DATEVENT) = :annee "
                  "GROUP BY EXTRACT(MONTH FROM DATEVENT) "
                  "ORDER BY MOIS");
    query.bindValue(":annee", annee);

    if (query.exec()) {
        while (query.next()) {
            int mois = query.value(0).toInt();
            int count = query.value(1).toInt();
            stats[mois] = count;
        }
        qDebug() << "Statistiques par mois chargées pour l'année" << annee;
    } else {
        qDebug() << "Erreur stats par mois:" << query.lastError().text();
    }

    return stats;
}
