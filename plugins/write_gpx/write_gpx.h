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


#ifndef WRITE_GPX_H
#define WRITE_GPX_H

#include <QDomNodeList>
#include <QObject>
#include <QFile>

#include "writeplugin.h"
#include "db/point.h"
#include "db/description.h"
#include "db/waypoint.h"
#include "db/cache.h"
#include "db/collection.h"
#include "db/log.h"

class WriteGpxPlugin : public WritePlugin {
    Q_OBJECT
public:
    WriteGpxPlugin(QSqlDatabase *db);
    QString name();
    void write(QFile *file, int collection_id);
public slots:
    void save();
private:
    QDomElement cache2gpx(QDomDocument *doc, Cache *cache);
    QDomElement waypoint2gpx(QDomDocument *doc, Waypoint *waypoint);
    QList<QDomElement> point2gpx(QDomDocument *doc, Point *point);
    QList<QDomElement> description2gpx(QDomDocument *doc, Description *description);
    QDomElement createTextElement(QDomDocument *doc, QString name, QString value);
};

class WriteGpxPluginFactory : public QObject, public WritePluginFactory
{
    Q_OBJECT
    Q_INTERFACES(WritePluginFactory)
public:
    WritePlugin *get_plugin(QSqlDatabase *db);
};

#endif 
