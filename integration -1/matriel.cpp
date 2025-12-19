#include "matriel.h"
#include "ui_matriel.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPixmap>
#include <QPalette>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QFileDialog>
#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QChart>
#include <QtCharts/QLegend>
#include <QVBoxLayout>
#include <QDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QPushButton>
#include <QShowEvent>
#include <QTimer>



Matriel::Matriel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Matriel)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/images/rs/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    connect(ui->btnMaintenance, &QPushButton::clicked, this, &Matriel::alerteMaintenance);



    // Display all matriels initially
    ui->tabMAT->setModel(afficher());
    //alerteStockFaible(5);
}

Matriel::~Matriel()
{
    delete ui;
}

// --- Back button ---
void Matriel::on_backButton_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    this->close();
}

// --- Add ---
bool Matriel::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO MATRIEL (ID_MAT, NOMMAT, QUANTITE, DISPONIBILITE, DATE_DERNIER_ENTRETIEN, ENTRETIEN_FREQUENCE, NB_UTILISATIONS, NB_UTILISATIONSM) "
                  "VALUES (:id_mat, :nommat, :quantite, :disponibilite, :date_dernier_entretien, :entretien_freq, :nb_utilisations, :nb_utilisationsm)");
    query.bindValue(":id_mat", ui->idMat->text());
    query.bindValue(":nommat", ui->nomMat->text());
    query.bindValue(":quantite", ui->Quantite->text());
    query.bindValue(":disponibilite", ui->Dispo->text());
    query.bindValue(":date_dernier_entretien", ui->dateDernierEntretien->date());
    query.bindValue(":entretien_freq", ui->entretienFrequence->text().toInt());
    query.bindValue(":nb_utilisations", ui->nbUtilisations->text().toInt());
    query.bindValue(":nb_utilisationsm", ui->nbUtilisationSM->text().toInt());

    return query.exec();
}

void Matriel::on_ajoutMat_clicked()
{
    QString id = ui->idMat->text().trimmed();
    QString nom = ui->nomMat->text().trimmed();
    QString quant = ui->Quantite->text().trimmed();
    QString dispo = ui->Dispo->text().trimmed();

    // --- Validation ---
    if (id.isEmpty() || nom.isEmpty() || quant.isEmpty() || dispo.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis !");
        return;
    }
     dispo = ui->Dispo->text().trimmed().toLower(); // convertit en minuscule

    if (dispo != "oui" && dispo != "non") {
        QMessageBox::warning(this, "Erreur", "La disponibilité doit être 'oui' ou 'non'.");
        return;
    }

    bool ok;
    int q = quant.toInt(&ok);
    if (!ok || q < 0) {
        QMessageBox::warning(this, "Erreur", "Quantité invalide !");
        return;
    }

    if (ajouter()) {
        QMessageBox::information(this, "Succès", "Matriel ajouté avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l'ajout du matriel.");
    }
}

// --- Modify ---
bool Matriel::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE MATRIEL SET NOMMAT=:nommat, QUANTITE=:quantite, DISPONIBILITE=:disponibilite, "
                  "DATE_DERNIER_ENTRETIEN=:date_dernier_entretien, ENTRETIEN_FREQUENCE=:entretien_freq, "
                  "NB_UTILISATIONS=:nb_utilisations, NB_UTILISATIONSM=:nb_utilisationsm "
                  "WHERE ID_MAT=:id_mat");
    query.bindValue(":id_mat", ui->idMat->text());
    query.bindValue(":nommat", ui->nomMat->text());
    query.bindValue(":quantite", ui->Quantite->text());
    query.bindValue(":disponibilite", ui->Dispo->text());
    query.bindValue(":date_dernier_entretien", ui->dateDernierEntretien->date());
    query.bindValue(":entretien_freq", ui->entretienFrequence->text().toInt());
    query.bindValue(":nb_utilisations", ui->nbUtilisations->text().toInt());
    query.bindValue(":nb_utilisationsm", ui->nbUtilisationSM->text().toInt());

    return query.exec();
}

void Matriel::on_modifierMat_clicked()
{
    QString id = ui->idMat->text().trimmed();
    QString nom = ui->nomMat->text().trimmed();
    QString quant = ui->Quantite->text().trimmed();
    QString dispo = ui->Dispo->text().trimmed();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "ID est obligatoire pour la modification !");
        return;
    }

    if (nom.isEmpty() && quant.isEmpty() && dispo.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Au moins un champ doit être modifié !");
        return;
    }

    bool ok;
    if (!quant.isEmpty()) {
        int q = quant.toInt(&ok);
        if (!ok || q < 0) {
            QMessageBox::warning(this, "Erreur", "Quantité invalide !");
            return;
        }
    }

    if (modifier()) {
        QMessageBox::information(this, "Succès", "Matriel modifié avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification.");
    }
}

