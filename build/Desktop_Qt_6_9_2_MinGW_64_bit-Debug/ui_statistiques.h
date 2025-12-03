/********************************************************************************
** Form generated from reading UI file 'statistiques.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTIQUES_H
#define UI_STATISTIQUES_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Statistiques
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QChartView *chartView1;
    QHBoxLayout *horizontalLayout;
    QChartView *chartView2;
    QChartView *chartView3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *closeButton;

    void setupUi(QDialog *Statistiques)
    {
        if (Statistiques->objectName().isEmpty())
            Statistiques->setObjectName("Statistiques");
        Statistiques->resize(1000, 700);
        verticalLayout = new QVBoxLayout(Statistiques);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(Statistiques);
        titleLabel->setObjectName("titleLabel");

        verticalLayout->addWidget(titleLabel);

        chartView1 = new QChartView(Statistiques);
        chartView1->setObjectName("chartView1");
        chartView1->setMinimumSize(QSize(0, 200));

        verticalLayout->addWidget(chartView1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        chartView2 = new QChartView(Statistiques);
        chartView2->setObjectName("chartView2");
        chartView2->setMinimumSize(QSize(0, 200));

        horizontalLayout->addWidget(chartView2);

        chartView3 = new QChartView(Statistiques);
        chartView3->setObjectName("chartView3");
        chartView3->setMinimumSize(QSize(0, 200));

        horizontalLayout->addWidget(chartView3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        closeButton = new QPushButton(Statistiques);
        closeButton->setObjectName("closeButton");

        horizontalLayout_2->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Statistiques);
        QObject::connect(closeButton, &QPushButton::clicked, Statistiques, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(Statistiques);
    } // setupUi

    void retranslateUi(QDialog *Statistiques)
    {
        Statistiques->setWindowTitle(QCoreApplication::translate("Statistiques", "Statistiques des Sponsors", nullptr));
        titleLabel->setText(QCoreApplication::translate("Statistiques", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Statistiques des Sponsors</span></p></body></html>", nullptr));
        closeButton->setText(QCoreApplication::translate("Statistiques", "Fermer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Statistiques: public Ui_Statistiques {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTIQUES_H
