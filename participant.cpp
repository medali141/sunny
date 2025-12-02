#include "participant.h"
#include "ui_participant.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>
#include <QPixmap>
#include <QPalette>

Participant::Participant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Participant)
{
    ui->setupUi(this);
    ui->tabMAT->setModel(afficher()); // affichage initial
    QPixmap bkgnd(":/images/rs/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

Participant::~Participant()
{
    delete ui;
}

// --- Validation de saisie ---
bool Participant::validerSaisie()
{
    QString id = ui->idPar->text().trimmed();
    QString nom = ui->nom->text().trimmed();
    QString prenom = ui->pre->text().trimmed();
    QString age = ui->age->text().trimmed();
    QString email = ui->emai->text().trimmed();
    QString tel = ui->tel->text().trimmed();

    if(id.length() < 6 || nom.isEmpty() || prenom.isEmpty() || age.isEmpty() || email.isEmpty() || tel.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être correctement remplis !");
        return false;
    }

    // Email regex simple
    QRegularExpression emailRegex(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");
    if(!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Email invalide.");
        return false;
    }

    bool ok;
    int ageInt = age.toInt(&ok);
    if(!ok || ageInt <= 0 || ageInt > 120) {
        QMessageBox::warning(this, "Erreur", "Age invalide.");
        return false;
    }

    QRegularExpression telRegex(R"(\d+)");
    if(!telRegex.match(tel).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Téléphone invalide.");
        return false;
    }

    return true;
}

// --- Ajouter ---
bool Participant::ajouter()
{
    if(!validerSaisie()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO PARTICIPANT (ID_PAT, NOM, PRENOM, AGE, EMAIL, TEL, TYPE) "
                  "VALUES (:id, :nom, :prenom, :age, :email, :tel, :type)");
    query.bindValue(":id", ui->idPar->text().trimmed());
    query.bindValue(":nom", ui->nom->text().trimmed());
    query.bindValue(":prenom", ui->pre->text().trimmed());
    query.bindValue(":age", ui->age->text().trimmed());
    query.bindValue(":email", ui->emai->text().trimmed());
    query.bindValue(":tel", ui->tel->text().trimmed());
    query.bindValue(":type", ui->comboBox->currentText());

    if(query.exec()) {
        ui->tabMAT->setModel(afficher());
        return true;
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l'ajout du participant.");
        return false;
    }
}

void Participant::on_ajoutMat_clicked()
{
    if(ajouter())
        QMessageBox::information(this, "Succès", "Participant ajouté !");
}

// --- Modifier ---
bool Participant::modifier()
{
    if(!validerSaisie()) return false;

    QSqlQuery query;
    query.prepare("UPDATE PARTICIPANT SET NOM=:nom, PRENOM=:prenom, AGE=:age, EMAIL=:email, TEL=:tel, TYPE=:type "
                  "WHERE ID_PAT=:id");
    query.bindValue(":id", ui->idPar->text().trimmed());
    query.bindValue(":nom", ui->nom->text().trimmed());
    query.bindValue(":prenom", ui->pre->text().trimmed());
    query.bindValue(":age", ui->age->text().trimmed());
    query.bindValue(":email", ui->emai->text().trimmed());
    query.bindValue(":tel", ui->tel->text().trimmed());
    query.bindValue(":type", ui->comboBox->currentText());

    if(query.exec()) {
        ui->tabMAT->setModel(afficher());
        return true;
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification.");
        return false;
    }
}

void Participant::on_modifierMat_clicked()
{
    if(modifier())
        QMessageBox::information(this, "Succès", "Participant modifié !");
}

// --- Supprimer ---
bool Participant::supprimer()
{
    QString id = ui->idMAT_Delete->text().trimmed();
    if(id.isEmpty()) return false;

    QSqlQuery query;
    query.prepare("DELETE FROM PARTICIPANT WHERE ID_PAT=:id");
    query.bindValue(":id", id);

    if(query.exec()) {
        ui->tabMAT->setModel(afficher());
        return true;
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression.");
        return false;
    }
}

void Participant::on_supprimerMat_clicked()
{
    if(ui->idMAT_Delete->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "ID requis pour supprimer !");
        return;
    }

    if(supprimer())
        QMessageBox::information(this, "Succès", "Participant supprimé !");
}

// --- Afficher ---
QSqlQueryModel* Participant::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PARTICIPANT");
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prenom");
    model->setHeaderData(3, Qt::Horizontal, "Age");
    model->setHeaderData(4, Qt::Horizontal, "Email");
    model->setHeaderData(5, Qt::Horizontal, "Tel");
    model->setHeaderData(6, Qt::Horizontal, "Type");
    return model;
}

// --- Rechercher ---
QSqlQueryModel* Participant::rechercher()
{
    QString id = ui->recherch_id->text().trimmed();
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM PARTICIPANT WHERE ID_PAT LIKE :id");
    query.bindValue(":id", "%" + id + "%");
    query.exec();
    model->setQuery(query);
    return model;
}

void Participant::on_rechID_clicked()
{
    ui->tabMAT->setModel(rechercher());
}

// --- Affichage ---
void Participant::on_afficherMar_clicked()
{
    ui->tabMAT->setModel(afficher());
}

// --- Back ---
void Participant::on_backButton_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    this->close();
}
