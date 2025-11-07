#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"
#include "login.h"
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test = c.createconnect();

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Database"),
                                 QObject::tr("Connection successful!"), QMessageBox::Ok);

        // Show login screen first
        Login loginWindow;
        loginWindow.show();

        return a.exec();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database"),
                              QObject::tr("Connection failed!"), QMessageBox::Cancel);
        return -1;  // exit application
    }
}
