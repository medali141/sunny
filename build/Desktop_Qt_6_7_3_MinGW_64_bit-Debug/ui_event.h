/********************************************************************************
** Form generated from reading UI file 'event.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENT_H
#define UI_EVENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Event
{
public:
    QLineEdit *recherch_id;
    QPushButton *rechID;
    QPushButton *afficherMar;
    QPushButton *backButton;
    QTableView *tabMAT;
    QPushButton *supprimerMat;
    QPushButton *modifierMat;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *idEvent;
    QLineEdit *nomEvent;
    QLineEdit *dateEvent;
    QLabel *label_4;
    QLineEdit *responsable;
    QLineEdit *statut;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *remarque;
    QPushButton *ajoutMat;
    QLineEdit *idMAT_Delete;

    void setupUi(QWidget *Event)
    {
        if (Event->objectName().isEmpty())
            Event->setObjectName("Event");
        Event->resize(1313, 667);
        recherch_id = new QLineEdit(Event);
        recherch_id->setObjectName("recherch_id");
        recherch_id->setGeometry(QRect(820, 500, 131, 31));
        rechID = new QPushButton(Event);
        rechID->setObjectName("rechID");
        rechID->setGeometry(QRect(960, 480, 131, 61));
        afficherMar = new QPushButton(Event);
        afficherMar->setObjectName("afficherMar");
        afficherMar->setGeometry(QRect(470, 470, 131, 61));
        backButton = new QPushButton(Event);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(1210, 570, 90, 29));
        tabMAT = new QTableView(Event);
        tabMAT->setObjectName("tabMAT");
        tabMAT->setGeometry(QRect(470, 60, 611, 401));
        supprimerMat = new QPushButton(Event);
        supprimerMat->setObjectName("supprimerMat");
        supprimerMat->setGeometry(QRect(210, 480, 131, 61));
        modifierMat = new QPushButton(Event);
        modifierMat->setObjectName("modifierMat");
        modifierMat->setGeometry(QRect(220, 340, 131, 61));
        groupBox = new QGroupBox(Event);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(50, 40, 351, 291));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 33, 91, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 73, 81, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 61, 21));
        idEvent = new QLineEdit(groupBox);
        idEvent->setObjectName("idEvent");
        idEvent->setGeometry(QRect(140, 40, 121, 31));
        nomEvent = new QLineEdit(groupBox);
        nomEvent->setObjectName("nomEvent");
        nomEvent->setGeometry(QRect(140, 80, 121, 31));
        dateEvent = new QLineEdit(groupBox);
        dateEvent->setObjectName("dateEvent");
        dateEvent->setGeometry(QRect(140, 120, 121, 31));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 160, 91, 20));
        responsable = new QLineEdit(groupBox);
        responsable->setObjectName("responsable");
        responsable->setGeometry(QRect(140, 160, 121, 31));
        statut = new QLineEdit(groupBox);
        statut->setObjectName("statut");
        statut->setGeometry(QRect(140, 199, 121, 31));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 210, 91, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 240, 91, 20));
        remarque = new QLineEdit(groupBox);
        remarque->setObjectName("remarque");
        remarque->setGeometry(QRect(140, 240, 121, 31));
        ajoutMat = new QPushButton(Event);
        ajoutMat->setObjectName("ajoutMat");
        ajoutMat->setGeometry(QRect(70, 340, 131, 61));
        idMAT_Delete = new QLineEdit(Event);
        idMAT_Delete->setObjectName("idMAT_Delete");
        idMAT_Delete->setGeometry(QRect(50, 490, 131, 31));

        retranslateUi(Event);

        QMetaObject::connectSlotsByName(Event);
    } // setupUi

    void retranslateUi(QWidget *Event)
    {
        Event->setWindowTitle(QCoreApplication::translate("Event", "Form", nullptr));
        rechID->setText(QCoreApplication::translate("Event", "Rechercher par ID", nullptr));
        afficherMar->setText(QCoreApplication::translate("Event", "Affichage", nullptr));
        backButton->setText(QCoreApplication::translate("Event", "back", nullptr));
        supprimerMat->setText(QCoreApplication::translate("Event", "Supprimer", nullptr));
        modifierMat->setText(QCoreApplication::translate("Event", "Modifier", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Event", "event", nullptr));
        label->setText(QCoreApplication::translate("Event", "id event", nullptr));
        label_2->setText(QCoreApplication::translate("Event", "nom event", nullptr));
        label_3->setText(QCoreApplication::translate("Event", "date", nullptr));
        label_4->setText(QCoreApplication::translate("Event", "responsable", nullptr));
        statut->setText(QString());
        label_5->setText(QCoreApplication::translate("Event", "satatue", nullptr));
        label_6->setText(QCoreApplication::translate("Event", "Remarque", nullptr));
        remarque->setText(QString());
        ajoutMat->setText(QCoreApplication::translate("Event", "Ajouter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Event: public Ui_Event {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENT_H
