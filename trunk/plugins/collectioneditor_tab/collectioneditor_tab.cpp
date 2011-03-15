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

CollectionEditorTabPlugin::CollectionEditorTabPlugin(Database *db, QTabWidget *pluginsTabWidget) :
    TabPlugin(db, pluginsTabWidget),
    _model(new TreeModel(db))
{
    ui.setupUi(this);
    ui.tree->setModel(_model);
    _model->refresh();
    refresh_collections();
    connect (_model, SIGNAL(cacheDragged(int)), this, SLOT(cacheDragged(int)));
    connect (_model, SIGNAL(waypointDragged(int)), this, SLOT(waypointDragged(int)));
    connect (_model, SIGNAL(cacheDropped(int)), this, SLOT(cacheDropped(int)));
    connect (_model, SIGNAL(waypointDropped(int)), this, SLOT(waypointDropped(int)));
}

QString CollectionEditorTabPlugin::name()
{
    return "Collection Editor";
}

void CollectionEditorTabPlugin::items_selection(QModelIndexList selection)
{

}

void CollectionEditorTabPlugin::refresh_collections()
{
    QSqlQuery query;
    query.prepare("SELECT id, name, description FROM COLLECTION;");
    if (!query.exec())
        throw query;
    Collection *collection;
    while (query.next()) {
        collection = new Collection(_db, query);
        ui.selector->addItem(collection->summary(), collection->getID());
        delete collection;
    }
}

void CollectionEditorTabPlugin::on_remove_selected_clicked()
{
    int type;
    int id;
    int collection_id;
    QModelIndex parent;
    Collection *collection = _model->collection();
    foreach (QModelIndex index, ui.tree->selectionModel()->selectedIndexes()) {
        parent = index.parent();
        if (index.isValid() && parent.isValid()) {
            type = parent.data(Qt::UserRole).value<int>();
            id = index.data(Qt::UserRole).value<int>();
            switch (type) {
                case INFO_TYPE_CACHE:
                    collection->removeCache(id);
                    break;
                case INFO_TYPE_WAYPOINT:
                    collection->removeWaypoint(id);
                    break;
            }
        }
    }
    _model->refresh();
}

void CollectionEditorTabPlugin::on_edit_collection_clicked()
{
    std::cout << "Editing Existing Collection" << std::endl;
    EditCollectionDialog dialog(_db, Collection(_db, ui.selector->itemData(ui.selector->currentIndex(), Qt::UserRole).toInt()));
    dialog.exec();
}

void CollectionEditorTabPlugin::on_delete_collection_clicked()
{
    foreach (QModelIndex index, ui.tree->selectionModel()->selectedIndexes()) {
        if (index.isValid() && index.parent().isValid())
            switch (index.parent().data(Qt::UserRole).toInt()) {
                case INFO_TYPE_CACHE:
                    Collection(_db, ui.selector->itemData(ui.selector->currentIndex(), Qt::UserRole).toInt()).removeCache(index.data(Qt::UserRole).toInt());
                    break;
                case INFO_TYPE_WAYPOINT:
                    Collection(_db, ui.selector->itemData(ui.selector->currentIndex(), Qt::UserRole).toInt()).removeWaypoint(index.data(Qt::UserRole).toInt());
                    break;
            }
    }
    _model->refresh();
}

void CollectionEditorTabPlugin::on_new_collection_clicked()
{
    EditCollectionDialog dialog(_db);
    dialog.exec();
}
void CollectionEditorTabPlugin::collectionIndexChanged(int index)
{
    QVariant qv = ui.selector->itemData(index, Qt::UserRole);
    if (qv.isValid() && qv.toInt() > 0) {
    Collection collection(_db, qv.toInt());
    _model->refresh(&collection);
    } else {
        _model->refresh();
    }
}

void CollectionEditorTabPlugin::cacheDragged(int id)
{
    Collection(_db, ui.selector->itemData(ui.selector->currentIndex(), Qt::UserRole).toInt()).removeCache(id);
}

void CollectionEditorTabPlugin::waypointDragged(int id)
{
    Collection(_db, ui.selector->itemData(ui.selector->currentIndex(), Qt::UserRole).toInt()).removeWaypoint(id);
}

void CollectionEditorTabPlugin::cacheDropped(int id)
{
    Collection(_db, ui.selector->itemData(ui.selector->currentIndex(), Qt::UserRole).toInt()).addCache(id);
}

void CollectionEditorTabPlugin::waypointDropped(int id)
{
    Collection(_db, ui.selector->itemData(ui.selector->currentIndex(), Qt::UserRole).toInt()).addWaypoint(id);
}



TabPlugin *CollectionEditorTabPluginFactory::get_plugin(Database *db, QTabWidget *pluginsTabWidget)
{
    return new CollectionEditorTabPlugin(db, pluginsTabWidget);
}

Q_EXPORT_PLUGIN2(collectioneditortabpluginfactory, CollectionEditorTabPluginFactory);


void CollectionEditorTabPlugin::on_selector_currentIndexChanged(int index)
{

}