// --- Delete ---
bool Matriel::supprimer()
{
    QSqlQuery query;
    query.prepare("DELETE FROM MATRIEL WHERE ID_MAT = :id_mat");
    query.bindValue(":id_mat", ui->idMAT_Delete->text());
    return query.exec();
}

void Matriel::on_supprimerMat_clicked()
{
    QString id = ui->idMAT_Delete->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID à supprimer !");
        return;
    }

    if (supprimer()) {
        QMessageBox::information(this, "Succès", "Matriel supprimé avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression.");
    }
}

// --- Display ---
QSqlQueryModel* Matriel::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_MAT, NOMMAT, QUANTITE, DISPONIBILITE, DATE_DERNIER_ENTRETIEN, ENTRETIEN_FREQUENCE, NB_UTILISATIONS, NB_UTILISATIONSM FROM MATRIEL");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMMAT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DISPONIBILITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DERNIER_ENTRETIEN"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ENTRETIEN_FREQUENCE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NB_UTILISATIONS"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("NB_UTILISATIONSM"));

    return model;
}


// --- Sort by quantity ---
QSqlQueryModel* Matriel::trierParqt()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM MATRIEL ORDER BY QUANTITE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMMAT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DISPONIBILITE"));
    return model;
}

void Matriel::on_Rtri_clicked()
{
    ui->tabMAT->setModel(trierParqt());
}

// --- Sort by name ---
QSqlQueryModel* Matriel::trierNOMMAT()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM MATRIEL ORDER BY NOMMAT ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMMAT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DISPONIBILITE"));
    return model;
}

void Matriel::on_Rtri_2_clicked()
{
    ui->tabMAT->setModel(trierNOMMAT());
}

// --- Search ---
QSqlQueryModel* Matriel::rechercher()
{
    QString id = ui->recherch_id->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID pour la recherche !");
        return afficher(); // afficher tout si vide
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM MATRIEL WHERE ID_MAT LIKE :id_mat");
    query.bindValue(":id_mat", "%" + id + "%");
    query.exec();
    model->setQuery(query);
    return model;
}

void Matriel::on_rechID_clicked()
{
    ui->tabMAT->setModel(rechercher());
}


void Matriel::on_exportPDFButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exporter Matériel en PDF",
        "materiel.pdf",
        "PDF (*.pdf)"
        );

    if (fileName.isEmpty()) return;
    if (!fileName.endsWith(".pdf"))
        fileName += ".pdf";

    // ---- Build HTML ----
    QString html;
    html += "<html><head><meta charset='UTF-8'><style>";

    // ****** FIX: text wrap + narrower table + bigger cells *******
    html += "body { font-family: Arial; margin: 20px; font-size:14px; }";
    html += "h1 { text-align:center; color:#2c3e50; "
            "border-bottom:3px solid #2980b9; padding-bottom:10px; font-size:26px; }";
    html += "body, table, th, td { color:black; }";


    // FIXED TABLE (no hidden text)
    html += "table { width:95%; border-collapse:collapse; margin-top:20px; table-layout:auto; }";
    html += "th { background:#2980b9; color:black; padding:10px; font-size:15px; }";
    html += "td { padding:10px; border-bottom:1px solid #ddd; word-wrap:break-word; "
            "white-space:normal; max-width:200px; font-size:14px; }";
    html += "tr:nth-child(even) { background:#f2f2f2; }";

    html += ".footer { margin-top:30px; text-align:center; font-size:12px; color:gray; }";
    html += "</style></head><body>";

    html += "<h1>Liste du Matériel</h1>";

    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tabMAT->model());
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Impossible de lire les données !");
        return;
    }

    html += "<table><tr>";
    for (int c = 0; c < model->columnCount(); c++) {
        html += "<th>" + model->headerData(c, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr>";

    for (int r = 0; r < model->rowCount(); r++) {
        html += "<tr>";
        for (int c = 0; c < model->columnCount(); c++) {
            QString cell = model->data(model->index(r, c)).toString();
            html += "<td>" + cell + "</td>";
        }
        html += "</tr>";
    }

    html += "</table>";
    html += "<div class='footer'>Document généré automatiquement — © 2025</div>";
    html += "</body></html>";

    // --------- Qt6 PDF EXPORT ---------
    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);
    pdf.setPageMargins(QMarginsF(15, 15, 15, 15));

    QPainter painter(&pdf);
    QTextDocument doc;

    doc.setDefaultFont(QFont("Arial", 14));
    doc.setHtml(html);

    // FIX: Proper width
    doc.setTextWidth(pdf.width() - 40);

    doc.drawContents(&painter);
    painter.end();

    QMessageBox::information(this, "Succès", "PDF généré :\n" + fileName);
}


