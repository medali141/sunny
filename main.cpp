#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include "mainwindow.h"
#include "login.h"
#include "connection.h"
#include <QPixmap>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Charger la feuille de style
    QFile styleFile(":/sunnydesk.qss");
    if (!styleFile.exists()) {
        styleFile.setFileName("C:\\Users\\med ali chihaoui\\Documents\\sunnyDesk\\sunnydesk.qss");
        // fallback si pas dans les ressources
    }
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        a.setStyleSheet(style);
        styleFile.close();
    }

    // Connexion à la base de données
    Connection c;
    bool test = c.createconnect();

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Database"),
                                 QObject::tr("Connection successful!"), QMessageBox::Ok);

        Login loginWindow;
        loginWindow.show();

        return a.exec();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database"),
                              QObject::tr("Connection failed!"), QMessageBox::Cancel);
        return -1;
    }
}
