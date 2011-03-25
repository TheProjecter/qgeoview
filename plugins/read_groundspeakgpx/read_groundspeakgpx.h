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

#ifndef READ_GROUNDSPEAKGPX_H
#define READ_GROUNDSPEAKGPX_H

#include <QDomNodeList>
#include <QObject>

#include "readplugin.h"
#include "db/point.h"
#include "db/description.h"
#include "db/waypoint.h"
#include "db/cache.h"
#include "db/log.h"

#define DATABASE_DATATYPE_STRING    1
#define DATABASE_DATATYPE_INT       2
#define DATABASE_DATATYPE_DOUBLE    3

class ReadGroundspeakGpxPlugin : public ReadPlugin {
    Q_OBJECT
public:
    ReadGroundspeakGpxPlugin(QSqlDatabase *db);
    QString name();
    void read(QDomDocument *doc);
signals:
    void pointRead(Point *point);
    void descriptionRead(Description *description);
    void waypointRead(Waypoint *waypoint);
    void cacheRead(Cache *cache);
    void done();
public slots:
    void open();
protected:
    QVariant child_value(QDomNodeList list, int format);
};

class ReadGroundspeakGpxPluginFactory : public QObject, public ReadPluginFactory
{
    Q_OBJECT
    Q_INTERFACES(ReadPluginFactory)
public:
    ReadPlugin *get_plugin(QSqlDatabase *db);
};

#endif
