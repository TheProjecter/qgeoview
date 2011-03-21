/******************************************************************************
** Copyright 2010 Doug Penner
**
** This file is part of QGeoView.
**
** QGeoView is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QGeoView is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QGeoView.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include <iostream>
#include <QDateTime>

#include "mainwindow.h"
#include "collectioneditor_tab.h"
#include "db/collection.h"
#include "editcollectiondialog.h"

CollectionEditorTabPlugin::CollectionEditorTabPlugin(QSqlDatabase *db, QTabWidget *pluginsTabWidget) :
    TabPlugin(db, pluginsTabWidget)
{
    ui.setupUi(this);
    _collection_selector_model = new CollectionSelectorModel(db);
    _item_tree_model = new TreeModel(db);

    ui.selector->setModel(_collection_selector_model);

    ui.tree->setModel(_item_tree_model);
    _item_tree_model->refresh();
    ui.tree->expandAll();


    connect(ui.selector, SIGNAL(currentIndexChanged(int)), _collection_selector_model, SLOT(indexChanged(int)));
    connect(ui.tree, SIGNAL(clicked(QModelIndex)), _item_tree_model, SLOT(itemSelected(QModelIndex)));
    connect(_collection_selector_model, SIGNAL(collectionSelected(int)), _item_tree_model, SLOT(showCollection(int)));
    connect(_collection_selector_model, SIGNAL(allSelected()), _item_tree_model, SLOT(showAll()));
    connect(_collection_selector_model, SIGNAL(noneSelected()), _item_tree_model, SLOT(showNone()));
    connect(_collection_selector_model, SIGNAL(refreshed()), _item_tree_model, SLOT(refresh()));
    connect (_item_tree_model, SIGNAL(cacheDragged(int)), this, SLOT(cacheDragged(int)));
    connect (_item_tree_model, SIGNAL(waypointDragged(int)), this, SLOT(waypointDragged(int)));
    connect (_item_tree_model, SIGNAL(cacheDropped(int)), this, SLOT(cacheDropped(int)));
    connect (_item_tree_model, SIGNAL(waypointDropped(int)), this, SLOT(waypointDropped(int)));
    _collection_selector_model->refresh();
}

QString CollectionEditorTabPlugin::name()
{
    return "Collection Editor";
}

void CollectionEditorTabPlugin::refresh_collections()
{
    QList<Collection*> collections = Collection::getAll(_db);
    for (QList<Collection*>::iterator i=collections.begin(); i!=collections.end(); ++i) {
        ui.selector->addItem((*i)->summary(), (*i)->getID());
        delete (*i);
    }
}

void CollectionEditorTabPlugin::on_remove_selected_clicked()
{
    Collection *collection = _collection_selector_model->collection();
    if (!collection)
        return;
    foreach (QModelIndex index, ui.tree->selectionModel()->selectedIndexes()) {
        if (index.isValid() && index.parent().isValid())
            switch (index.parent().data(Qt::UserRole).toInt()) {
                case INFO_TYPE_CACHE:
                    collection->removeCache(index.data(Qt::UserRole).toInt());
                    break;
                case INFO_TYPE_WAYPOINT:
                    collection->removeWaypoint(index.data(Qt::UserRole).toInt());
                    break;
            }
    }
    _item_tree_model->refresh();
}

void CollectionEditorTabPlugin::on_edit_collection_clicked()
{
    std::cout << "Editing Existing Collection" << std::endl;
    EditCollectionDialog dialog(new Collection(_db, ui.selector->itemData(ui.selector->currentIndex(), Qt::UserRole).toInt()));
    dialog.exec();
    _collection_selector_model->refresh();
}

void CollectionEditorTabPlugin::on_delete_collection_clicked()
{
    Collection *collection = _collection_selector_model->collection();
    if (!collection)
        return;
    collection->remove();
    _collection_selector_model->refresh();
}

void CollectionEditorTabPlugin::on_new_collection_clicked()
{
    EditCollectionDialog dialog(_db);
    dialog.exec();
    _collection_selector_model->refresh();
}

void CollectionEditorTabPlugin::cacheDragged(int id)
{
    Collection *collection = _collection_selector_model->collection();
    if (collection)
        collection->removeCache(id);
}

void CollectionEditorTabPlugin::cacheDropped(int id)
{
    Collection *collection = _collection_selector_model->collection();
    if (collection)
        collection->addCache(id);
}

void CollectionEditorTabPlugin::waypointDropped(int id)
{
    Collection *collection = _collection_selector_model->collection();
    if (collection)
        collection->addWaypoint(id);
}


TabPlugin *CollectionEditorTabPluginFactory::get_plugin(QSqlDatabase *db, QTabWidget *pluginsTabWidget)
{
    return new CollectionEditorTabPlugin(db, pluginsTabWidget);
}

Q_EXPORT_PLUGIN2(collectioneditortabpluginfactory, CollectionEditorTabPluginFactory);
