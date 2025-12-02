#ifndef MATRIEL_H
#define MATRIEL_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QShowEvent>

namespace Ui {
class Matriel;
}

class Matriel : public QWidget
{
    Q_OBJECT

public:
    explicit Matriel(QWidget *parent = nullptr);
    ~Matriel();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_backButton_clicked();
    void on_ajoutMat_clicked();
    void on_modifierMat_clicked();
    void on_supprimerMat_clicked();
    void on_Rtri_clicked();
    void on_Rtri_2_clicked();
    void on_rechID_clicked();
    void on_exportPDFButton_clicked();
    void on_affSTAT_clicked();
    void alerteStockFaible(int seuil = 5);
    void alerteMaintenance(); // new maintenance predictive

private:
    Ui::Matriel *ui;

    // --- Database methods ---
    bool ajouter();
    bool modifier();
    bool supprimer();
    QSqlQueryModel* afficher();
    QSqlQueryModel* trierParqt();
    QSqlQueryModel* trierNOMMAT();
    QSqlQueryModel* rechercher();
};

#endif // MATRIEL_H
