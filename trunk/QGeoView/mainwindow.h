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

#include <QSettings>
#include <QMainWindow>
#include <QItemSelection>
#include <QSortFilterProxyModel>
#include <QDateTime>
#include <QDir>

#include "database.h"
#include "dummyplugin.h"
#include "readplugin.h"
#include "writeplugin.h"
#include "tabplugin.h"
#include "db/cache.h"
#include "db/waypoint.h"

#define INFO_TYPE_NONE      1
#define INFO_TYPE_CACHE     2
#define INFO_TYPE_WAYPOINT  3
#define INFO_TYPE_ROUTE     4
#define INFO_TYPE_TRACK     5

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    void firstRun();
    void openFile(QString filename);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    void loadPlugins();
    void loadDummyPlugin(DummyPlugin *plugin);
    void loadReadPlugin(ReadPlugin *plugin);
    void loadWritePlugin(WritePlugin *plugin);
    void loadTabPlugin(TabPlugin *plugin);
    Ui::MainWindow *ui;
    Database* _db;
    QSettings* _settings;
    QList<DummyPlugin*> _dummyPlugins;
    QList<ReadPlugin*> _readPlugins;
    QList<WritePlugin*> _writePlugins;
    QList<TabPlugin*> _tabPlugins;

private slots:
    void on_action_Quit_triggered();
    void on_action_Test_triggered();
    void refreshTree();
    void on_comboBox_activated(int index);
    void item_selected(QModelIndex index);
signals:
    void quit();
    void waypointSelected(Waypoint waypoint);
    void cacheSelected(Cache cache);
};

#endif // MAINWINDOW_H
