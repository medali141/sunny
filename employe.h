#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "ui_employe.h"
#include <QDate>

struct EmployeScore {
    QString id;
    QString nom;
    QString poste;
    int tachesEnCours;
    int tachesReussies;
    double moyennePerformance;
    QString disponibilite;
    double scoreTotal;
};

struct ResultatVerificationConge {
    bool estValide;
    QString message;
    int employesPresents;
    int joursRestants;
};

namespace Ui {
class Employe;
}

class Employe : public QWidget
{
    Q_OBJECT

public:
    explicit Employe(QWidget *parent = nullptr);
    ~Employe();

private slots:
    void on_backButton_clicked();
    void on_ajoutMat_clicked();
    void on_modifierMat_clicked();
    void on_supprimerMat_clicked();
    void on_afficherMar_clicked();  // Display all
    void on_rechID_clicked();

 
    // Slots pour les fonctionnalités métier
    void on_statistiquesButton_clicked();
    void on_assignationAutoButton_clicked();
    void on_congesButton_clicked();

    void on_exportPdfButton_clicked();

    void afficherStatistiques();
    void afficherAssignationAuto();
    void afficherGestionConges();

    double calculerScore(int tachesEnCours, int tachesReussies, double moyennePerf, bool posteCorrespond);
    QList<EmployeScore> calculerScoresEmployes(const QString &posteRequis);
    int compterEmployesPresents(const QDate &dateDebut, const QDate &dateFin);
    int getSoldeConges(const QString &idEmploye);
    ResultatVerificationConge verifierDemandeConge(const QString &idEmploye, const QDate &dateDebut, const QDate &dateFin);
    bool enregistrerDemandeConge(const QString &idEmploye, const QDate &dateDebut, const QDate &dateFin, const QString &statut, const QString &motif);
    QSqlQueryModel* getSoldesConges();
    QSqlQueryModel* getHistoriqueConges();
 
private:
    Ui::Employe *ui;

    // --- Database methods ---
    bool ajouter();
    bool modifier();
    bool supprimer();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher();
};

#endif // EMPLOYE_H
