#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "createaccount.h"
#include <QMessageBox>
#include <QScreen>
#include <QGuiApplication>

#include <QPixmap>
#include <QPalette>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->passwordInput->setEchoMode(QLineEdit::Password);

    QPixmap bkgnd(":/images/rs/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);



    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);




}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM LOGIN WHERE USERNAME = :username AND PWD = :pwd");
    query.bindValue(":username", username);
    query.bindValue(":pwd", password);

    if (query.exec() && query.next()) {
        QMessageBox::information(this, "Login", "Login successful!");

        MainWindow *mainWin = new MainWindow();
        mainWin->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Invalid username or password.");
    }
}

void Login::on_createAccountButton_clicked()
{

    CreateAccount *c = new CreateAccount();
    c->show();
    this->hide();
}