void Matriel::on_affSTAT_clicked()
{
    // Create a dialog to show the chart
    QDialog *chartDialog = new QDialog(this);
    chartDialog->setWindowTitle("Statistiques du Matériel");
    chartDialog->resize(600, 400);

    QBarSet *availableSet = new QBarSet("Disponible");
    QBarSet *notAvailableSet = new QBarSet("Non Disponible");

    QStringList categories;

    // Query to get stats
    QSqlQuery query("SELECT NOMMAT, DISPONIBILITE FROM MATRIEL");
    while (query.next()) {
        QString name = query.value(0).toString();
        QString dispo = query.value(1).toString().toLower();

        categories << name;
        if (dispo == "oui")
            *availableSet << 1;
        else
            *availableSet << 0;

        if (dispo == "non")
            *notAvailableSet << 1;
        else
            *notAvailableSet << 0;
    }

    QBarSeries *series = new QBarSeries();
    series->append(availableSet);
    series->append(notAvailableSet);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Disponibilité du Matériel");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(chartDialog);
    layout->addWidget(chartView);
    chartDialog->setLayout(layout);

    chartDialog->exec();
}
void Matriel::alerteStockFaible(int seuil)
{
    QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tabMAT->model());
    if (!model) return;

    QStringList matrielsFaible;

    for (int row = 0; row < model->rowCount(); ++row) {
        int quantite = model->data(model->index(row, 2)).toInt();
        if (quantite <= seuil) {
            QString nom = model->data(model->index(row, 1)).toString();
            matrielsFaible << nom;

            for (int col = 0; col < model->columnCount(); ++col) {
                ui->tabMAT->model()->setData(model->index(row, col), QColor(Qt::red), Qt::BackgroundRole);
                ui->tabMAT->model()->setData(model->index(row, col), QColor(Qt::white), Qt::ForegroundRole);
            }
        }
    }

    if (!matrielsFaible.isEmpty()) {
        QString msg = "Les matériels suivants ont un stock faible (≤ " + QString::number(seuil) + "):\n";
        msg += matrielsFaible.join("\n");

        QMessageBox msgBox;
        msgBox.setWindowTitle("Alerte Stock Faible");
        msgBox.setText(msg);
        QPushButton* contacter = msgBox.addButton("Contacter Fournisseur", QMessageBox::ActionRole);
        msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();

        if (msgBox.clickedButton() == contacter) {
            // Déclarer body ici
            QString body = "Bonjour, je souhaite commander les matériels suivants:\n" + matrielsFaible.join("\n");

            QString subject = QUrl::toPercentEncoding("Commande matériel");
            QString bodyEncoded = QUrl::toPercentEncoding(body);

            QString url = "https://mail.google.com/mail/?view=cm&fs=1&to=fournisseur@example.com&su="
                          + subject + "&body=" + bodyEncoded;

            QDesktopServices::openUrl(QUrl(url));
        }

    }
}

void Matriel::showEvent(QShowEvent *event)
{
    // update table
    ui->tabMAT->setModel(afficher());

    // call parent
    QWidget::showEvent(event);

    // alert stock faible
 QTimer::singleShot(100, this, [this]() {
        alerteStockFaible(5); });

}
void Matriel::alerteMaintenance()
{
    QSqlQuery query("SELECT NOMMAT, DATE_DERNIER_ENTRETIEN, ENTRETIEN_FREQUENCE, NB_UTILISATIONS, NB_UTILISATIONSM FROM MATRIEL");
    QStringList alertes;

    while (query.next()) {
        QString nom = query.value(0).toString();
        QDate dernierEntretien = query.value(1).toDate();
        int freq = query.value(2).toInt();
        int nbUtil = query.value(3).toInt();
        int nbMax = query.value(4).toInt();

        QDate prochaineEntretien = dernierEntretien.addDays(freq);
        if (QDate::currentDate() >= prochaineEntretien.addDays(-3)) {
            alertes << QString("Le matériel %1 nécessite un entretien dans 3 jours").arg(nom);
        }

        if (nbUtil >= nbMax * 0.9) {
            alertes << QString("Le matériel %1 est proche de sa limite d'utilisation").arg(nom);
        }
    }

    if (!alertes.isEmpty()) {
        QMessageBox::warning(this, "Maintenance prédictive", alertes.join("\n"));
    } else {
        QMessageBox::information(this, "Maintenance prédictive", "Aucune alerte pour le moment.");
    }
}
