#ifndef MATRIEL_H
#define MATRIEL_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class Matriel;
}

class Matriel : public QWidget
{
    Q_OBJECT

public:
    explicit Matriel(QWidget *parent = nullptr);
    ~Matriel();

private slots:
    void on_backButton_clicked();
    void on_ajoutMat_clicked();
    void on_modifierMat_clicked();
    void on_supprimerMat_clicked();
    void on_Rtri_clicked();
    void on_Rtri_2_clicked();
    void on_rechID_clicked();

    void on_afficherMar_2_clicked();

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
