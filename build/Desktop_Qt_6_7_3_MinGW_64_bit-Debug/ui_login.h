/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *labelUsername;
    QLineEdit *usernameInput;
    QLabel *labelUsername_2;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QPushButton *createAccountButton;
    QLabel *labelUsername_3;
    QLabel *label;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(1316, 666);
        labelUsername = new QLabel(Login);
        labelUsername->setObjectName("labelUsername");
        labelUsername->setGeometry(QRect(470, 220, 101, 20));
        usernameInput = new QLineEdit(Login);
        usernameInput->setObjectName("usernameInput");
        usernameInput->setGeometry(QRect(610, 220, 111, 41));
        labelUsername_2 = new QLabel(Login);
        labelUsername_2->setObjectName("labelUsername_2");
        labelUsername_2->setGeometry(QRect(470, 270, 101, 20));
        passwordInput = new QLineEdit(Login);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setGeometry(QRect(610, 270, 111, 41));
        loginButton = new QPushButton(Login);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(610, 330, 111, 41));
        createAccountButton = new QPushButton(Login);
        createAccountButton->setObjectName("createAccountButton");
        createAccountButton->setGeometry(QRect(420, 330, 181, 41));
        labelUsername_3 = new QLabel(Login);
        labelUsername_3->setObjectName("labelUsername_3");
        labelUsername_3->setGeometry(QRect(540, 170, 151, 41));
        label = new QLabel(Login);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 91, 101));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/rs/logo.png")));
        label->setScaledContents(true);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Form", nullptr));
        labelUsername->setText(QCoreApplication::translate("Login", "User name :", nullptr));
        labelUsername_2->setText(QCoreApplication::translate("Login", "password : ", nullptr));
        loginButton->setText(QCoreApplication::translate("Login", "Login", nullptr));
        createAccountButton->setText(QCoreApplication::translate("Login", "Create an account ", nullptr));
        labelUsername_3->setText(QCoreApplication::translate("Login", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-style:italic; text-decoration: underline;\"> Login</span></p></body></html>", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
