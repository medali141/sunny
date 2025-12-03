#include "statistiques.h"
#include "ui_statistiques.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QtCharts/QChart>

Statistiques::Statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistiques)
{
    ui->setupUi(this);
    setWindowTitle("Statistiques des Sponsors");
    loadStatistics();
}

Statistiques::~Statistiques()
{
    delete ui;
}

void Statistiques::loadStatistics()
{
    createPieChart();
    createBarChart();
    createAvgChart();
}

void Statistiques::createPieChart()
{
    // Query pour obtenir la distribution par niveau
    QSqlQuery query;
    query.prepare("SELECT NIVEAU, COUNT(*) as count FROM SPONSOR GROUP BY NIVEAU ORDER BY NIVEAU");
    
    if (!query.exec()) {
        qDebug() << "Erreur requête pie chart:" << query.lastError().text();
        return;
    }

    QPieSeries *series = new QPieSeries();
    
    while (query.next()) {
        QString niveau = "Niveau " + query.value(0).toString();
        int count = query.value(1).toInt();
        
        QPieSlice *slice = series->append(niveau, count);
        slice->setLabelVisible(true);
        slice->setLabel(QString("%1: %2 (%3%)")
                       .arg(niveau)
                       .arg(count)
                       .arg(100 * slice->percentage(), 0, 'f', 1));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Distribution des Sponsors par Niveau");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->chartView1->setChart(chart);
    ui->chartView1->setRenderHint(QPainter::Antialiasing);
}

void Statistiques::createBarChart()
{
    // Query pour obtenir le nombre par niveau
    QSqlQuery query;
    query.prepare("SELECT NIVEAU, COUNT(*) as count FROM SPONSOR GROUP BY NIVEAU ORDER BY NIVEAU");
    
    if (!query.exec()) {
        qDebug() << "Erreur requête bar chart:" << query.lastError().text();
        return;
    }

    QBarSet *set = new QBarSet("Nombre de Sponsors");
    QStringList categories;

    while (query.next()) {
        QString niveau = query.value(0).toString();
        int count = query.value(1).toInt();
        
        *set << count;
        categories << "Niveau " + niveau;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre de Sponsors par Niveau");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->chartView2->setChart(chart);
    ui->chartView2->setRenderHint(QPainter::Antialiasing);
}

void Statistiques::createAvgChart()
{
    // Query pour obtenir la moyenne des pourcentages par niveau
    QSqlQuery query;
    query.prepare("SELECT NIVEAU, AVG(POURCENTAGE) as avg_pct FROM SPONSOR GROUP BY NIVEAU ORDER BY NIVEAU");
    
    if (!query.exec()) {
        qDebug() << "Erreur requête avg chart:" << query.lastError().text();
        return;
    }

    QBarSet *set = new QBarSet("Pourcentage Moyen");
    QStringList categories;

    while (query.next()) {
        QString niveau = query.value(0).toString();
        double avgPct = query.value(1).toDouble();
        
        *set << avgPct;
        categories << "Niveau " + niveau;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pourcentage Moyen par Niveau");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Pourcentage (%)");
    axisY->setRange(0, 100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->chartView3->setChart(chart);
    ui->chartView3->setRenderHint(QPainter::Antialiasing);
}
