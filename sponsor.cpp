#include "sponsor.h"
#include "ui_sponsor.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPixmap>
#include <QPalette>

Sponsor::Sponsor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sponsor)
{
    ui->setupUi(this);
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
