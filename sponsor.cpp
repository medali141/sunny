#include "sponsor.h"
#include "ui_sponsor.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPixmap>
#include <QPalette>
#include <qDebug>
#include <QSslSocket>
#include "qrcodegen.hpp"  // Inclure la bibliothèque qrcodegen
#include "statistiques.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTextDocument>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QDateTime>
#include <QErrorMessage>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>

#include <QDebug>

Sponsor::Sponsor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sponsor)
{
    ui->setupUi(this);
    
    // Configure table selection behavior
    ui->tabMAT->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabMAT->setSelectionMode(QAbstractItemView::SingleSelection);
    
    // Show all sponsors initially
    ui->tabMAT->setModel(afficher());
    
    QPixmap bkgnd(":/images/rs/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

Sponsor::~Sponsor()
{
    delete ui;
}

// --- Back Button ---
void Sponsor::on_backButton_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    this->close();
}

// --- Add ---
bool Sponsor::ajouter()
{
    QString id = ui->idSponsor->text();
    QString nom = ui->nom->text();
    QString niveau = ui->comboBox->currentText();
    QString prcnt = ui->prcnt->text();

    // --- Input validation ---
    if(id.length() < 6) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir au moins 6 caractères.");
        return false;
    }

    if(nom.isEmpty() || prcnt.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return false;
    }

    bool ok;
    prcnt.toDouble(&ok);
    if(!ok) {
        QMessageBox::warning(this, "Erreur", "Le pourcentage doit être un nombre.");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO SPONSOR (ID_SPONSOR, NOM, NIVEAU, POURCENTAGE) "
                  "VALUES (:id, :nom, :niveau, :prcnt)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":niveau", niveau);
    query.bindValue(":prcnt", prcnt);

    return query.exec();
}

void Sponsor::on_ajoutMat_clicked()
{
    if(ajouter()) {
        QMessageBox::information(this, "Succès", "Sponsor ajouté avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l'ajout du sponsor.");
    }
}

// --- Modify ---
bool Sponsor::modifier()
{
    QString id = ui->idSponsor->text();
    QString nom = ui->nom->text();
    QString niveau = ui->comboBox->currentText();
    QString prcnt = ui->prcnt->text();

    if(id.length() < 6) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir au moins 6 caractères.");
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE SPONSOR SET NOM = :nom, NIVEAU = :niveau, POURCENTAGE = :prcnt WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":niveau", niveau);
    query.bindValue(":prcnt", prcnt);

    return query.exec();
}

void Sponsor::on_modifierMat_clicked()
{
    if(modifier()) {
        QMessageBox::information(this, "Succès", "Sponsor modifié avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification.");
    }
}

// --- Delete ---
bool Sponsor::supprimer()
{
    QString id = ui->idMAT_Delete->text();

    if(id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer l'ID du sponsor à supprimer.");
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM SPONSOR WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id);

    return query.exec();
}

void Sponsor::on_supprimerMat_clicked()
{
    if(supprimer()) {
        QMessageBox::information(this, "Succès", "Sponsor supprimé avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression.");
    }
}

// --- Display / Refresh ---
QSqlQueryModel* Sponsor::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM SPONSOR");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_SPONSOR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NIVEAU"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("POURCENTAGE"));
    return model;
}

void Sponsor::on_afficherMar_clicked()
{
    ui->tabMAT->setModel(afficher());
}

// --- Search ---
QSqlQueryModel* Sponsor::rechercher()
{
    QString id = ui->recherch_id->text();

    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSOR WHERE ID_SPONSOR LIKE :id");
    query.bindValue(":id", "%" + id + "%");
    query.exec();
    model->setQuery(query);

    return model;
}

