#ifndef EVENT_H
#define EVENT_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class Event;
}

class Event : public QWidget
{
    Q_OBJECT

public:
    explicit Event(QWidget *parent = nullptr);
    ~Event();

private slots:
    void on_ajoutMat_clicked();
    void on_modifierMat_clicked();
    void on_supprimerMat_clicked();
    void on_afficherMar_clicked();
    void on_rechID_clicked();
    void on_backButton_clicked();

private:
    Ui::Event *ui;
    void rafraichirAffichage();
    bool controleSaisie();
};

#endif // EVENT_H
