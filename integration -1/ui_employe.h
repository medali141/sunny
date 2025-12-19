/********************************************************************************
** Form generated from reading UI file 'employe.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYE_H
#define UI_EMPLOYE_H

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

class Ui_Employe
{
public:
    QPushButton *backButton;
    QPushButton *rechID;
    QTableView *tabMAT;
    QPushButton *modifierMat;
    QPushButton *supprimerMat;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *idE;
    QLineEdit *nom;
    QLineEdit *poste;
    QLabel *label_4;
    QLineEdit *email;
    QLineEdit *statut_dem;
    QLabel *label_5;
    QPushButton *afficherMar;
    QPushButton *ajoutMat;
    QLineEdit *recherch_id;
    QLineEdit *idMAT_Delete;
    QPushButton *statistiquesButton;
    QPushButton *exportPdfButton;
    QPushButton *assignationAutoButton;
    QPushButton *congesButton;

    void setupUi(QWidget *Employe)
    {
        if (Employe->objectName().isEmpty())
            Employe->setObjectName("Employe");
        Employe->resize(1317, 699);
        Employe->setStyleSheet(QString::fromUtf8("color:black\n"
""));
        backButton = new QPushButton(Employe);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(1210, 580, 90, 29));
        rechID = new QPushButton(Employe);
        rechID->setObjectName("rechID");
        rechID->setGeometry(QRect(960, 490, 131, 61));
        tabMAT = new QTableView(Employe);
        tabMAT->setObjectName("tabMAT");
        tabMAT->setGeometry(QRect(470, 70, 611, 401));
        modifierMat = new QPushButton(Employe);
        modifierMat->setObjectName("modifierMat");
        modifierMat->setGeometry(QRect(220, 350, 131, 61));
        supprimerMat = new QPushButton(Employe);
        supprimerMat->setObjectName("supprimerMat");
        supprimerMat->setGeometry(QRect(210, 490, 131, 61));
        groupBox = new QGroupBox(Employe);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(50, 50, 351, 271));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 33, 91, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 73, 61, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 61, 21));
        idE = new QLineEdit(groupBox);
        idE->setObjectName("idE");
        idE->setGeometry(QRect(140, 40, 141, 31));
        nom = new QLineEdit(groupBox);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(140, 80, 141, 31));
        poste = new QLineEdit(groupBox);
        poste->setObjectName("poste");
        poste->setGeometry(QRect(140, 120, 141, 31));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 151, 91, 20));
        email = new QLineEdit(groupBox);
        email->setObjectName("email");
        email->setGeometry(QRect(140, 160, 141, 31));
        statut_dem = new QLineEdit(groupBox);
        statut_dem->setObjectName("statut_dem");
        statut_dem->setGeometry(QRect(140, 210, 141, 31));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 210, 91, 20));
        afficherMar = new QPushButton(Employe);
        afficherMar->setObjectName("afficherMar");
        afficherMar->setGeometry(QRect(470, 480, 131, 61));
        ajoutMat = new QPushButton(Employe);
        ajoutMat->setObjectName("ajoutMat");
        ajoutMat->setGeometry(QRect(70, 350, 131, 61));
        recherch_id = new QLineEdit(Employe);
        recherch_id->setObjectName("recherch_id");
        recherch_id->setGeometry(QRect(820, 510, 131, 31));
        idMAT_Delete = new QLineEdit(Employe);
        idMAT_Delete->setObjectName("idMAT_Delete");
        idMAT_Delete->setGeometry(QRect(50, 500, 131, 31));

        statistiquesButton = new QPushButton(Employe);
        statistiquesButton->setObjectName("statistiquesButton");
        statistiquesButton->setGeometry(QRect(620, 480, 131, 61));
        exportPdfButton = new QPushButton(Employe);
        exportPdfButton->setObjectName("exportPdfButton");
        exportPdfButton->setGeometry(QRect(1110, 490, 131, 61));
        assignationAutoButton = new QPushButton(Employe);
        assignationAutoButton->setObjectName("assignationAutoButton");
        assignationAutoButton->setGeometry(QRect(1140, 90, 131, 61));
        congesButton = new QPushButton(Employe);
        congesButton->setObjectName("congesButton");
        congesButton->setGeometry(QRect(1140, 170, 131, 61));

        retranslateUi(Employe);

        QMetaObject::connectSlotsByName(Employe);
    } // setupUi

    void retranslateUi(QWidget *Employe)
    {
        Employe->setWindowTitle(QCoreApplication::translate("Employe", "Form", nullptr));
        backButton->setText(QCoreApplication::translate("Employe", "back", nullptr));
        rechID->setText(QCoreApplication::translate("Employe", "Rechercher par ID", nullptr));
        modifierMat->setText(QCoreApplication::translate("Employe", "Modifier", nullptr));
        supprimerMat->setText(QCoreApplication::translate("Employe", "Supprimer", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Employe", "Ajouter / Modidier un Employe(e)", nullptr));
        label->setText(QCoreApplication::translate("Employe", "Id Employe", nullptr));
        label_2->setText(QCoreApplication::translate("Employe", "Nom", nullptr));
        label_3->setText(QCoreApplication::translate("Employe", "Poste", nullptr));
        label_4->setText(QCoreApplication::translate("Employe", "Email", nullptr));
        statut_dem->setText(QString());
        label_5->setText(QCoreApplication::translate("Employe", "statut_dem", nullptr));
        afficherMar->setText(QCoreApplication::translate("Employe", "Affichage", nullptr));
        ajoutMat->setText(QCoreApplication::translate("Employe", "Ajouter", nullptr));
        statistiquesButton->setText(QCoreApplication::translate("Employe", "Statistique", nullptr));
        exportPdfButton->setText(QCoreApplication::translate("Employe", "Exporter en PDF", nullptr));
        assignationAutoButton->setText(QCoreApplication::translate("Employe", "Assignation Auto", nullptr));
        congesButton->setText(QCoreApplication::translate("Employe", "Gestion des Congés", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Employe: public Ui_Employe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYE_H
