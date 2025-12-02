#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>
#include <QDate>

namespace Ui {
class Employe;
}

// Structure pour l'assignation automatique
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

// Structure pour la vérification des congés
struct ResultatVerificationConge {
    bool estValide;
    QString message;
    int employesPresents;
    int joursRestants;
};

class Employe : public QWidget
{
    Q_OBJECT

public:
    explicit Employe(QWidget *parent = nullptr);
    ~Employe();

private slots:
    // Slots pour les opérations CRUD
    void on_backButton_clicked();
    void on_ajoutMat_clicked();
    void on_modifierMat_clicked();
    void on_supprimerMat_clicked();
    void on_afficherMar_clicked();
    void on_rechID_clicked();

    // Slots pour les fonctionnalités métier
    void on_statistiquesButton_clicked();
    void on_assignationAutoButton_clicked();
    void on_congesButton_clicked();

private:
    Ui::Employe *ui;

    // --- Méthodes CRUD de base ---
    bool ajouter();
    bool modifier();
    bool supprimer();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher();

    // --- Statistiques graphiques ---
    void afficherStatistiques();

    // --- Assignation automatique ---
    void afficherAssignationAuto();
    QList<EmployeScore> calculerScoresEmployes(const QString &posteRequis);
    double calculerScore(int tachesEnCours, int tachesReussies,
                         double moyennePerf, bool posteCorrespond);

    // --- Gestion des congés ---
    void afficherGestionConges();
    ResultatVerificationConge verifierDemandeConge(const QString &idEmploye,
                                                   const QDate &dateDebut,
                                                   const QDate &dateFin);
    int compterEmployesPresents(const QDate &dateDebut, const QDate &dateFin);
    int getSoldeConges(const QString &idEmploye);
    bool enregistrerDemandeConge(const QString &idEmploye,
                                 const QDate &dateDebut,
                                 const QDate &dateFin,
                                 const QString &statut,
                                 const QString &motif = "");
    QSqlQueryModel* getHistoriqueConges();
    QSqlQueryModel* getSoldesConges();
};

#endif // EMPLOYE_H
