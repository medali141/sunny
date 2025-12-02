#include "matriel.h"
#include "ui_matriel.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPixmap>
#include <QPalette>

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


    // Display all matriels initially
    ui->tabMAT->setModel(afficher());
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
    query.prepare("INSERT INTO MATRIEL (ID_MAT, NOMMAT, QUANTITE, DISPONIBILITE) "
                  "VALUES (:id_mat, :nommat, :quantite, :disponibilite)");
    query.bindValue(":id_mat", ui->idMat->text());
    query.bindValue(":nommat", ui->nomMat->text());
    query.bindValue(":quantite", ui->Quantite->text());
    query.bindValue(":disponibilite", ui->Dispo->text());

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
    query.prepare("UPDATE MATRIEL SET NOMMAT = :nommat, QUANTITE = :quantite, DISPONIBILITE = :disponibilite "
                  "WHERE ID_MAT = :id_mat");
    query.bindValue(":id_mat", ui->idMat->text());
    query.bindValue(":nommat", ui->nomMat->text());
    query.bindValue(":quantite", ui->Quantite->text());
    query.bindValue(":disponibilite", ui->Dispo->text());

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
    model->setQuery("SELECT * FROM MATRIEL");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_MAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMMAT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DISPONIBILITE"));
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


