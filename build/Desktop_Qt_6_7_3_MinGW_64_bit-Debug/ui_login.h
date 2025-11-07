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

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(1316, 666);
        labelUsername = new QLabel(Login);
        labelUsername->setObjectName("labelUsername");
        labelUsername->setGeometry(QRect(90, 130, 101, 20));
        usernameInput = new QLineEdit(Login);
        usernameInput->setObjectName("usernameInput");
        usernameInput->setGeometry(QRect(230, 130, 113, 28));
        labelUsername_2 = new QLabel(Login);
        labelUsername_2->setObjectName("labelUsername_2");
        labelUsername_2->setGeometry(QRect(90, 180, 101, 20));
        passwordInput = new QLineEdit(Login);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setGeometry(QRect(230, 180, 113, 28));
        loginButton = new QPushButton(Login);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(240, 250, 90, 29));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Form", nullptr));
        labelUsername->setText(QCoreApplication::translate("Login", "User name :", nullptr));
        labelUsername_2->setText(QCoreApplication::translate("Login", "password : ", nullptr));
        loginButton->setText(QCoreApplication::translate("Login", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
