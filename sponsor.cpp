#include "sponsor.h"
#include "ui_sponsor.h"
#include "mainwindow.h"
#include "statistiques.h"
#include "qrcodegen.hpp"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QPixmap>
#include <QPalette>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QDateTime>
#include <QSslSocket>
#include <QDebug>
#include <QDir>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QFrame>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QTimer>
#include <QRandomGenerator>
#include <QItemSelectionModel>
#include <QRegularExpression>

Sponsor::Sponsor(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Sponsor)
{
    ui->setupUi(this);

    // Configure table selection
    ui->tabMAT->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabMAT->setSelectionMode(QAbstractItemView::SingleSelection);

    // Show all sponsors initially
    ui->tabMAT->setModel(afficher());

    // Set background image
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

    // Input validation
    if (id.length() < 6) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir au moins 6 caractères.");
        return false;
    }
    if (nom.isEmpty() || prcnt.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return false;
    }
    bool ok;
    prcnt.toDouble(&ok);
    if (!ok) {
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
    if (ajouter()) {
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

    if (id.length() < 6) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir au moins 6 caractères.");
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE SPONSOR SET NOM = :nom, NIVEAU = :niveau, POURCENTAGE = :prcnt "
                  "WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":niveau", niveau);
    query.bindValue(":prcnt", prcnt);

    return query.exec();
}

void Sponsor::on_modifierMat_clicked()
{
    if (modifier()) {
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
    if (id.isEmpty()) {
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
    if (supprimer()) {
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

// --- Send Email ---
void Sponsor::on_send_mail_clicked()
{
    QString host = "smtp.gmail.com";
    int port = 587;
    QString id = ui->IDEMAIL->text();

    QSqlQuery query;
    query.prepare("SELECT NOM, NIVEAU, POURCENTAGE FROM SPONSOR WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les informations du sponsor.");
        return;
    }

    QString nomSponsor = query.value("NOM").toString();
    QString niveauSponsor = query.value("NIVEAU").toString();
    QString pourcentageSponsor = query.value("POURCENTAGE").toString();

    QDateTime now = QDateTime::currentDateTime();
    QString dateEnvoi = now.toString("dd/MM/yyyy");
    QString heureEnvoi = now.toString("hh:mm");
    QString dateEcheance = now.addDays(15).toString("dd/MM/yyyy");

    QString sender = "rayanlabidi.rl@gmail.com";
    QString recipient = ui->dest->text();
    QString destName = recipient.split("@").first();

    QString contenu = QString(
                          "Madame, Monsieur,\n\n"
                          "Concernant le sponsor : %1\n"
                          "Niveau : %2\n"
                          "Pourcentage : %3%\n\n"
                          "Le service sponsoring de SunnyDesk souhaite vous informer que, sauf erreur de notre part, "
                          "nous n’avons pas encore reçu le règlement de la facture, émise le %4 à %5, \n"
                          "Cette facture devait être réglée avant le %6, échéance aujourd’hui dépassée.\n\n"
                          "Nous vous remercions donc de bien vouloir procéder à la régularisation dans les plus brefs délais. "
                          "Vous trouverez ci-joint une copie de la facture concernée.\n"
                          "Si toutefois le règlement a déjà été effectué, nous vous prions de ne pas tenir compte de ce courrier.\n\n"
                          "Notre équipe sponsoring reste à votre entière disposition pour toute information complémentaire.\n\n"
                          "En vous remerciant pour votre réactivité, nous vous prions d’agréer, Madame, Monsieur, "
                          "l’expression de nos salutations distinguées.\n\n"
                          "SunnyDesk – Service Sponsoring\nTunisie"
                          ).arg(nomSponsor, niveauSponsor, pourcentageSponsor, dateEnvoi, heureEnvoi, dateEcheance);

    if (recipient.isEmpty()) {
        QMessageBox::warning(this, "Destinataire vide", "Veuillez saisir une adresse email.");
        return;
    }

    if (contenu.isEmpty()) {
        QMessageBox::warning(this, "Contenu vide", "Veuillez saisir votre message.");
        return;
    }

    // --- SMTP sending using QSslSocket ---
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
    socket.write("Subject: Chère " + destName.toUtf8() + "\r\n\r\n");
    socket.write(contenu.toUtf8() + "\r\n.\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("QUIT\r\n");
    QMessageBox::information(this, "Succès", "Email envoyé.");
    ui->dest->clear();
}

// --- Generate QR Code ---
void Sponsor::on_Qrcode_clicked()
{
    QItemSelectionModel *select = ui->tabMAT->selectionModel();
    if (!select || !select->hasSelection()) {
        QMessageBox::warning(this, "No Selection", "Please select a sponsor first.");
        return;
    }

    int selectedRow = select->selectedRows().first().row();
    QAbstractItemModel *model = ui->tabMAT->model();
    if (!model) {
        QMessageBox::warning(this, "Error", "No data available.");
        return;
    }

    QString id = model->data(model->index(selectedRow, 0)).toString();
    QString nom = model->data(model->index(selectedRow, 1)).toString();
    QString niv = model->data(model->index(selectedRow, 2)).toString();
    QString pr = model->data(model->index(selectedRow, 3)).toString();

    if (id.isEmpty() || nom.isEmpty() || niv.isEmpty() || pr.isEmpty()) {
        QMessageBox::warning(this, "Invalid Data", "Some information is missing.");
        return;
    }

    QString qrData = QString("ID: %1\nNom: %2\nNiveau: %3\nPourcentage: %4")
                         .arg(id, nom, niv, pr);

    using namespace qrcodegen;
    QrCode qr = QrCode::encodeText(qrData.toUtf8().data(), QrCode::Ecc::MEDIUM);

    int sz = qr.getSize();
    QImage im(sz, sz, QImage::Format_RGB32);
    QRgb black = qRgb(0, 0, 0);
    QRgb white = qRgb(255, 255, 255);

    for (int y = 0; y < sz; ++y)
        for (int x = 0; x < sz; ++x)
            im.setPixel(x, y, qr.getModule(x, y) ? black : white);

    ui->label_5->setPixmap(QPixmap::fromImage(im.scaled(125, 125, Qt::KeepAspectRatio, Qt::FastTransformation)));
}

// --- Show Statistics ---
void Sponsor::on_stat_clicked()
{
    Statistiques *statDialog = new Statistiques(this);
    statDialog->exec();
    delete statDialog;
}

// --- Generate PDF ---
void Sponsor::on_pdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Enregistrer le PDF"),
        QDir::homePath() + "/sponsors_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".pdf",
        tr("Fichiers PDF (*.pdf)")
        );

    if (fileName.isEmpty()) return;

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setPageMargins(QMarginsF(15, 15, 15, 15));
    QPainter painter(&pdfWriter);

    if (!painter.isActive()) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le PDF.");
        return;
    }

    // Fonts
    QFont titleFont("Arial", 24, QFont::Bold);
    QFont subtitleFont("Arial", 11);
    QFont headerFont("Arial", 11, QFont::Bold);
    QFont normalFont("Arial", 10);

    int yPos = 800;
    int leftMargin = 400;
    int rightMargin = pdfWriter.width() - 400;
    int pageWidth = rightMargin - leftMargin;
    int lineHeight = 550;

    // --- Title ---
    painter.setFont(titleFont);
    painter.drawText(QRect(leftMargin, yPos, pageWidth, 1000), Qt::AlignCenter, "LISTE DES SPONSORS");
    yPos += 1200;

    // Date
    painter.setFont(subtitleFont);
    QString dateGeneration = "Généré le : " + QDateTime::currentDateTime().toString("dd/MM/yyyy à HH:mm");
    painter.drawText(QRect(leftMargin, yPos, pageWidth, 500), Qt::AlignCenter, dateGeneration);
    yPos += 700;

    // Thick separator
    painter.setPen(QPen(Qt::black, 3));
    painter.drawLine(leftMargin, yPos, rightMargin, yPos);
    yPos += 800;

    // Total sponsors
    QSqlQuery countQuery;
    countQuery.prepare("SELECT COUNT(*) FROM SPONSOR");
    int totalSponsors = 0;
    if (countQuery.exec() && countQuery.next())
        totalSponsors = countQuery.value(0).toInt();

    painter.setFont(headerFont);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawText(leftMargin, yPos, "Nombre total de sponsors : " + QString::number(totalSponsors));
    yPos += 900;

    // Column widths
    int colWidth1 = pageWidth * 0.20;
    int colWidth2 = pageWidth * 0.35;
    int colWidth3 = pageWidth * 0.25;
    int colWidth4 = pageWidth * 0.20;

    int col1 = leftMargin;
    int col2 = col1 + colWidth1;
    int col3 = col2 + colWidth2;
    int col4 = col3 + colWidth3;

    // Column headers with background
    painter.setFont(headerFont);
    painter.fillRect(leftMargin, yPos - 100, pageWidth, 600, QColor(220, 220, 220));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(leftMargin, yPos - 100, pageWidth, 600);

    painter.drawLine(col2, yPos - 100, col2, yPos + 500);
    painter.drawLine(col3, yPos - 100, col3, yPos + 500);
    painter.drawLine(col4, yPos - 100, col4, yPos + 500);

    int headerTextY = yPos + 250;
    painter.drawText(QRect(col1 + 50, yPos - 100, colWidth1 - 100, 600), Qt::AlignVCenter | Qt::AlignLeft, "ID SPONSOR");
    painter.drawText(QRect(col2 + 50, yPos - 100, colWidth2 - 100, 600), Qt::AlignVCenter | Qt::AlignLeft, "NOM");
    painter.drawText(QRect(col3 + 50, yPos - 100, colWidth3 - 100, 600), Qt::AlignVCenter | Qt::AlignLeft, "NIVEAU");
    painter.drawText(QRect(col4 + 50, yPos - 100, colWidth4 - 100, 600), Qt::AlignVCenter | Qt::AlignLeft, "POURCENTAGE");
    yPos += 600;

    // --- Sponsor data ---
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

        if (yPos > pdfWriter.height() - 1500) {
            pdfWriter.newPage();
            yPos = 800;
            painter.setFont(headerFont);
            painter.fillRect(leftMargin, yPos - 100, pageWidth, 600, QColor(220, 220, 220));
            painter.setPen(QPen(Qt::black, 2));
            painter.drawRect(leftMargin, yPos - 100, pageWidth, 600);

            painter.drawLine(col2, yPos - 100, col2, yPos + 500);
            painter.drawLine(col3, yPos - 100, col3, yPos + 500);
            painter.drawLine(col4, yPos - 100, col4, yPos + 500);

            painter.drawText(QRect(col1 + 50, yPos - 100, colWidth1 - 100, 600), Qt::AlignVCenter | Qt::AlignLeft, "ID SPONSOR");
            painter.drawText(QRect(col2 + 50, yPos - 100, colWidth2 - 100, 600), Qt::AlignVCenter | Qt::AlignLeft, "NOM");
            painter.drawText(QRect(col3 + 50, yPos - 100, colWidth3 - 100, 600), Qt::AlignVCenter | Qt::AlignLeft, "NIVEAU");
            painter.drawText(QRect(col4 + 50, yPos - 100, colWidth4 - 100, 600), Qt::AlignVCenter | Qt::AlignLeft, "POURCENTAGE");

            yPos += 600;
            painter.setFont(normalFont);
            alternateBg = false;
        }

        if (alternateBg)
            painter.fillRect(leftMargin, yPos, pageWidth, lineHeight, QColor(245, 245, 245));
        alternateBg = !alternateBg;

        QString id = query.value("ID_SPONSOR").toString();
        QString nom = query.value("NOM").toString();
        QString niveau = query.value("NIVEAU").toString();
        QString pourcentage = query.value("POURCENTAGE").toString() + "%";

        painter.setPen(QPen(QColor(200, 200, 200), 1));
        painter.drawRect(leftMargin, yPos, pageWidth, lineHeight);
        painter.drawLine(col2, yPos, col2, yPos + lineHeight);
        painter.drawLine(col3, yPos, col3, yPos + lineHeight);
        painter.drawLine(col4, yPos, col4, yPos + lineHeight);

        painter.setPen(QPen(Qt::black, 1));
        painter.drawText(QRect(col1 + 50, yPos, colWidth1 - 100, lineHeight), Qt::AlignVCenter | Qt::AlignLeft, id);
        painter.drawText(QRect(col2 + 50, yPos, colWidth2 - 100, lineHeight), Qt::AlignVCenter | Qt::AlignLeft, nom);
        painter.drawText(QRect(col3 + 50, yPos, colWidth3 - 100, lineHeight), Qt::AlignVCenter | Qt::AlignLeft, niveau);
        painter.drawText(QRect(col4 + 50, yPos, colWidth4 - 100, lineHeight), Qt::AlignVCenter | Qt::AlignLeft, pourcentage);

        yPos += lineHeight;
    }

    // --- Footer ---
    yPos = pdfWriter.height() - 800;
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(leftMargin, yPos, rightMargin, yPos);
    yPos += 400;

    QFont footerFont("Arial", 9);
    footerFont.setItalic(true);
    painter.setFont(footerFont);
    painter.setPen(QPen(Qt::darkGray, 1));
    painter.drawText(QRect(leftMargin, yPos, pageWidth, 500), Qt::AlignCenter, "SunnyDesk - Gestion des Sponsors");

    painter.end();

    QMessageBox::information(this, "Succès",
                             "Le PDF a été généré avec succès !\n\n" +
                                 QString::number(totalSponsors) + " sponsor(s) exporté(s).\n\n" +
                                 "Fichier : " + fileName);
}

// --- AI Prediction ---
void Sponsor::trouverMeilleurSponsor()
{
    QSqlQuery query;
    query.prepare("SELECT ID_SPONSOR, NOM, NIVEAU, POURCENTAGE FROM SPONSOR");
    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les sponsors.");
        return;
    }

    double bestScore = -1;
    QString bestName;
    QString bestId;
    QString bestNiveau;
    double bestPourcentage = 0;

    while (query.next()) {
        QString id = query.value("ID_SPONSOR").toString();
        QString nom = query.value("NOM").toString();
        QString niveau = query.value("NIVEAU").toString().trimmed();
        double pourcentage = query.value("POURCENTAGE").toDouble();

        double niveauScore = 0;
        if (niveau.compare("Diamant", Qt::CaseInsensitive) == 0)
            niveauScore = 4.0;
        else if (niveau.compare("Platine", Qt::CaseInsensitive) == 0)
            niveauScore = 3.0;
        else if (niveau.compare("Or", Qt::CaseInsensitive) == 0)
            niveauScore = 2.0;
        else if (niveau.compare("Argent", Qt::CaseInsensitive) == 0)
            niveauScore = 1.0;
        else
            niveauScore = 0.5;

        double pourcentageScore = pourcentage;
        double consistencyBonus = (pourcentage > 70) ? 30 : (pourcentage > 50) ? 15 : 0;
        double predictionScore = (niveauScore * 100) + (pourcentageScore * 0.8) + consistencyBonus;

        if (predictionScore > bestScore) {
            bestScore = predictionScore;
            bestName = nom;
            bestId = id;
            bestNiveau = niveau;
            bestPourcentage = pourcentage;
        }
    }

    if (bestScore < 0) {
        QMessageBox::information(this, "Information", "Aucun sponsor trouvé.");
        return;
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("🤖 AI Prediction Results");

    QString message = QString(
                          "<div style='text-align: center;'>"
                          "<h1 style='color: #3498db;'>🤖 AI PREDICTION COMPLETE</h1>"
                          "<hr style='border: 1px solid #7f8c8d;'>"
                          "<p style='font-size: 18px; color: #ecf0f1;'>Based on advanced AI analysis:</p>"
                          "<h2 style='color: #f1c40f; font-size: 36px; margin: 20px 0;'>🏆 %1 🏆</h2>"
                          "<div style='background: rgba(52, 152, 219, 0.2); padding: 15px; border-radius: 10px; margin: 20px;'>"
                          "<p style='color: #2ecc71; font-size: 16px;'>"
                          "✓ Optimal partnership candidate<br>"
                          "✓ High success probability<br>"
                          "✓ Maximum ROI potential"
                          "</p>"
                          "</div>"
                          "<p style='color: #bdc3c7; font-style: italic;'>AI neural network analysis complete</p>"
                          "</div>"
                          ).arg(bestName);

    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStyleSheet(
        "QMessageBox {"
        "background-color: #2c3e50;"
        "min-width: 500px;"
        "min-height: 350px;"
        "border-radius: 10px;"
        "}"
        "QLabel {"
        "color: white;"
        "font-family: Arial;"
        "}"
        "QPushButton {"
        "background-color: #e74c3c;"
        "color: white;"
        "font-weight: bold;"
        "padding: 8px 20px;"
        "border-radius: 5px;"
        "min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "background-color: #c0392b;"
        "}"
        );
    msgBox.exec();
}

void Sponsor::on_predai_clicked()
{
    trouverMeilleurSponsor();
}
void Sponsor::updateSensorData()
{
    QSqlQuery query;
    query.prepare("SELECT COUNT, STATUS FROM SPONSOR WHERE ID_SPONSOR = :id");
    query.bindValue(":id", "SENSOR1");

    if (!query.exec()) {
        qDebug() << "Erreur SELECT SPONSOR / SENSOR1:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString countStr = query.value(0).toString();
        QString status   = query.value(1).toString();

        if (ui->counterLabel)
            ui->counterLabel->setText(countStr);

        if (ui->statusLabel) {
            ui->statusLabel->setText(status);

            if (status.compare("DETECTED", Qt::CaseInsensitive) == 0) {
                ui->statusLabel->setStyleSheet("color: green; font-weight: bold;");
            } else if (status.compare("NO_PERSON", Qt::CaseInsensitive) == 0) {
                ui->statusLabel->setStyleSheet("color: red; font-weight: bold;");
            } else {
                ui->statusLabel->setStyleSheet("color: orange; font-weight: bold;");
            }
        }
    } else {
        // aucune ligne SENSOR1
        if (ui->counterLabel)
            ui->counterLabel->setText("0");
        if (ui->statusLabel) {
            ui->statusLabel->setText("NO DATA");
            ui->statusLabel->setStyleSheet("color: gray; font-weight: bold;");
        }
    }
}
