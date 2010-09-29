#include <iostream>
#include "database.h"

Database::Database(QString location, QObject *parent) :
    QObject(parent)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(location);
    if (_db.open()) {
        std::cout << "Connected" << std::endl;
    } else {
        std::cerr << "Error Connecting to Database: " << location.toStdString() << std::endl;
    }
}

Database::~Database()
{

}
