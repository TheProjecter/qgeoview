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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QSettings>
#include <QMainWindow>
#include <QItemSelection>
#include <QSortFilterProxyModel>
#include <QDateTime>
#include <QDir>
#include <QModelIndexList>

#include "readplugin.h"
#include "writeplugin.h"
#include "tabplugin.h"
#include "db/cache.h"
#include "db/waypoint.h"
#include "treemodel.h"
#include "collectionselectormodel.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Quit_triggered();

signals:
    void quit();
    void collectionSelected(Collection *collection);
    void noCollectionSelected();

private:
    void firstRun();
    void loadPlugins();
    void loadReadPlugin(ReadPlugin *plugin);
    void loadWritePlugin(WritePlugin *plugin);
    void loadTabPlugin(TabPlugin *plugin);

    Ui::MainWindow *ui;
    QSettings *_settings;
    QSqlDatabase _db;
    QList<ReadPlugin*> _readPlugins;
    QList<WritePlugin*> _writePlugins;
    QList<TabPlugin*> _tabPlugins;
    TreeModel *_item_tree_model;
    CollectionSelectorModel *_collection_selector_model;
};

#endif // MAINWINDOW_H
