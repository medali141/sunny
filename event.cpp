#include "event.h"
#include "ui_event.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QPixmap>
#include <QPalette>
#include <QRegularExpression>

Event::Event(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Event)
{
    ui->setupUi(this);
    rafraichirAffichage();

    // --- Background ---
    QPixmap bkgnd(":/images/rs/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

Event::~Event()
{
    delete ui;
}

// ================== CONTROLE DE SAISIE ==================
bool Event::controleSaisie()
{
    QString id = ui->idEvent->text().trimmed();
    QString nom = ui->nomEvent->text().trimmed();
    QString date = ui->dateEvent->text().trimmed();
    QString responsable = ui->responsable->text().trimmed();
    QString statut = ui->statut->text().trimmed();

    // Vérification ID
    if (id.length() < 3) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir au moins 3 caractères.");
        return false;
    }

    // Champs obligatoires
    if (nom.isEmpty() || date.isEmpty() || responsable.isEmpty() || statut.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
        return false;
    }

    // Vérification du format de la date (JJ/MM/AAAA)
    QRegularExpression regexDate("^\\d{2}/\\d{2}/\\d{4}$");
    if (!regexDate.match(date).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Le format de la date doit être JJ/MM/AAAA.");
        return false;
    }

    // Vérification du statut
    QString s = statut.toLower();
    if (s != "actif" && s != "inactif") {
        QMessageBox::warning(this, "Erreur", "Le statut doit être 'actif' ou 'inactif'.");
        return false;
    }

    return true;
}

// ================== RAFFRAICHIR TABLE ==================
void Event::rafraichirAffichage()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENMENT ORDER BY ID_EVENT ASC");
    ui->tabMAT->setModel(model);
}

// ================== AJOUTER ==================
void Event::on_ajoutMat_clicked()
{
    if (!controleSaisie())
        return;

    QString id = ui->idEvent->text();
    QString nom = ui->nomEvent->text();
    QString date = ui->dateEvent->text();
    QString responsable = ui->responsable->text();
    QString statut = ui->statut->text();
    QString remarque = ui->remarque->text();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO EVENMENT (ID_EVENT, NOMEVENT, DATEE, RESPONSABLE, STATUT, REMARQUE) "
        "VALUES (:id, :nom, TO_DATE(:datee, 'DD/MM/YYYY'), :responsable, :statut, :remarque)"
        );

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":datee", date);
    query.bindValue(":responsable", responsable);
    query.bindValue(":statut", statut);
    query.bindValue(":remarque", remarque);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Événement ajouté avec succès !");
        rafraichirAffichage();
    } else {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        qDebug() << "Erreur SQL (ajout):" << query.lastError().text();
    }
}

// ================== MODIFIER ==================
void Event::on_modifierMat_clicked()
{
    if (!controleSaisie())
        return;

    QString id = ui->idEvent->text();
    QString nom = ui->nomEvent->text();
    QString date = ui->dateEvent->text();
    QString responsable = ui->responsable->text();
    QString statut = ui->statut->text();
    QString remarque = ui->remarque->text();

    QSqlQuery query;
    query.prepare(
        "UPDATE EVENMENT SET NOMEVENT=:nom, DATEE=TO_DATE(:datee, 'DD/MM/YYYY'), "
        "RESPONSABLE=:responsable, STATUT=:statut, REMARQUE=:remarque "
        "WHERE ID_EVENT=:id"
        );

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":datee", date);
    query.bindValue(":responsable", responsable);
    query.bindValue(":statut", statut);
    query.bindValue(":remarque", remarque);

    if (query.exec() && query.numRowsAffected() > 0) {
        QMessageBox::information(this, "Succès", "Événement modifié avec succès !");
        rafraichirAffichage();
    } else {
        QMessageBox::critical(this, "Erreur SQL", "Échec de la modification : " + query.lastError().text());
        qDebug() << "Erreur SQL (modif):" << query.lastError().text();
    }
}

// ================== SUPPRIMER ==================
void Event::on_supprimerMat_clicked()
{
    QString id = ui->idMAT_Delete->text().trimmed();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID à supprimer !");
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM EVENMENT WHERE ID_EVENT = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.numRowsAffected() > 0) {
        QMessageBox::information(this, "Succès", "Événement supprimé avec succès !");
        rafraichirAffichage();
    } else {
        QMessageBox::critical(this, "Erreur SQL", "Échec de la suppression : " + query.lastError().text());
        qDebug() << "Erreur SQL (suppression):" << query.lastError().text();
    }
}

// ================== AFFICHER ==================
void Event::on_afficherMar_clicked()
{
    rafraichirAffichage();
}

// ================== RECHERCHER ==================
void Event::on_rechID_clicked()
{
    QString id = ui->recherch_id->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID à rechercher !");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENMENT WHERE ID_EVENT LIKE '%" + id + "%'");
    ui->tabMAT->setModel(model);
}

// ================== BACK ==================
void Event::on_backButton_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    this->close();
}
