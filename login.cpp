#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QMessageBox>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    if (username == "" && password == "") {
        QMessageBox::information(this, "Login", "Login successful!");

        MainWindow *mainWin = new MainWindow();
        mainWin->show();
        this->close(); // close login window
    } else {
        QMessageBox::warning(this, "Error", "Invalid username or password.");
    }
}
