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

#include <QMainWindow>
#include <QItemSelection>
#include <QSortFilterProxyModel>
#include "cachetable.h"
#include "../QMapControl/qmapcontrol.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    void openFile(QString filename);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QSortFilterProxyModel *_cacheTableProxy;
    CacheTable *_cacheTable;
    QDomDocument gpx_file;
    qmapcontrol::MapControl *_map;
    qmapcontrol::MapAdapter* _map_adapter;
    qmapcontrol::Layer* _map_mainlayer;

private slots:
    void on_actionSave_triggered();
    void on_action_Open_triggered();
    void on_actionTest_triggered();
    void on_action_Quit_triggered();

public slots:
    void view_row_selected(const QModelIndex & index);
    void cache_selected(Cache *cache);

signals:
    void row_selected(const QModelIndex & index);
    void cache_changed(Cache *);
    void cache_lat_changed(double);
    void cache_lon_changed(double);
    void cache_number_changed(QString);
    void cache_name_changed(QString);
    void cache_long_name_changed(QString);
    void cache_url_changed(QString);
    void cache_url_name_changed(QString);
    void cache_placed_by_changed(QString);
    void cache_owner_changed(QString);
    void cache_terrain_changed(double);
    void cache_type_changed(QString);
    void cache_container_changed(QString);
    void cache_difficulty_changed(double);
    void cache_desc_long_changed(QString);
    void cache_desc_long_html_changed(QString);
    void cache_desc_short_changed(QString);
    void cache_desc_short_html_changed(QString);
    void cache_hint_changed(QString);
    void quit();
};

#endif // MAINWINDOW_H
