#include "connection.h"

Connection::Connection()
{
    // Initialize the database connection name
    db = QSqlDatabase::addDatabase("QODBC");
}

bool Connection::createconnect()
{
    db.setDatabaseName("TNS Service Name");  // Replace with your actual ODBC source
    db.setUserName("rayensql");              // Username
    db.setPassword("esprit25");              // Password

    if (db.open())
        return true;
    else
        return false;
}

void Connection::closeConnection()
{
    if (db.isOpen())
        db.close();
}
