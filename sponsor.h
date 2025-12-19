#ifndef SPONSOR_H
#define SPONSOR_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QPushButton>
#include <QFrame>
#include <QGraphicsEffect>
#include <QPropertyAnimation>
#include <QLinearGradient>
#include <QMap>
#include <QTimer>          // <<--- AJOUT POUR LE CAPTEUR

namespace Ui {
class Sponsor;
}

class Sponsor : public QWidget
{
    Q_OBJECT

public:
    explicit Sponsor(QWidget *parent = nullptr);
    ~Sponsor();

    // CRUD operations
    bool ajouter();
    bool modifier();
    bool supprimer();

    // Display / Search
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher();

private slots:
    // UI button slots
    void on_backButton_clicked();
    void on_ajoutMat_clicked();
    void on_modifierMat_clicked();
    void on_supprimerMat_clicked();
    void on_afficherMar_clicked();
    void on_rechID_clicked();
    void on_send_mail_clicked();
    void on_Qrcode_clicked();
    void on_stat_clicked();
    void on_pdf_clicked();
    void on_predai_clicked();

    // --- CAPTEUR / SPONSOR1 ---
    void updateSensorData();   // <<--- SLOT QUI LIT LA DB ET MET À JOUR LES LABELS

private:
    Ui::Sponsor *ui;

    // Helper functions
    void trouverMeilleurSponsor(); // AI prediction

    // --- CAPTEUR ---
    QTimer *sensorTimer;       // <<--- TIMER POUR RAFRAICHIR LES DONNÉES
};

#endif // SPONSOR_H
