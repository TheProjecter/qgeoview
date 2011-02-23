#include "treeitem.h"
#include "treemodel.h"
#include <iostream>

TreeModel::TreeModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    _rootItem = new TreeItem;
    *_rootItem << "Name";
    *_rootItem << "Description";
}

TreeModel::~TreeModel()
{
    delete _rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    } else {
        return _rootItem->columnCount();
    }
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return 0;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return _rootItem->data(section);
    }
    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }
    TreeItem* parentItem;
    if (!parent.isValid()) {
        parentItem = _rootItem;
    } else {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem *childItem = parentItem->child(row);
    if (childItem) {
        return createIndex(row, column, childItem);
    } else {
        return QModelIndex();
    }
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }
    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem* parentItem = childItem->parent();

    if (parentItem == _rootItem) {
        return QModelIndex();
    }
    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem* parentItem;
    if (parent.column() > 0) {
        return 0;
    }
    if (!parent.isValid()) {
        parentItem = _rootItem;
    } else {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }
    return parentItem->childCount();
}

void TreeModel::waypoint_added(int id)
{
}

void TreeModel::track_added(int id)
{
}

void TreeModel::route_added(int id)
{
}
