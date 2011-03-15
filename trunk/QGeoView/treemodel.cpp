#include "treemodel.h"

TreeModel::TreeModel(Database *db, QObject *parent) :
    QStandardItemModel(parent),
    _db(db)
{
}


void TreeModel::refresh(Collection *collection)
{
    QSqlQuery cachesQuery;
    clear();

    // Caches
    QStandardItem *caches = new QStandardItem("Caches");
    caches->setEditable(false);
    caches->setData(QVariant::fromValue<int>(INFO_TYPE_CACHE), Qt::UserRole);
    appendRow(caches);
    if (collection) {
        cachesQuery.prepare("SELECT id, " + Cache::fieldNames().join(", ") + " FROM Cache WHERE id IN (SELECT fk_cache FROM Cache2Collection WHERE fk_collection=?);");
        cachesQuery.addBindValue(collection->getID());
    } else {
        cachesQuery.prepare("SELECT id, " + Cache::fieldNames().join(", ") + " FROM Cache;");
    }
    if (!cachesQuery.exec())
        throw cachesQuery;
    while (cachesQuery.next()) {
        Cache cache(_db, cachesQuery);
        QStandardItem *item = new QStandardItem(cache.summary());
        item->setEditable(false);
        item->setData(QVariant::fromValue<int>(cache.getID()), Qt::UserRole);
        caches->appendRow(item);
    }

    QSqlQuery waypointsQuery;
    // Waypoints
    QStandardItem *waypoints = new QStandardItem("Waypoints");
    waypoints->setEditable(false);
    waypoints->setData(QVariant::fromValue<int>(INFO_TYPE_WAYPOINT), Qt::UserRole);
    appendRow(waypoints);

    if (collection) {
        waypointsQuery.prepare("SELECT id, " + Waypoint::fieldNames().join(", ") + " FROM Waypoint WHERE id NOT IN (SELECT fk_waypoint FROM Cache) AND id IN (SELECT fk_waypoint FROM Waypoint2Collection WHERE fk_collection=?);");
        waypointsQuery.addBindValue(collection->getID());
    } else
        waypointsQuery.prepare("SELECT id, " + Waypoint::fieldNames().join(", ") + " FROM Waypoint WHERE id NOT IN (SELECT fk_waypoint FROM Cache);");
    if (!waypointsQuery.exec())
        throw waypointsQuery;
    while (waypointsQuery.next()) {
        Waypoint waypoint(_db, waypointsQuery);
        QStandardItem *item = new QStandardItem(waypoint.summary());
        item->setEditable(false);
        item->setData(QVariant::fromValue<int>(waypoint.getID()), Qt::UserRole);
        waypoints->appendRow(item);
    }
}

void TreeModel::item_selected(QModelIndex index)
{
    QModelIndex parent = index.parent();
    if (parent.isValid()) {
        // Item
        int id = index.data(Qt::UserRole).value<int>();
        int category = parent.data(Qt::UserRole).value<int>();
        switch (category) {
            case INFO_TYPE_CACHE:
                emit cacheSelected(Cache(_db, id));
                break;
            case INFO_TYPE_WAYPOINT:
                emit waypointSelected(Waypoint(_db, id));
                break;
            default:
                throw InvalidTreeItemCategoryException(category);
        }
    } else {
        // Category
        // This can be later expanded in case something wants to know when a category is clicked.
        // int category = index.data(Qt::UserRole).value<int>();
    }
}
