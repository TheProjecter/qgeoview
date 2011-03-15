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


#ifndef DETAILS_TAB_H
#define DETAILS_TAB_H

#include <QObject>
#include <QTabWidget>

#include "tabplugin.h"
#include "ui_mainwidget.h"

class DetailsTabPlugin : public TabPlugin
{
    Q_OBJECT
public:
    DetailsTabPlugin(Database *db, QTabWidget *tabPluginsTab);
    QString name();
public slots:
    void cacheSelected(Cache cache);
    void waypointSelected(Waypoint waypoint);
    void logIndexSelected(int index);
private slots:
    void open_description_link();
private:
    void setCacheData(Cache *cache);
    void setDescriptionData(Description *details);
    void setPointData(Point *point);
    void setAccuracyData(Point *point);
    void setLogsData(QList<int> *logIDs);
    QString _link_url;
    Ui::MainWidget ui;
};

class DetailsTabPluginFactory : public QObject, public TabPluginFactory
{
    Q_OBJECT
    Q_INTERFACES(TabPluginFactory)
public:
    TabPlugin *get_plugin(Database *db, QTabWidget *pluginsTabWidget);
};

#endif 
