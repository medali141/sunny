#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class Participant;
}

class Participant : public QWidget
{
    Q_OBJECT

public:
    explicit Participant(QWidget *parent = nullptr);
    ~Participant();

    bool ajouter();
    bool modifier();
    bool supprimer();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher();
    bool validerSaisie();

private slots:
    void on_ajoutMat_clicked();
    void on_modifierMat_clicked();
    void on_supprimerMat_clicked();
    void on_afficherMar_clicked();
    void on_rechID_clicked();
    void on_backButton_clicked();

private:
    Ui::Participant *ui;
};

#endif // PARTICIPANT_H
