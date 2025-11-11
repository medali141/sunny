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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/images/rs/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    this->close();  // close dashboard
}

