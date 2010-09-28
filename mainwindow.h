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
#include <QSqlQueryModel>
#include <QDomDocument>
#include <QDateTime>

#define INFO_TYPE_NONE      1
#define INFO_TYPE_WAYPOINT  2
#define INFO_TYPE_ROUTE     3
#define INFO_TYPE_TRACK     4

typedef struct {
    QDateTime datetime;
    QString type;
    QString poster;
    bool text_encoded;
    QString text;
} CacheLog;

typedef struct {
    QDomElement xmlElement;
    bool selected;
    double latitude;
    double longitude;
    QString number;
    QString name;
    QString long_name;
    QString url;
    QString url_name;
    QString placed_by;
    QString owner;
    float terrain;
    QString type;
    QString container;
    float difficulty;
    bool desc_short_html;
    QString desc_short;
    bool desc_long_html;
    QString desc_long;
    QString hint;
    QList<CacheLog*> logs;
} Cache;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    void openFile(QString filename);
    void infoType(int type);
    ~MainWindow();
    void openGPX(QDomDocument *doc);
    QDomDocument* genGPX(QList<Cache*> caches);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QSortFilterProxyModel *_cacheTableProxy;
    QDomDocument gpx_file;
    QSqlQueryModel* _db;

private slots:
    void on_actionSave_triggered();
    void on_action_Open_triggered();
    void on_actionTest_triggered();
    void on_action_Quit_triggered();

public slots:
    void view_row_selected(const QModelIndex & index);
    void activate_cache(Cache *cache);
    void MapSourceChanged(QString src);

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
    void new_cache(Cache* cache);
};

#endif // MAINWINDOW_H
