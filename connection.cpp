#include "connection.h"
#include <QDebug>

Connection::Connection()
{
}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    // Try direct connection string instead of DSN
    db.setDatabaseName("DRIVER={Oracle in XE};SERVER=localhost;PORT=1521;DATABASE=xe;UID=Rayensql;PWD=esprit25;");

    if (db.open())
    {
        test = true;
    }
    else
    {
        qDebug() << "Error:" << db.lastError().text();
    }
    return test;
}


