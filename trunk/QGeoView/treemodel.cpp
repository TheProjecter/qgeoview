#include <iostream>
#include "treemodel.h"

TreeModel::TreeModel(QSqlDatabase *db, QObject *parent) :
    QStandardItemModel(parent),
    _db(db),
    _collection(NULL),
    _all(false),
    _caches("Caches"),
    _waypoints("Waypoints")
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

void TreeModel::showCollection(Collection *collection)
{
    if (_collection)
        delete _collection;
    _collection = collection;
    refresh();
}

void TreeModel::showNone()
{
    if (_collection) {
        delete _collection;
        _collection = NULL;
    }
    _all = false;
    refresh();
}

void TreeModel::showAll()
{
    if (_collection) {
        delete _collection;
        _collection = NULL;
    }
    _all = true;
    refresh();
}

void TreeModel::refresh()
{
    // Clear
    _caches.removeRows(0, _caches.rowCount());
    _waypoints.removeRows(0, _waypoints.rowCount());

    if (!_collection & !_all)   // if no collection and _all is false, show empty tree
        return;

    // Caches
    QList<Cache*> caches;
    if (_collection) {
        caches = _collection->caches();
    } else {
        caches = Cache::getAll(_db);
    }
    for (QList<Cache*>::iterator i=caches.begin(); i!=caches.end(); ++i) {
        QStandardItem *item = new QStandardItem((*i)->summary());
        item->setEditable(false);
        item->setData(QVariant::fromValue<int>((*i)->getID()), Qt::UserRole);
        delete (*i);
        _caches.appendRow(item);
    }

    // Waypoints
    QList<Waypoint*> waypoints;
    if (_collection) {
        waypoints = _collection->waypoints();
    } else {
        waypoints = Waypoint::getAll(_db);
    }

    for (QList<Waypoint*>::iterator i=waypoints.begin(); i!=waypoints.end(); ++i) {
        QStandardItem *item = new QStandardItem((*i)->summary());
        item->setEditable(false);
        item->setData(QVariant::fromValue<int>((*i)->getID()), Qt::UserRole);
        delete (*i);
        _waypoints.appendRow(item);
    }
}

void TreeModel::itemSelected(QModelIndex index)
{
    QModelIndex parent = index.parent();
    if (!parent.isValid())  // Only categories have no parents, those are useless to us.
        return;

    // Item
    int id = index.data(Qt::UserRole).value<int>();
    int category = parent.data(Qt::UserRole).value<int>();
    switch (category) {
        case INFO_TYPE_CACHE:
            emit cacheSelected(new Cache(_db, id));
            break;
        case INFO_TYPE_WAYPOINT:
            emit waypointSelected(new Waypoint(_db, id));
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
            stream << parent.data(Qt::UserRole).value<int>() << index.data(Qt::UserRole).value<int>();   // Stream parent's data (which is the item's TYPE) and the item's data (which is it's DB id)
        }
    }
    mimeData->setData("data/QGeoViewItemIDs", encodedData);
    return mimeData;
}

bool TreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(row)
    Q_UNUSED(column)
    Q_UNUSED(parent)
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
        switch (type) {
            case INFO_TYPE_CACHE:
                item = new QStandardItem(Cache(_db, id).summary());
                item->setEditable(false);
                item->setData(QVariant::fromValue<int>(id), Qt::UserRole);
                _caches.appendRow(item);
                emit cacheDropped(id);
                break;
            case INFO_TYPE_WAYPOINT:
                item = new QStandardItem(Waypoint(_db, id).summary());
                item->setEditable(false);
                item->setData(QVariant::fromValue<int>(id), Qt::UserRole);
                _waypoints.appendRow(item);
                emit waypointDropped(id);
                break;
        }
    }
    return true;
}
