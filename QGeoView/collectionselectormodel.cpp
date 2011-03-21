#include <iostream>
#include <QPointer>
#include "collectionselectormodel.h"

CollectionSelectorModel::CollectionSelectorModel(QSqlDatabase *db, bool all) :
    _db(db),
    _all(all)
{
    _collection = 0;
    _root = invisibleRootItem();
}

CollectionSelectorModel::~CollectionSelectorModel()
{
    if (_collection)
        delete _collection;
    if (_root)
        delete _root;
}

Collection *CollectionSelectorModel::collection()
{
    return QPointer<Collection>(new Collection(_db, _collection->getID()));
}

void CollectionSelectorModel::indexChanged(int index)
{
    int id = 0;
    if (index >= 0) // QComboBox will send -1 if the current item is removed.
        id = _root->child(index, 0)->data(Qt::UserRole).toInt();

    if (id > 0) {
        _collection = QPointer<Collection>(new Collection(_db, id));
        emit collectionSelected(id);
        return;
    }
    if (_all) {
        emit allSelected();
        return;
    }
    emit noneSelected();
}

void CollectionSelectorModel::refresh()
{
    // Clear existing collections
    _root->removeRows(0, _root->rowCount());

    // "All" selection
    if (_all) {
        QStandardItem *item = new QStandardItem("All");
        item->setData(0, Qt::UserRole);
        _root->appendRow(item);
    }

    // Repopulate collections
    QList<Collection*> collections = Collection::getAll(_db);
    QList<Collection*>::iterator i;
    for (i = collections.begin(); i != collections.end(); ++i) {
        Collection *collection = *i;
        QStandardItem *item = new QStandardItem(collection->summary());
        item->setData(collection->getID(), Qt::UserRole);
        _root->appendRow(item);
        delete collection;
    }
    emit refreshed();
}
