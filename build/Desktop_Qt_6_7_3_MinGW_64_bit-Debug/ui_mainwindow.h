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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
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
    QPushButton *logoutButton;
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *matrielButton;
    QPushButton *employeButton;
    QPushButton *eventButton;
    QPushButton *sponsorButton;
    QPushButton *participantButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1323, 666);
        MainWindow->setStyleSheet(QString::fromUtf8("backgroundcolor:black"));
        MainWindow->setDocumentMode(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setGeometry(QRect(1220, 570, 90, 29));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(320, -150, 991, 411));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(140, 140, 971, 91));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        matrielButton = new QPushButton(layoutWidget);
        matrielButton->setObjectName("matrielButton");

        horizontalLayout->addWidget(matrielButton);

        employeButton = new QPushButton(layoutWidget);
        employeButton->setObjectName("employeButton");

        horizontalLayout->addWidget(employeButton);

        eventButton = new QPushButton(layoutWidget);
        eventButton->setObjectName("eventButton");

        horizontalLayout->addWidget(eventButton);

        sponsorButton = new QPushButton(layoutWidget);
        sponsorButton->setObjectName("sponsorButton");

        horizontalLayout->addWidget(sponsorButton);

        participantButton = new QPushButton(layoutWidget);
        participantButton->setObjectName("participantButton");

        horizontalLayout->addWidget(participantButton);

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
        logoutButton->setText(QCoreApplication::translate("MainWindow", "logout", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:72pt;\">                                                                                  sunny desk </span></p></body></html>", nullptr));
        matrielButton->setText(QCoreApplication::translate("MainWindow", "Matriel", nullptr));
        employeButton->setText(QCoreApplication::translate("MainWindow", "Employe", nullptr));
        eventButton->setText(QCoreApplication::translate("MainWindow", "event", nullptr));
        sponsorButton->setText(QCoreApplication::translate("MainWindow", "sponsor", nullptr));
        participantButton->setText(QCoreApplication::translate("MainWindow", "Participant", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
