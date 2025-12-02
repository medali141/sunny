/********************************************************************************
** Form generated from reading UI file 'matriel.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIEL_H
#define UI_MATRIEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
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
    QLabel *label_5;
    QDateEdit *dateDernierEntretien;
    QLabel *label_6;
    QLineEdit *entretienFrequence;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *nbUtilisations;
    QLineEdit *nbUtilisationSM;
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
    QPushButton *exportPDFButton;
    QPushButton *affSTAT;
    QPushButton *btnMaintenance;

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
        groupBox->setGeometry(QRect(30, 30, 361, 371));
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
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 200, 151, 20));
        dateDernierEntretien = new QDateEdit(groupBox);
        dateDernierEntretien->setObjectName("dateDernierEntretien");
        dateDernierEntretien->setGeometry(QRect(150, 200, 110, 29));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 230, 151, 20));
        entretienFrequence = new QLineEdit(groupBox);
        entretienFrequence->setObjectName("entretienFrequence");
        entretienFrequence->setGeometry(QRect(130, 230, 113, 28));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 260, 151, 20));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 300, 151, 20));
        nbUtilisations = new QLineEdit(groupBox);
        nbUtilisations->setObjectName("nbUtilisations");
        nbUtilisations->setGeometry(QRect(120, 260, 113, 28));
        nbUtilisationSM = new QLineEdit(groupBox);
        nbUtilisationSM->setObjectName("nbUtilisationSM");
        nbUtilisationSM->setGeometry(QRect(110, 290, 113, 28));
        idMAT_Delete = new QLineEdit(Matriel);
        idMAT_Delete->setObjectName("idMAT_Delete");
        idMAT_Delete->setGeometry(QRect(30, 480, 131, 31));
        rechID = new QPushButton(Matriel);
        rechID->setObjectName("rechID");
        rechID->setGeometry(QRect(940, 470, 241, 61));
        ajoutMat = new QPushButton(Matriel);
        ajoutMat->setObjectName("ajoutMat");
        ajoutMat->setGeometry(QRect(40, 400, 131, 61));
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
        tabMAT->setGeometry(QRect(450, 50, 851, 401));
        supprimerMat = new QPushButton(Matriel);
        supprimerMat->setObjectName("supprimerMat");
        supprimerMat->setGeometry(QRect(190, 470, 131, 61));
        Rtri_2 = new QRadioButton(Matriel);
        Rtri_2->setObjectName("Rtri_2");
        Rtri_2->setGeometry(QRect(600, 500, 191, 25));
        modifierMat = new QPushButton(Matriel);
        modifierMat->setObjectName("modifierMat");
        modifierMat->setGeometry(QRect(200, 400, 131, 61));
        exportPDFButton = new QPushButton(Matriel);
        exportPDFButton->setObjectName("exportPDFButton");
        exportPDFButton->setGeometry(QRect(940, 540, 241, 61));
        affSTAT = new QPushButton(Matriel);
        affSTAT->setObjectName("affSTAT");
        affSTAT->setGeometry(QRect(680, 540, 241, 61));
        btnMaintenance = new QPushButton(Matriel);
        btnMaintenance->setObjectName("btnMaintenance");
        btnMaintenance->setGeometry(QRect(420, 540, 241, 61));

        retranslateUi(Matriel);

        QMetaObject::connectSlotsByName(Matriel);
    } // setupUi

    void retranslateUi(QWidget *Matriel)
    {
        Matriel->setWindowTitle(QCoreApplication::translate("Matriel", "Form", nullptr));
        backButton->setText(QCoreApplication::translate("Matriel", "back", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Matriel", "Ajouter/Modifier un  Matriel", nullptr));
        label->setText(QCoreApplication::translate("Matriel", "idMAT", nullptr));
        label_2->setText(QCoreApplication::translate("Matriel", "nomMAT", nullptr));
        label_3->setText(QCoreApplication::translate("Matriel", "Quantite", nullptr));
        label_4->setText(QCoreApplication::translate("Matriel", "Disponibilite", nullptr));
        label_5->setText(QCoreApplication::translate("Matriel", "Date dernier entretien", nullptr));
        label_6->setText(QCoreApplication::translate("Matriel", "freq dentretien", nullptr));
        label_7->setText(QCoreApplication::translate("Matriel", "nb utilisations", nullptr));
        label_8->setText(QCoreApplication::translate("Matriel", "nb utlis max", nullptr));
        nbUtilisations->setText(QString());
        nbUtilisationSM->setText(QString());
        rechID->setText(QCoreApplication::translate("Matriel", "Rechercher par ID", nullptr));
        ajoutMat->setText(QCoreApplication::translate("Matriel", "Ajouter", nullptr));
        afficherMar->setText(QCoreApplication::translate("Matriel", "Affichage", nullptr));
        Rtri->setText(QCoreApplication::translate("Matriel", "tri par % Quantite", nullptr));
        supprimerMat->setText(QCoreApplication::translate("Matriel", "Supprimer", nullptr));
        Rtri_2->setText(QCoreApplication::translate("Matriel", "tri par % Nom Matricule ", nullptr));
        modifierMat->setText(QCoreApplication::translate("Matriel", "Modifier", nullptr));
        exportPDFButton->setText(QCoreApplication::translate("Matriel", "Export to PDF", nullptr));
        affSTAT->setText(QCoreApplication::translate("Matriel", "afficher STAT", nullptr));
        btnMaintenance->setText(QCoreApplication::translate("Matriel", "V\303\251rifier la maintenance", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Matriel: public Ui_Matriel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIEL_H
