/********************************************************************************
** Form generated from reading UI file 'matriel.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIEL_H
#define UI_MATRIEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Matriel
{
public:
    QPushButton *backButton;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *idMat;
    QLineEdit *nomMat;
    QLineEdit *Quantite;
    QLabel *label_4;
    QLineEdit *Dispo;
    QLineEdit *idMAT_Delete;
    QPushButton *rechID;
    QPushButton *ajoutMat;
    QLineEdit *recherch_id;
    QPushButton *afficherMar;
    QRadioButton *Rtri;
    QTableView *tabMAT;
    QPushButton *supprimerMat;
    QRadioButton *Rtri_2;
    QPushButton *modifierMat;

    void setupUi(QWidget *Matriel)
    {
        if (Matriel->objectName().isEmpty())
            Matriel->setObjectName("Matriel");
        Matriel->resize(1308, 661);
        backButton = new QPushButton(Matriel);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(1189, 598, 101, 41));
        groupBox = new QGroupBox(Matriel);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 30, 351, 271));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 33, 61, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 73, 61, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 61, 21));
        idMat = new QLineEdit(groupBox);
        idMat->setObjectName("idMat");
        idMat->setGeometry(QRect(140, 40, 121, 31));
        nomMat = new QLineEdit(groupBox);
        nomMat->setObjectName("nomMat");
        nomMat->setGeometry(QRect(140, 80, 121, 31));
        Quantite = new QLineEdit(groupBox);
        Quantite->setObjectName("Quantite");
        Quantite->setGeometry(QRect(140, 120, 121, 31));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 151, 91, 20));
        Dispo = new QLineEdit(groupBox);
        Dispo->setObjectName("Dispo");
        Dispo->setGeometry(QRect(140, 160, 121, 31));
        idMAT_Delete = new QLineEdit(Matriel);
        idMAT_Delete->setObjectName("idMAT_Delete");
        idMAT_Delete->setGeometry(QRect(30, 480, 131, 31));
        rechID = new QPushButton(Matriel);
        rechID->setObjectName("rechID");
        rechID->setGeometry(QRect(940, 470, 241, 61));
        ajoutMat = new QPushButton(Matriel);
        ajoutMat->setObjectName("ajoutMat");
        ajoutMat->setGeometry(QRect(50, 330, 131, 61));
        recherch_id = new QLineEdit(Matriel);
        recherch_id->setObjectName("recherch_id");
        recherch_id->setGeometry(QRect(800, 490, 131, 31));
        afficherMar = new QPushButton(Matriel);
        afficherMar->setObjectName("afficherMar");
        afficherMar->setGeometry(QRect(450, 460, 131, 61));
        Rtri = new QRadioButton(Matriel);
        Rtri->setObjectName("Rtri");
        Rtri->setGeometry(QRect(600, 480, 141, 25));
        tabMAT = new QTableView(Matriel);
        tabMAT->setObjectName("tabMAT");
        tabMAT->setGeometry(QRect(450, 50, 721, 401));
        supprimerMat = new QPushButton(Matriel);
        supprimerMat->setObjectName("supprimerMat");
        supprimerMat->setGeometry(QRect(190, 470, 131, 61));
        Rtri_2 = new QRadioButton(Matriel);
        Rtri_2->setObjectName("Rtri_2");
        Rtri_2->setGeometry(QRect(600, 500, 191, 25));
        modifierMat = new QPushButton(Matriel);
        modifierMat->setObjectName("modifierMat");
        modifierMat->setGeometry(QRect(200, 330, 131, 61));

        retranslateUi(Matriel);

        QMetaObject::connectSlotsByName(Matriel);
    } // setupUi

    void retranslateUi(QWidget *Matriel)
    {
        Matriel->setWindowTitle(QCoreApplication::translate("Matriel", "Form", nullptr));
        backButton->setText(QCoreApplication::translate("Matriel", "back", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Matriel", "Ajouter/Modifier un  Materiel", nullptr));
        label->setText(QCoreApplication::translate("Matriel", "idMAT", nullptr));
        label_2->setText(QCoreApplication::translate("Matriel", "nomMAT", nullptr));
        label_3->setText(QCoreApplication::translate("Matriel", "Quantite", nullptr));
        label_4->setText(QCoreApplication::translate("Matriel", "Disponibilite", nullptr));
        rechID->setText(QCoreApplication::translate("Matriel", "Rechercher par ID", nullptr));
        ajoutMat->setText(QCoreApplication::translate("Matriel", "Ajouter", nullptr));
        afficherMar->setText(QCoreApplication::translate("Matriel", "Affichage", nullptr));
        Rtri->setText(QCoreApplication::translate("Matriel", "tri par % Quantite", nullptr));
        supprimerMat->setText(QCoreApplication::translate("Matriel", "Supprimer", nullptr));
        Rtri_2->setText(QCoreApplication::translate("Matriel", "tri par % Nom Matricule ", nullptr));
        modifierMat->setText(QCoreApplication::translate("Matriel", "Modifier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Matriel: public Ui_Matriel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIEL_H