void Sponsor::on_rechID_clicked()
{
    ui->tabMAT->setModel(rechercher());
}
void Sponsor::on_send_mail_clicked()
{
    QString host = "smtp.gmail.com";
    int port = 587;
    QString id =ui->IDEMAIL->text();
    QSqlQuery query;
    query.prepare("SELECT NOM, NIVEAU, POURCENTAGE FROM SPONSOR WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id); // id = ui->IDEMAIL->text()

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les informations du sponsor.");
        return;
    }

    QString nomSponsor = query.value("NOM").toString();
    QString niveauSponsor = query.value("NIVEAU").toString();
    QString pourcentageSponsor = query.value("POURCENTAGE").toString();
    // Date et heure actuelles = date d’envoi
    QDateTime now = QDateTime::currentDateTime();

    // Format lisible
    QString dateEnvoi = now.toString("dd/MM/yyyy");
    QString heureEnvoi = now.toString("hh:mm");

    // Date d'échéance = +15 jours
    QDateTime echeance = now.addDays(15);
    QString dateEcheance = echeance.toString("dd/MM/yyyy");

    QString sender = "rayanlabidi.rl@gmail.com";
    QString recipient = ui->dest->text();
    QString destName = ui->dest->text().split("@").first();  // Exemple simple : avant @

    QString contenu =
        "Madame, Monsieur,\n\n"
        "Concernant le sponsor : " + nomSponsor + "\n"
                       "Niveau : " + niveauSponsor + "\n"
                          "Pourcentage : " + pourcentageSponsor + "%\n\n"
                               "Le service sponsoring de SunnyDesk souhaite vous informer que, sauf erreur de notre part, "
                               "nous n’avons pas encore reçu le règlement de la facture, émise le " + dateEnvoi + " à " + heureEnvoi + ", \n"
                                           "Cette facture devait être réglée avant le " + dateEcheance + ", échéance aujourd’hui dépassée.\n\n"
                         "Nous vous remercions donc de bien vouloir procéder à la régularisation dans les plus brefs délais. "
                         "Vous trouverez ci-joint une copie de la facture concernée.\n"
                         "Si toutefois le règlement a déjà été effectué, nous vous prions de ne pas tenir compte de ce courrier.\n\n"
                         "Notre équipe sponsoring reste à votre entière disposition pour toute information complémentaire.\n\n"
                         "En vous remerciant pour votre réactivité, nous vous prions d’agréer, Madame, Monsieur, "
                         "l’expression de nos salutations distinguées.\n\n"
                         "SunnyDesk – Service Sponsoring\n"
                         "Tunisie";

    // Validation email
    if (recipient.isEmpty()) {
        QMessageBox::warning(this, "Destinataire vide", "Veuillez saisir une adresse email.");
        return;
    }

    if (contenu.isEmpty()) {
        QMessageBox::warning(this, "Contenu vide", "Veuillez saisir votre message.");
        return;
    }

    // Validation URL dans le contenu
    QRegularExpression urlRegex("(https?://[^\\s]+)");
    QRegularExpressionMatch match = urlRegex.match(contenu);

    QString subject = "Chère  " + destName;
    QString body = contenu;

    QSslSocket socket;
    socket.connectToHost(host, port);

    if (!socket.waitForConnected()) {
        qDebug() << "Failed to connect:" << socket.errorString();
        return;
    }

    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("EHLO localhost\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("STARTTLS\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.startClientEncryption();
    if (!socket.waitForEncrypted()) {
        qDebug() << "Encryption failed:" << socket.errorString();
        return;
    }

    socket.write("AUTH LOGIN\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write(QByteArray(sender.toUtf8()).toBase64() + "\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write(QByteArray("lpdl ksfg hvhr mguv").toBase64() + "\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("MAIL FROM:<" + sender.toUtf8() + ">\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("RCPT TO:<" + recipient.toUtf8() + ">\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("DATA\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("From: " + sender.toUtf8() + "\r\n");
    socket.write("To: " + recipient.toUtf8() + "\r\n");
    socket.write("Subject: " + subject.toUtf8() + "\r\n\r\n");
    socket.write(body.toUtf8() + "\r\n.\r\n");

    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("QUIT\r\n");

    QMessageBox::information(this, "Succès", "Email envoyé.");
     ui->dest->clear();
}
void Sponsor::on_Qrcode_clicked()
{
    // Obtenir la ligne sélectionnée dans le QTableView (tabMAT)
    QItemSelectionModel *select = ui->tabMAT->selectionModel();

    if (!select || !select->hasSelection()) {
        QMessageBox::warning(this, "No Selection", "Please select a sponsor first.");
        return;
    }

    QModelIndexList selectedRows = select->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a sponsor first.");
        return;
    }

    int selectedRow = selectedRows.first().row();

    // Accéder au modèle
    QAbstractItemModel *model = ui->tabMAT->model();
    if (!model) {
        QMessageBox::warning(this, "Error", "No data available.");
        return;
    }

     QString id  = model->data(model->index(selectedRow, 0)).toString(); // Col 1 → ID
    QString nom = model->data(model->index(selectedRow, 1)).toString(); // Col 2 → Nom
    QString niv = model->data(model->index(selectedRow, 2)).toString(); // Col 0 → CIN
    QString pr = model->data(model->index(selectedRow, 3)).toString(); // Col 0 → CIN

    if (id.isEmpty() || nom.isEmpty() || niv.isEmpty() || pr.isEmpty()) {
        QMessageBox::warning(this, "Invalid Data", "Some information is missing.");
        return;
    }

    // Créer le contenu du QR Code
    QString qrData = QString("ID: %1\nNom: %2\nNiveau: %3\nPourcentage: %4").arg(id, nom, niv, pr);

    // Générer le QR Code
    using namespace qrcodegen;
    QrCode qr = QrCode::encodeText(qrData.toUtf8().data(), QrCode::Ecc::MEDIUM);

    int sz = qr.getSize();
    QImage im(sz, sz, QImage::Format_RGB32);
    QRgb black = qRgb(0, 0, 0);
    QRgb white = qRgb(255, 255, 255);

    for (int y = 0; y < sz; ++y) {
        for (int x = 0; x < sz; ++x) {
            im.setPixel(x, y, qr.getModule(x, y) ? black : white);
        }
    }

    // Afficher le QR Code dans label_5
    ui->label_5->setPixmap(
        QPixmap::fromImage(im.scaled(125, 125, Qt::KeepAspectRatio, Qt::FastTransformation))
    );
}

void Sponsor::on_stat_clicked()
{
    Statistiques *statDialog = new Statistiques(this);
    statDialog->exec();
    delete statDialog;
}


void Sponsor::on_pdf_clicked()
{
    // Demander à l'utilisateur où sauvegarder le PDF
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Enregistrer le PDF"),
                                                    QDir::homePath() + "/sponsors_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".pdf",
                                                    tr("Fichiers PDF (*.pdf)"));

    if (fileName.isEmpty()) {
        return;
    }

    // Créer le PDF writer
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setPageMargins(QMarginsF(15, 15, 15, 15));

    QPainter painter(&pdfWriter);

    if (!painter.isActive()) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le PDF.");
        return;
    }

    // Configuration des polices
    QFont titleFont("Arial", 24, QFont::Bold);
    QFont subtitleFont("Arial", 11);
    QFont headerFont("Arial", 11, QFont::Bold);
    QFont normalFont("Arial", 10);

    int yPos = 800;
    int leftMargin = 400;
    int rightMargin = pdfWriter.width() - 400;
    int pageWidth = rightMargin - leftMargin;
    int lineHeight = 550;

    // === TITRE DU DOCUMENT ===
    painter.setFont(titleFont);
    painter.drawText(QRect(leftMargin, yPos, pageWidth, 1000),
                     Qt::AlignCenter,
                     "LISTE DES SPONSORS");
    yPos += 1200;

    // Date de génération
    painter.setFont(subtitleFont);
    QString dateGeneration = "Généré le : " + QDateTime::currentDateTime().toString("dd/MM/yyyy à HH:mm");
    painter.drawText(QRect(leftMargin, yPos, pageWidth, 500),
                     Qt::AlignCenter,
                     dateGeneration);
    yPos += 700;

    // Ligne de séparation épaisse
    painter.setPen(QPen(Qt::black, 3));
    painter.drawLine(leftMargin, yPos, rightMargin, yPos);
    yPos += 800;

    // === RÉCUPÉRER LES DONNÉES ===
    // Compter d'abord le nombre total
    QSqlQuery countQuery;
    countQuery.prepare("SELECT COUNT(*) FROM SPONSOR");
    int totalSponsors = 0;

    if (countQuery.exec() && countQuery.next()) {
        totalSponsors = countQuery.value(0).toInt();
    }

    // Afficher le total
    painter.setFont(headerFont);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawText(leftMargin, yPos, "Nombre total de sponsors : " + QString::number(totalSponsors));
    yPos += 900;

    // === CALCULER LES LARGEURS DES COLONNES ===
    int colWidth1 = pageWidth * 0.20;  // 20% - ID
    int colWidth2 = pageWidth * 0.35;  // 35% - NOM
    int colWidth3 = pageWidth * 0.25;  // 25% - NIVEAU
    int colWidth4 = pageWidth * 0.20;  // 20% - POURCENTAGE

    int col1 = leftMargin;
    int col2 = col1 + colWidth1;
    int col3 = col2 + colWidth2;
    int col4 = col3 + colWidth3;

    // === EN-TÊTES DES COLONNES AVEC FOND ===
    painter.setFont(headerFont);

    // Dessiner le fond gris pour l'en-tête
    painter.fillRect(leftMargin, yPos - 100, pageWidth, 600, QColor(220, 220, 220));

    // Bordures de l'en-tête
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(leftMargin, yPos - 100, pageWidth, 600);

    // Lignes verticales séparatrices
    painter.drawLine(col2, yPos - 100, col2, yPos + 500);
    painter.drawLine(col3, yPos - 100, col3, yPos + 500);
    painter.drawLine(col4, yPos - 100, col4, yPos + 500);

    // Texte des en-têtes (centré verticalement)
    int headerTextY = yPos + 250;
    painter.drawText(QRect(col1 + 50, yPos - 100, colWidth1 - 100, 600),
                     Qt::AlignVCenter | Qt::AlignLeft, "ID SPONSOR");
    painter.drawText(QRect(col2 + 50, yPos - 100, colWidth2 - 100, 600),
                     Qt::AlignVCenter | Qt::AlignLeft, "NOM");
    painter.drawText(QRect(col3 + 50, yPos - 100, colWidth3 - 100, 600),
                     Qt::AlignVCenter | Qt::AlignLeft, "NIVEAU");
    painter.drawText(QRect(col4 + 50, yPos - 100, colWidth4 - 100, 600),
                     Qt::AlignVCenter | Qt::AlignLeft, "POURCENTAGE");

    yPos += 600;

    // === DONNÉES DES SPONSORS ===
    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSOR ORDER BY NOM");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les données : " + query.lastError().text());
        painter.end();
        return;
    }

    painter.setFont(normalFont);
    painter.setPen(QPen(Qt::black, 1));

    int rowCount = 0;
    bool alternateBg = false;

    while (query.next()) {
        rowCount++;

        // Vérifier si on doit passer à une nouvelle page
        if (yPos > pdfWriter.height() - 1500) {
            pdfWriter.newPage();
            yPos = 800;

            // Redessiner les en-têtes sur la nouvelle page
            painter.setFont(headerFont);
            painter.fillRect(leftMargin, yPos - 100, pageWidth, 600, QColor(220, 220, 220));
            painter.setPen(QPen(Qt::black, 2));
            painter.drawRect(leftMargin, yPos - 100, pageWidth, 600);
            painter.drawLine(col2, yPos - 100, col2, yPos + 500);
            painter.drawLine(col3, yPos - 100, col3, yPos + 500);
            painter.drawLine(col4, yPos - 100, col4, yPos + 500);

            painter.drawText(QRect(col1 + 50, yPos - 100, colWidth1 - 100, 600),
                             Qt::AlignVCenter | Qt::AlignLeft, "ID SPONSOR");
            painter.drawText(QRect(col2 + 50, yPos - 100, colWidth2 - 100, 600),
                             Qt::AlignVCenter | Qt::AlignLeft, "NOM");
            painter.drawText(QRect(col3 + 50, yPos - 100, colWidth3 - 100, 600),
                             Qt::AlignVCenter | Qt::AlignLeft, "NIVEAU");
            painter.drawText(QRect(col4 + 50, yPos - 100, colWidth4 - 100, 600),
                             Qt::AlignVCenter | Qt::AlignLeft, "POURCENTAGE");

            yPos += 600;
            painter.setFont(normalFont);
            alternateBg = false;
        }

        // Fond alterné pour les lignes (zebra striping)
        if (alternateBg) {
            painter.fillRect(leftMargin, yPos, pageWidth, lineHeight, QColor(245, 245, 245));
        }
        alternateBg = !alternateBg;

        // Récupérer les données
        QString id = query.value("ID_SPONSOR").toString();
        QString nom = query.value("NOM").toString();
        QString niveau = query.value("NIVEAU").toString();
        QString pourcentage = query.value("POURCENTAGE").toString() + "%";

        // Bordures de la ligne
        painter.setPen(QPen(QColor(200, 200, 200), 1));
        painter.drawRect(leftMargin, yPos, pageWidth, lineHeight);
        painter.drawLine(col2, yPos, col2, yPos + lineHeight);
        painter.drawLine(col3, yPos, col3, yPos + lineHeight);
        painter.drawLine(col4, yPos, col4, yPos + lineHeight);

        // Afficher les données (centrées verticalement)
        painter.setPen(QPen(Qt::black, 1));
        painter.drawText(QRect(col1 + 50, yPos, colWidth1 - 100, lineHeight),
                         Qt::AlignVCenter | Qt::AlignLeft, id);
        painter.drawText(QRect(col2 + 50, yPos, colWidth2 - 100, lineHeight),
                         Qt::AlignVCenter | Qt::AlignLeft, nom);
        painter.drawText(QRect(col3 + 50, yPos, colWidth3 - 100, lineHeight),
                         Qt::AlignVCenter | Qt::AlignLeft, niveau);
        painter.drawText(QRect(col4 + 50, yPos, colWidth4 - 100, lineHeight),
                         Qt::AlignVCenter | Qt::AlignLeft, pourcentage);

        yPos += lineHeight;
    }

    // === PIED DE PAGE ===
    yPos = pdfWriter.height() - 800;

    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(leftMargin, yPos, rightMargin, yPos);
    yPos += 400;

    QFont footerFont("Arial", 9);
    footerFont.setItalic(true);
    painter.setFont(footerFont);
    painter.setPen(QPen(Qt::darkGray, 1));
    painter.drawText(QRect(leftMargin, yPos, pageWidth, 500),
                     Qt::AlignCenter,
                     "SunnyDesk - Gestion des Sponsors");

    // Terminer le document
    painter.end();

    // Message de confirmation
    QMessageBox::information(this, "Succès",
                             "Le PDF a été généré avec succès !\n\n" +
                                 QString::number(totalSponsors) + " sponsor(s) exporté(s).\n\n" +
                                 "Fichier : " + fileName);
}
