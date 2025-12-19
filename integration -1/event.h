#ifndef EVENT_H
#define EVENT_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QtCharts>
#include "meteoassistant.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Event;
}
QT_END_NAMESPACE

class Event : public QMainWindow
{
    Q_OBJECT

public:
    explicit Event(QWidget *parent = nullptr);
    ~Event();

private slots:
    void on_btnAjouterEvenement_clicked();
    void on_btnModifierEvenement_clicked();
    void on_btnSupprimerEvenement_clicked();
    void on_tableView_evenment_clicked(const QModelIndex &index);
    void on_rechercherevent_textChanged(const QString &text);
    void on_pdf_clicked();
    void on_btnStatistiques_clicked();
    void on_btnExportCalendar_clicked();

    // Nouveaux slots pour l'analyse météo
    void on_btnAnalyserMeteo_clicked();
    void onAnalyseMeteoTerminee(const MeteoRecommendation &recommendation);
    void onErreurMeteo(const QString &message);

    // Back button slot (added for integration)
    void on_backButton_clicked();

    // Navigation button slots
    void on_btnsponsor_clicked();
    void on_btnevenement_clicked();
    void on_btnparticipants_clicked();
    void on_btnemploye_clicked();
    void on_btnlogistique_clicked();

private:
    Ui::Event *ui;
    MeteoAssistant *meteoAssistant;

    void rafraichirTableEvenements();
    void installerValidationsEvenements();
    void rechercherEvenements(const QString &searchText);
    void exporterPDF();
    void afficherStatistiquesParMois();
    void exporterCalendrierICS();
};

#endif // EVENT_H
