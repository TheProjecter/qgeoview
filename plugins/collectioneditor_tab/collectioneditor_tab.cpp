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
    TabPlugin(db, pluginsTabWidget)
{
    ui.setupUi(this);
    refresh_collections();
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

void CollectionEditorTabPlugin::on_edit_button_clicked()
{
    std::cout << "Editing Existing Collection" << std::endl;
    EditCollectionDialog dialog(_db, Collection(_db, ui.selector->itemData(ui.selector->currentIndex(), Qt::UserRole).toInt()));
    dialog.exec();
}

void CollectionEditorTabPlugin::on_new_button_clicked()
{
    EditCollectionDialog dialog(_db);
    dialog.exec();
}

void CollectionEditorTabPlugin::on_delete_button_clicked()
{
    Collection(_db, ui.selector->itemData(ui.selector->currentIndex(), Qt::UserRole).toInt()).remove();
}


TabPlugin *CollectionEditorTabPluginFactory::get_plugin(Database *db, QTabWidget *pluginsTabWidget)
{
    return new CollectionEditorTabPlugin(db, pluginsTabWidget);
}

Q_EXPORT_PLUGIN2(collectioneditortabpluginfactory, CollectionEditorTabPluginFactory);


void CollectionEditorTabPlugin::on_selector_currentIndexChanged(int index)
{

}
