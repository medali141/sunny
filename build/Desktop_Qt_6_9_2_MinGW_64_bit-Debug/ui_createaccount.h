/********************************************************************************
** Form generated from reading UI file 'createaccount.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEACCOUNT_H
#define UI_CREATEACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateAccount
{
public:
    QLineEdit *passwordInput;
    QLabel *labelUsername_2;
    QLineEdit *usernameInput;
    QPushButton *createAccountButton;
    QLabel *labelUsername;
    QPushButton *backButton;

    void setupUi(QWidget *CreateAccount)
    {
        if (CreateAccount->objectName().isEmpty())
            CreateAccount->setObjectName("CreateAccount");
        CreateAccount->resize(505, 358);
        passwordInput = new QLineEdit(CreateAccount);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setGeometry(QRect(250, 140, 113, 28));
        labelUsername_2 = new QLabel(CreateAccount);
        labelUsername_2->setObjectName("labelUsername_2");
        labelUsername_2->setGeometry(QRect(110, 140, 101, 20));
        usernameInput = new QLineEdit(CreateAccount);
        usernameInput->setObjectName("usernameInput");
        usernameInput->setGeometry(QRect(250, 90, 113, 28));
        createAccountButton = new QPushButton(CreateAccount);
        createAccountButton->setObjectName("createAccountButton");
        createAccountButton->setGeometry(QRect(240, 190, 141, 31));
        labelUsername = new QLabel(CreateAccount);
        labelUsername->setObjectName("labelUsername");
        labelUsername->setGeometry(QRect(110, 90, 101, 20));
        backButton = new QPushButton(CreateAccount);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(390, 310, 90, 29));

        retranslateUi(CreateAccount);

        QMetaObject::connectSlotsByName(CreateAccount);
    } // setupUi

    void retranslateUi(QWidget *CreateAccount)
    {
        CreateAccount->setWindowTitle(QCoreApplication::translate("CreateAccount", "Form", nullptr));
        labelUsername_2->setText(QCoreApplication::translate("CreateAccount", "password : ", nullptr));
        createAccountButton->setText(QCoreApplication::translate("CreateAccount", "Create the Account ", nullptr));
        labelUsername->setText(QCoreApplication::translate("CreateAccount", "User name :", nullptr));
        backButton->setText(QCoreApplication::translate("CreateAccount", "back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateAccount: public Ui_CreateAccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEACCOUNT_H
