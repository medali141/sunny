#include "employe.h"
#include "ui_employe.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>

Employe::Employe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Employe)
{
    ui->setupUi(this);

    // Display all employees initially
    ui->tabMAT->setModel(afficher());
}

Employe::~Employe()
{
    delete ui;
}

// --- Back button ---
void Employe::on_backButton_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    this->close();
}

// --- Add ---
bool Employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (ID_EMPLOYE, NOM, POSTE, EMAIL, STATUT_DEM) "
                  "VALUES (:id, :nom, :poste, :email, :statut)");
    query.bindValue(":id", ui->idE->text().trimmed());
    query.bindValue(":nom", ui->nom->text().trimmed());
    query.bindValue(":poste", ui->poste->text().trimmed());
    query.bindValue(":email", ui->email->text().trimmed());
    query.bindValue(":statut", ui->statut_dem->text().trimmed());

    return query.exec();
}

void Employe::on_ajoutMat_clicked()
{
    QString id = ui->idE->text().trimmed();
    QString nom = ui->nom->text().trimmed();
    QString poste = ui->poste->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString statut = ui->statut_dem->text().trimmed();

    // --- Validation ---
    if (id.isEmpty() || nom.isEmpty() || poste.isEmpty() || email.isEmpty() || statut.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis !");
        return;
    }

    if (id.length() < 6) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir au moins 6 caractères !");
        return;
    }

    if (statut.toLower() != "passe" && statut.toLower() != "en attente") {
        QMessageBox::warning(this, "Erreur", "Le statut doit être 'passe' ou 'en attente' !");
        return;
    }

    QRegularExpression emailRegex(R"((\w+)(\.?\w*)@(\w+)\.(\w+))");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Adresse email invalide !");
        return;
    }

    // --- si tout est OK ---
    if (ajouter()) {
        QMessageBox::information(this, "Succès", "Employé ajouté avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l'ajout.");
    }
}

// --- Modify ---
bool Employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM = :nom, POSTE = :poste, EMAIL = :email, STATUT_DEM = :statut "
                  "WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", ui->idE->text().trimmed());
    query.bindValue(":nom", ui->nom->text().trimmed());
    query.bindValue(":poste", ui->poste->text().trimmed());
    query.bindValue(":email", ui->email->text().trimmed());
    query.bindValue(":statut", ui->statut_dem->text().trimmed());

    return query.exec();
}

void Employe::on_modifierMat_clicked()
{
    QString id = ui->idE->text().trimmed();
    QString nom = ui->nom->text().trimmed();
    QString poste = ui->poste->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString statut = ui->statut_dem->text().trimmed();

    // --- Validation ---
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "ID est obligatoire pour la modification !");
        return;
    }

    if (id.length() < 6) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir au moins 6 caractères !");
        return;
    }

    if (statut.toLower() != "approuvé" && statut.toLower() != "en attente") {
        QMessageBox::warning(this, "Erreur", "Le statut doit être 'approuvé' ou 'en attente' !");
        return;
    }

    QRegularExpression emailRegex(R"((\w+)(\.?\w*)@(\w+)\.(\w+))");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Adresse email invalide !");
        return;
    }

    if (modifier()) {
        QMessageBox::information(this, "Succès", "Employé modifié avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification.");
    }
}

// --- Delete ---
bool Employe::supprimer()
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", ui->idMAT_Delete->text().trimmed());
    return query.exec();
}

void Employe::on_supprimerMat_clicked()
{
    QString id = ui->idMAT_Delete->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID à supprimer !");
        return;
    }

    if (supprimer()) {
        QMessageBox::information(this, "Succès", "Employé supprimé avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression.");
    }
}

// --- Display all ---
void Employe::on_afficherMar_clicked()
{
    ui->tabMAT->setModel(afficher());
}

// --- Display ---
QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMPLOYE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("POSTE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT_DEM"));
    return model;
}

// --- Search ---
QSqlQueryModel* Employe::rechercher()
{
    QString id = ui->recherch_id->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID pour la recherche !");
        return afficher();
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE ID_EMPLOYE LIKE :id");
    query.bindValue(":id", "%" + id + "%");
    query.exec();
    model->setQuery(query);
    return model;
}

void Employe::on_rechID_clicked()
{
    ui->tabMAT->setModel(rechercher());
}
