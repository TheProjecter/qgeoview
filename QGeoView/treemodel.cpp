#include <iostream>
#include "treemodel.h"

TreeModel::TreeModel(Database *db, QObject *parent) :
    QStandardItemModel(parent),
    _db(db),
    _caches("Caches"),
    _waypoints("Waypoints"),
    _collection(NULL)
{
    // Caches
    _caches.setEditable(false);
    _caches.setData(QVariant::fromValue<int>(INFO_TYPE_CACHE), Qt::UserRole);
    appendRow(&_caches);

    // Waypoints
    _waypoints.setEditable(false);
    _waypoints.setData(QVariant::fromValue<int>(INFO_TYPE_WAYPOINT), Qt::UserRole);
    appendRow(&_waypoints);
}

TreeModel::~TreeModel()
{
    if (_collection)
        delete _collection;
}

Collection *TreeModel::collection() {
    return _collection;
}

int TreeModel::collectionID() {
    if (!_collection)
        return NULL;
    return _collection->getID();
}


void TreeModel::refresh(Collection *collection)
{
    // Caches
    _caches.removeRows(0, _caches.rowCount());
    QSqlQuery cachesQuery;
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
        _caches.appendRow(item);
    }

    // Waypoints
    _waypoints.removeRows(0, _waypoints.rowCount());
    QSqlQuery waypointsQuery;
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
        _waypoints.appendRow(item);
    }
}

void TreeModel::item_selected(QModelIndex index)
{
    QModelIndex parent = index.parent();
    if (!parent.isValid())
        return;
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
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);

    if (index.isValid())
        return defaultFlags | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    else
        return defaultFlags | Qt::ItemIsDropEnabled;
}

QStringList TreeModel::mimeTypes() const
{
    QStringList types;
    types << "data/QGeoViewItemIDs";
    return types;
}

Qt::DropActions TreeModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QMimeData *TreeModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes) {
        QModelIndex parent = index.parent();
        if (index.isValid() && parent.isValid()) { // index must be Valid and it must have a valid parent (otherwise it is a category, which is USELESS!)
            int type = parent.data(Qt::UserRole).value<int>();
            int id = index.data(Qt::UserRole).value<int>();
            std::cout << "Found " << type << " : " << id << std::endl;
            stream << type << id;   // Stream parent's data (which is the item's TYPE) and the item's data (which is it's DB id)
        }
    }
    mimeData->setData("data/QGeoViewItemIDs", encodedData);
    return mimeData;
}

bool TreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("data/QGeoViewItemIDs"))
        return false;

    QByteArray encodedData = data->data("data/QGeoViewItemIDs");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);

    while (!stream.atEnd()) {
        int type;
        int id;
        stream >> type >> id;
        QStandardItem *item;
        Cache *cache;
        Waypoint *waypoint;
        switch (type) {
            case INFO_TYPE_CACHE:
                cache = new Cache(_db, id);
                item = new QStandardItem(cache->summary());
                item->setEditable(false);
                item->setData(QVariant::fromValue<int>(id), Qt::UserRole);
                _caches.appendRow(item);
                emit cacheDropped(id);
                break;
            case INFO_TYPE_WAYPOINT:
                waypoint = new Waypoint(_db, id);
                item = new QStandardItem(waypoint->summary());
                item->setEditable(false);
                item->setData(QVariant::fromValue<int>(id), Qt::UserRole);
                _waypoints.appendRow(item);
                emit waypointDropped(id);
                break;
        }
    }
}
