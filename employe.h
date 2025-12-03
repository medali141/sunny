#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

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
