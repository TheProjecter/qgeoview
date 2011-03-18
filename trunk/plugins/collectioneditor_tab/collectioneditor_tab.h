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


#ifndef COLLECTIONEDITOR_TAB_H
#define COLLECTIONEDITOR_TAB_H

#include <QObject>
#include <QMainWindow>

#include "tabplugin.h"
#include "ui_mainwidget.h"
#include "treemodel.h"
#include "collectionselectormodel.h"

class CollectionEditorTabPlugin : public TabPlugin
{
    Q_OBJECT
public:
    CollectionEditorTabPlugin(QSqlDatabase *db, QTabWidget *pluginsTabWindow);
    QString name();
public slots:
    void items_selection(QModelIndexList selection);
    void refresh_collections();
    void cacheDragged(int id);
    void waypointDragged(int id);
    void cacheDropped(int id);
    void waypointDropped(int id);
private slots:
    void open_description_link();
    void on_remove_selected_clicked();
    void on_edit_collection_clicked();
    void on_delete_collection_clicked();
    void on_new_collection_clicked();

private:
    Ui::MainWidget ui;
    CollectionSelectorModel *_collection_selector_model;
    TreeModel *_item_tree_model;
};

class CollectionEditorTabPluginFactory : public QObject, public TabPluginFactory
{
    Q_OBJECT
    Q_INTERFACES(TabPluginFactory)
public:
    TabPlugin *get_plugin(QSqlDatabase *db, QTabWidget *pluginsTabWindow);
};

#endif 
