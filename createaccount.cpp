#include "createaccount.h"
#include "ui_createaccount.h"
#include "login.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QPalette>

CreateAccount::CreateAccount(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateAccount)
{
    ui->setupUi(this);

    // Optional: add background if you have an image in your resources
    // QPixmap bg(":/resources/bg.png");
    // QPalette palette;
    // palette.setBrush(QPalette::Window, bg.scaled(this->size(), Qt::KeepAspectRatioByExpanding));
    // this->setPalette(palette);

    // Make password hidden
    ui->passwordInput->setEchoMode(QLineEdit::Password);

    // Optional: style setup (if not using QSS)
    this->setStyleSheet(
        "QWidget { background-color: #2b2b2b; color: white; font-family: 'Segoe UI'; font-size: 14px; }"
        "QLineEdit { background: white; color: black; border-radius: 6px; padding: 4px; }"
        "QPushButton { background-color: #FFD700; color: black; border-radius: 10px; padding: 6px; font-weight: bold; }"
        "QPushButton:hover { background-color: #ffea00; }"
        "QPushButton#backButton { background-color: #555; color: white; }"
        "QPushButton#backButton:hover { background-color: #666; }"
        );
}

CreateAccount::~CreateAccount()
{
    delete ui;
}

// 🔙 Go back to login
void CreateAccount::on_backButton_clicked()
{
    this->close();
    Login *loginPage = new Login();
    loginPage->show();
}

// 🆕 Create new user account
void CreateAccount::on_createAccountButton_clicked()
{
    QString username = ui->usernameInput->text().trimmed();
    QString password = ui->passwordInput->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error ⚠️", "Please fill in both username and password.");
        return;
    }

    // Check if username already exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT USERNAME FROM LOGIN WHERE USERNAME = :username");
    checkQuery.bindValue(":username", username);

    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to check username.\n" + checkQuery.lastError().text());
        return;
    }

    if (checkQuery.next()) {
        QMessageBox::warning(this, "Error ⚠️", "Username already exists. Please choose another one.");
        return;
    }

    // Insert new user
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO LOGIN (USERNAME, PWD) VALUES (:username, :pwd)");
    insertQuery.bindValue(":username", username);
    insertQuery.bindValue(":pwd", password);

    if (insertQuery.exec()) {
        QMessageBox::information(this, "Success 🎉", "Account created successfully!");
        this->close();
        Login *loginPage = new Login();
        loginPage->show();
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to create account.\n" + insertQuery.lastError().text());
    }
}
