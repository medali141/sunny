/********************************************************************************
** Form generated from reading UI file 'sponsor.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPONSOR_H
#define UI_SPONSOR_H

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

class Ui_Sponsor
{
public:
    QPushButton *backButton;
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
    QLineEdit *idSponsor;
    QLineEdit *nom;
    QLineEdit *prcnt;
    QLabel *label_4;
    QComboBox *comboBox;
    QLineEdit *dest;
    QPushButton *send_mail;
    QLabel *label_5;
    QPushButton *stat;
    QPushButton *Qrcode;
    QLineEdit *IDEMAIL;
    QPushButton *pdf;

    void setupUi(QWidget *Sponsor)
    {
        if (Sponsor->objectName().isEmpty())
            Sponsor->setObjectName("Sponsor");
        Sponsor->resize(1319, 665);
        backButton = new QPushButton(Sponsor);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(1220, 620, 90, 29));
        rechID = new QPushButton(Sponsor);
        rechID->setObjectName("rechID");
        rechID->setGeometry(QRect(860, 20, 201, 41));
        tabMAT = new QTableView(Sponsor);
        tabMAT->setObjectName("tabMAT");
        tabMAT->setGeometry(QRect(480, 80, 611, 401));
        supprimerMat = new QPushButton(Sponsor);
        supprimerMat->setObjectName("supprimerMat");
        supprimerMat->setGeometry(QRect(230, 460, 131, 61));
        recherch_id = new QLineEdit(Sponsor);
        recherch_id->setObjectName("recherch_id");
        recherch_id->setGeometry(QRect(660, 30, 131, 31));
        ajoutMat = new QPushButton(Sponsor);
        ajoutMat->setObjectName("ajoutMat");
        ajoutMat->setGeometry(QRect(90, 320, 131, 61));
        modifierMat = new QPushButton(Sponsor);
        modifierMat->setObjectName("modifierMat");
        modifierMat->setGeometry(QRect(230, 320, 131, 61));
        afficherMar = new QPushButton(Sponsor);
        afficherMar->setObjectName("afficherMar");
        afficherMar->setGeometry(QRect(230, 390, 131, 61));
        idMAT_Delete = new QLineEdit(Sponsor);
        idMAT_Delete->setObjectName("idMAT_Delete");
        idMAT_Delete->setGeometry(QRect(80, 470, 131, 31));
        groupBox = new QGroupBox(Sponsor);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(90, 30, 351, 271));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 33, 91, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 73, 81, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 61, 21));
        idSponsor = new QLineEdit(groupBox);
        idSponsor->setObjectName("idSponsor");
        idSponsor->setGeometry(QRect(140, 40, 113, 20));
        nom = new QLineEdit(groupBox);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(140, 80, 113, 20));
        prcnt = new QLineEdit(groupBox);
        prcnt->setObjectName("prcnt");
        prcnt->setGeometry(QRect(130, 160, 113, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 160, 91, 20));
        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(140, 110, 82, 28));
        dest = new QLineEdit(Sponsor);
        dest->setObjectName("dest");
        dest->setGeometry(QRect(1110, 110, 181, 31));
        send_mail = new QPushButton(Sponsor);
        send_mail->setObjectName("send_mail");
        send_mail->setGeometry(QRect(1120, 160, 131, 61));
        label_5 = new QLabel(Sponsor);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(530, 510, 161, 141));
        stat = new QPushButton(Sponsor);
        stat->setObjectName("stat");
        stat->setGeometry(QRect(90, 530, 131, 61));
        Qrcode = new QPushButton(Sponsor);
        Qrcode->setObjectName("Qrcode");
        Qrcode->setGeometry(QRect(790, 550, 131, 61));
        IDEMAIL = new QLineEdit(Sponsor);
        IDEMAIL->setObjectName("IDEMAIL");
        IDEMAIL->setGeometry(QRect(1120, 70, 151, 28));
        pdf = new QPushButton(Sponsor);
        pdf->setObjectName("pdf");
        pdf->setGeometry(QRect(970, 550, 131, 61));

        retranslateUi(Sponsor);

        QMetaObject::connectSlotsByName(Sponsor);
    } // setupUi

    void retranslateUi(QWidget *Sponsor)
    {
        Sponsor->setWindowTitle(QCoreApplication::translate("Sponsor", "Form", nullptr));
        backButton->setText(QCoreApplication::translate("Sponsor", "back", nullptr));
        rechID->setText(QCoreApplication::translate("Sponsor", "Rechercher par ID", nullptr));
        supprimerMat->setText(QCoreApplication::translate("Sponsor", "Supprimer", nullptr));
        ajoutMat->setText(QCoreApplication::translate("Sponsor", "Ajouter", nullptr));
        modifierMat->setText(QCoreApplication::translate("Sponsor", "Modifier", nullptr));
        afficherMar->setText(QCoreApplication::translate("Sponsor", "Affichage", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Sponsor", "Ajouter / Modidier un Sponsor", nullptr));
        label->setText(QCoreApplication::translate("Sponsor", "is sponsor", nullptr));
        label_2->setText(QCoreApplication::translate("Sponsor", "nom", nullptr));
        label_3->setText(QCoreApplication::translate("Sponsor", "niveau", nullptr));
        label_4->setText(QCoreApplication::translate("Sponsor", "pourcentage", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Sponsor", "1", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Sponsor", "2", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Sponsor", "3", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Sponsor", "4", nullptr));

        dest->setPlaceholderText(QCoreApplication::translate("Sponsor", "@ destinataire", nullptr));
        send_mail->setText(QCoreApplication::translate("Sponsor", "Rappeler ", nullptr));
        label_5->setText(QString());
        stat->setText(QCoreApplication::translate("Sponsor", "Statistiques", nullptr));
        Qrcode->setText(QCoreApplication::translate("Sponsor", "Qrcode", nullptr));
        IDEMAIL->setPlaceholderText(QCoreApplication::translate("Sponsor", "ID", nullptr));
        pdf->setText(QCoreApplication::translate("Sponsor", "PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sponsor: public Ui_Sponsor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPONSOR_H
