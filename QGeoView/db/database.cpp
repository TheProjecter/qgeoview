#include <iostream>
#include "database.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include "treeitem.h"


/*
 Opens the database and ensures that it is available.
*/
Database::Database(QString location, QTreeView *tree, QObject *parent) :
    QObject(parent),
    _tree(tree)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
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

QList<int> Database::getCacheIDs()
{
    QList<int> ids;
    QSqlQuery query;
    QString query_string;
    query_string = "SELECT c.id FROM Cache c;";
    query.prepare(query_string);
    query.exec();
    while (query.next())
        ids.append(query.value(0).toInt());
    return ids;
}

QList<int> Database::getWaypointIDs(bool orphan)
{
    QList<int> ids;
    QSqlQuery query;
    QString query_string;
    if (orphan)
        query_string = "SELECT w.id FROM Waypoint w WHERE w.id not in (SELECT UNIQUE fk_cache from Cache);";
    else
        query_string = "SELECT w.id FROM Waypoint w;";
    query.prepare(query_string);
    query.exec();
    while (query.next())
        ids.append(query.value(0).toInt());
    return ids;
}
