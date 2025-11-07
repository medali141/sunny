#ifndef SPONSOR_H
#define SPONSOR_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class Sponsor;
}

class Sponsor : public QWidget
{
    Q_OBJECT

public:
    explicit Sponsor(QWidget *parent = nullptr);
    ~Sponsor();

    bool ajouter();
    bool modifier();
    bool supprimer();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher();

private slots:
    void on_backButton_clicked();
    void on_ajoutMat_clicked();
    void on_modifierMat_clicked();
    void on_supprimerMat_clicked();
    void on_afficherMar_clicked();
    void on_rechID_clicked();

private:
    Ui::Sponsor *ui;
};

#endif // SPONSOR_H
