#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "matriel.h"
#include "sponsor.h"
#include "event.h"
#include "employe.h"
#include "participant.h"
#include "login.h"

#include <QPixmap>
#include <QPalette>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Background
    QPixmap bkgnd(":/images/rs/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);




QMessageBox::information(this, "TEST", "MainWindow is running");
    // 🔥 Arduino
    arduino = new Ard(this);

    connect(arduino, &Ard::arduinoConnected,
            this, &MainWindow::onArduinoConnected);

    connect(arduino, &Ard::fireDetected,
            this, &MainWindow::onFireDetected);

    arduino->connectToArduino();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ---------- Navigation buttons ----------

void MainWindow::on_matrielButton_clicked()
{
    Matriel *m = new Matriel();
    m->show();
    this->hide();
}

void MainWindow::on_sponsorButton_clicked()
{
    Sponsor *s = new Sponsor();
    s->show();
    this->hide();
}

void MainWindow::on_eventButton_clicked()
{
    Event *e = new Event();
    e->show();
    this->hide();
}

void MainWindow::on_employeButton_clicked()
{
    Employe *emp = new Employe();
    emp->show();
    this->hide();
}

void MainWindow::on_participantButton_clicked()
{
    Participant *p = new Participant();
    p->show();
    this->hide();
}

void MainWindow::on_logoutButton_clicked()
{
    Login *loginWindow = new Login();
    loginWindow->show();
    this->close();
}
void MainWindow::on_flameHistoryButton_clicked()
{
    FlameHistory *history = new FlameHistory();
    history->setAttribute(Qt::WA_DeleteOnClose);
    history->show();
}
// ---------- Arduino connected ----------

void MainWindow::onArduinoConnected(const QString &port)
{
    QMessageBox::information(
        this,
        "Arduino Connected",
        "🔥 Flame detector is ONLINE\nPort: " + port
        );
}

// ---------- Fire detected ----------

void MainWindow::onFireDetected()
{
    QMessageBox::critical(
        this,
        "🔥 FIRE ALERT",
        "Flame detected!\nIncident saved to database."
        );

    saveFireIncident();
}

// ---------- Save to Oracle ----------

void MainWindow::saveFireIncident()
{
    QSqlQuery query;

    query.prepare(
        "INSERT INTO flame (fire_date, fire_time) "
        "VALUES (:fire_date, :fire_time)"
        );

    query.bindValue(":fire_date", QDate::currentDate());
    query.bindValue(":fire_time",
                    QTime::currentTime().toString("HH:mm:ss"));

    if (!query.exec()) {
        qDebug() << "❌ Oracle Error:"
                 << query.lastError().text();
    } else {
        qDebug() << "✅ Fire incident saved";
    }
}

