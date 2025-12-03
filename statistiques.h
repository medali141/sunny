#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>


namespace Ui {
class Statistiques;
}

class Statistiques : public QDialog
{
    Q_OBJECT

public:
    explicit Statistiques(QWidget *parent = nullptr);
    ~Statistiques();

private:
    Ui::Statistiques *ui;
    void loadStatistics();
    void createPieChart();      // Distribution par niveau
    void createBarChart();      // Nombre par niveau
    void createAvgChart();      // Pourcentage moyen par niveau
};

#endif // STATISTIQUES_H
