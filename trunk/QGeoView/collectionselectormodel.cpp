#include <iostream>
#include "collectionselectormodel.h"

CollectionSelectorModel::CollectionSelectorModel(QSqlDatabase *db, bool all) :
    _db(db),
    _collection(NULL),
    _root(invisibleRootItem()),
    _all(all)
{}

CollectionSelectorModel::~CollectionSelectorModel()
{
    if (_collection)
        delete _collection;
    if (_root)
        delete _root;
}

Collection *CollectionSelectorModel::collection() {
    return _collection;
}

void CollectionSelectorModel::indexChanged(int index)
{
    int id = 0;
    if (index < _ids.count()) {    // QComboBox will spit out -1 if the list is empty or something goes wrong
        id = _ids.at(index);
    }

    if (_collection) {
        delete _collection;
        _collection = NULL;
    }

    if (id) {
        _collection = new Collection(_db, id);
        emit collectionSelected(_collection);
    } else if (_all) {
        emit allSelected();
    } else {
        emit noneSelected();
    }
}

void CollectionSelectorModel::refresh()
{
    // Clear existing collections
    _root->removeRows(0, _root->rowCount());

    // "All" selection
    if (_all) {
        _root->appendRow(new QStandardItem("All"));
        _ids.append(0);
    }

    // Repopulate collections
    QList<Collection*> collections = Collection::getAll(_db);
    QList<Collection*>::iterator i;
    for (i = collections.begin(); i != collections.end(); ++i) {
        _ids.append((*i)->getID());
        _root->appendRow(new QStandardItem((*i)->summary()));
        delete (*i);
    }
    emit refreshed();
}
