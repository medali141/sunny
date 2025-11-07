/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *matrielButton;
    QPushButton *sponsorButton;
    QPushButton *eventButton;
    QPushButton *participantButton;
    QPushButton *employeButton;
    QPushButton *logoutButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1323, 666);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        matrielButton = new QPushButton(centralwidget);
        matrielButton->setObjectName("matrielButton");
        matrielButton->setGeometry(QRect(20, 120, 90, 29));
        sponsorButton = new QPushButton(centralwidget);
        sponsorButton->setObjectName("sponsorButton");
        sponsorButton->setGeometry(QRect(20, 180, 90, 29));
        eventButton = new QPushButton(centralwidget);
        eventButton->setObjectName("eventButton");
        eventButton->setGeometry(QRect(20, 240, 90, 29));
        participantButton = new QPushButton(centralwidget);
        participantButton->setObjectName("participantButton");
        participantButton->setGeometry(QRect(20, 390, 90, 29));
        employeButton = new QPushButton(centralwidget);
        employeButton->setObjectName("employeButton");
        employeButton->setGeometry(QRect(20, 310, 90, 29));
        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setGeometry(QRect(1180, 570, 90, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1323, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        matrielButton->setText(QCoreApplication::translate("MainWindow", "Matriel", nullptr));
        sponsorButton->setText(QCoreApplication::translate("MainWindow", "sponsor", nullptr));
        eventButton->setText(QCoreApplication::translate("MainWindow", "event", nullptr));
        participantButton->setText(QCoreApplication::translate("MainWindow", "Participant", nullptr));
        employeButton->setText(QCoreApplication::translate("MainWindow", "Employe", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
