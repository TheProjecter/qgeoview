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
    populate();
}


/*
 Closes the database connection.
*/
Database::~Database()
{
    _db.close();
}


/*
 Populates the list
*/
void Database::populate(int collection_id)
{
    QSqlQuery *query;
    // Caches
    if (collection_id < 0) {
        std::cout << "selecting all" << std::endl;
        query = new QSqlQuery("SELECT Caches.id, Caches.name from Caches");
    } else {
        std::cout << "selecting from collection" << std::endl;
        query = new QSqlQuery("SELECT Caches.id, Caches.name from Caches where c.id in (SELECT CachesInCollections.cache FROM CachesInCollections where CachesInCollections.id=?)");
        query->addBindValue(collection_id);
    }
    _tree->setSortingEnabled(1);
    std::cout << "Now Adding " << query->size() << "items" << std::endl;
    std::cerr << "Possible Driver Error: " << query->lastError().driverText().toStdString() << std::endl;
    std::cerr << "Possible Database Error: " << query->lastError().databaseText().toStdString() << std::endl;
    while (query->next()) {
        // TODO: Add Item To Tree
        // std::cout << "Added " << item->text().toStdString() << std::endl;
    }
    // waypoints TODO: finish
    if (collection_id < 0) {
        query = new QSqlQuery("SELECT w.id, d.name from Waypoints w INNER JOIN Descriptions d ON w.description = d.id");
    } else {
        query = new QSqlQuery("SELECT w.id, d.name from Waypoints w INNER JOIN Descriptions d ON w.description = d.id where w.id in (SELECT wc.waypoint FROM WaypointCollections wc where id=?)");
        query->addBindValue(collection_id);
    }
    delete query;
}

void Database::transaction()
{
    _db.transaction();
}

void Database::commit()
{
    _db.commit();
}
