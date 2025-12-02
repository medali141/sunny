/********************************************************************************
** Form generated from reading UI file 'chatbot.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATBOT_H
#define UI_CHATBOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatbot
{
public:

    void setupUi(QWidget *chatbot)
    {
        if (chatbot->objectName().isEmpty())
            chatbot->setObjectName("chatbot");
        chatbot->resize(1061, 450);

        retranslateUi(chatbot);

        QMetaObject::connectSlotsByName(chatbot);
    } // setupUi

    void retranslateUi(QWidget *chatbot)
    {
        chatbot->setWindowTitle(QCoreApplication::translate("chatbot", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatbot: public Ui_chatbot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATBOT_H
