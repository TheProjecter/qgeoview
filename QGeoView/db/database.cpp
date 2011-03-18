#include <iostream>
#include "database.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>


/*
 Opens the database and ensures that it is available.
*/
Database::Database(QString location, QObject *parent) :
    _db(QSqlDatabase::addDatabase("QSQLITE"))
{
    _db.setDatabaseName(location);
    if (_db.open()) {
        std::cout << "Connected" << std::endl;
    } else {
        std::cerr << "Error Connecting to Database: " << location.toStdString() << std::endl;
    }
}


/*
 Closes the database connection.
*/
Database::~Database()
{
    _db.close();
}

void Database::transaction()
{
    _db.transaction();
}

void Database::commit()
{
    _db.commit();
}
