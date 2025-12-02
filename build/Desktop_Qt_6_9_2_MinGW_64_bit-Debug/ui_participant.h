/********************************************************************************
** Form generated from reading UI file 'participant.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTICIPANT_H
#define UI_PARTICIPANT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Participant
{
public:
    QPushButton *rechID;
    QTableView *tabMAT;
    QPushButton *supprimerMat;
    QLineEdit *recherch_id;
    QPushButton *ajoutMat;
    QPushButton *modifierMat;
    QPushButton *afficherMar;
    QLineEdit *idMAT_Delete;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *idPar;
    QLineEdit *nom;
    QLineEdit *pre;
    QLabel *label_4;
    QLineEdit *age;
    QLineEdit *emai;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboBox;
    QLineEdit *tel;
    QLabel *label_7;
    QPushButton *backButton;

    void setupUi(QWidget *Participant)
    {
        if (Participant->objectName().isEmpty())
            Participant->setObjectName("Participant");
        Participant->resize(1323, 662);
        rechID = new QPushButton(Participant);
        rechID->setObjectName("rechID");
        rechID->setGeometry(QRect(970, 490, 131, 61));
        tabMAT = new QTableView(Participant);
        tabMAT->setObjectName("tabMAT");
        tabMAT->setGeometry(QRect(480, 70, 611, 401));
        supprimerMat = new QPushButton(Participant);
        supprimerMat->setObjectName("supprimerMat");
        supprimerMat->setGeometry(QRect(220, 490, 131, 61));
        recherch_id = new QLineEdit(Participant);
        recherch_id->setObjectName("recherch_id");
        recherch_id->setGeometry(QRect(830, 510, 131, 31));
        ajoutMat = new QPushButton(Participant);
        ajoutMat->setObjectName("ajoutMat");
        ajoutMat->setGeometry(QRect(80, 350, 131, 61));
        modifierMat = new QPushButton(Participant);
        modifierMat->setObjectName("modifierMat");
        modifierMat->setGeometry(QRect(230, 350, 131, 61));
        afficherMar = new QPushButton(Participant);
        afficherMar->setObjectName("afficherMar");
        afficherMar->setGeometry(QRect(480, 480, 131, 61));
        idMAT_Delete = new QLineEdit(Participant);
        idMAT_Delete->setObjectName("idMAT_Delete");
        idMAT_Delete->setGeometry(QRect(60, 500, 131, 31));
        groupBox = new QGroupBox(Participant);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(60, 50, 351, 271));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 33, 91, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 73, 81, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 61, 21));
        idPar = new QLineEdit(groupBox);
        idPar->setObjectName("idPar");
        idPar->setGeometry(QRect(140, 40, 113, 20));
        nom = new QLineEdit(groupBox);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(140, 80, 113, 20));
        pre = new QLineEdit(groupBox);
        pre->setObjectName("pre");
        pre->setGeometry(QRect(140, 120, 113, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 150, 91, 20));
        age = new QLineEdit(groupBox);
        age->setObjectName("age");
        age->setGeometry(QRect(140, 150, 113, 20));
        emai = new QLineEdit(groupBox);
        emai->setObjectName("emai");
        emai->setGeometry(QRect(140, 180, 113, 20));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 180, 91, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 230, 91, 20));
        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(140, 230, 82, 28));
        tel = new QLineEdit(groupBox);
        tel->setObjectName("tel");
        tel->setGeometry(QRect(140, 200, 113, 20));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 200, 91, 20));
        backButton = new QPushButton(Participant);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(1220, 580, 90, 29));

        retranslateUi(Participant);

        QMetaObject::connectSlotsByName(Participant);
    } // setupUi

    void retranslateUi(QWidget *Participant)
    {
        Participant->setWindowTitle(QCoreApplication::translate("Participant", "Form", nullptr));
        rechID->setText(QCoreApplication::translate("Participant", "Rechercher par ID", nullptr));
        supprimerMat->setText(QCoreApplication::translate("Participant", "Supprimer", nullptr));
        ajoutMat->setText(QCoreApplication::translate("Participant", "Ajouter", nullptr));
        modifierMat->setText(QCoreApplication::translate("Participant", "Modifier", nullptr));
        afficherMar->setText(QCoreApplication::translate("Participant", "Affichage", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Participant", "Ajouter / Modidier un Participant", nullptr));
        label->setText(QCoreApplication::translate("Participant", "id participant", nullptr));
        label_2->setText(QCoreApplication::translate("Participant", "nom", nullptr));
        label_3->setText(QCoreApplication::translate("Participant", "prenom", nullptr));
        label_4->setText(QCoreApplication::translate("Participant", "age", nullptr));
        emai->setText(QString());
        label_5->setText(QCoreApplication::translate("Participant", "email", nullptr));
        label_6->setText(QCoreApplication::translate("Participant", "type", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Participant", "1", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Participant", "2", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Participant", "3", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Participant", "4", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Participant", "5", nullptr));

        tel->setText(QString());
        label_7->setText(QCoreApplication::translate("Participant", "tel", nullptr));
        backButton->setText(QCoreApplication::translate("Participant", "back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Participant: public Ui_Participant {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTICIPANT_H
