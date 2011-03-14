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

#include <QSqlQuery>
#include <iostream>
#include <QSqlError>
#include <QFileDialog>

#include "read_gpx.h"

ReadGpxPlugin::ReadGpxPlugin(Database *db) :
    ReadPlugin(db)
{
}

QString ReadGpxPlugin::name()
{
    return "GPX Reader";
}

void ReadGpxPlugin::open()
{
    QString filename = QFileDialog::getOpenFileName();
    if (filename.isNull())
        return;
    std::cout << "Opening: " << filename.toStdString() << std::endl;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }
    QDomDocument gpx_file;
    if (!gpx_file.setContent(&file)) {
        std::cerr << "Unusable file, not XML" << std::endl;
        file.close();
        return;
    }
    file.close();
    read(&gpx_file);
    emit done();
}

void ReadGpxPlugin::read(QDomDocument *doc)
{
    QSqlQuery query;
    QDomElement gpx_element = doc->documentElement();
    if (gpx_element.tagName() != "gpx")
    {
        std::cerr << "Not an XML file" << std::endl;
        return;
    }

    // read data
    QDomNodeList wpt_list = gpx_element.elementsByTagName("wpt");
    Point *p;
    Description *d;
    Waypoint *w;
    Cache *c;
    Log *l;
    for (int wpt_i = 0; wpt_i < wpt_list.count(); ++wpt_i)
    {
        QDomElement wpt_element = wpt_list.item(wpt_i).toElement();
        QDomElement cache_element = wpt_element.elementsByTagName("groundspeak:cache").item(0).toElement();
        QDomNode node;

        // Point
        p = new Point(_db);

        node = wpt_element.elementsByTagName("time").item(0).firstChild();
        if (!node.isNull())
            p->setQStringValue(NULLMASK_POINT_TIME, node.nodeValue());

        node = wpt_element.elementsByTagName("sym").item(0).firstChild();
        if (!node.isNull())
            p->setQStringValue(NULLMASK_POINT_SYMBOL, node.nodeValue());

        p->setFloatValue(NULLMASK_POINT_LATITUDE, wpt_element.attribute("lat").toDouble());

        p->setFloatValue(NULLMASK_POINT_LONGITUDE, wpt_element.attribute("lon").toDouble());

        p->save();

        // Description
        d = new Description(_db);

        node = wpt_element.elementsByTagName("name").item(0).firstChild();
        if (!node.isNull())
            d->setQStringValue(NULLMASK_DESCRIPTION_NAME, node.nodeValue());

        node = wpt_element.elementsByTagName("linkname").item(0).firstChild();
        if (!node.isNull())
            d->setQStringValue(NULLMASK_DESCRIPTION_LINKNAME, node.nodeValue());

        node = wpt_element.elementsByTagName("link").item(0).firstChild();
        if (!node.isNull())
            d->setQStringValue(NULLMASK_DESCRIPTION_LINKURL, node.nodeValue());

        node = wpt_element.elementsByTagName("type").item(0).firstChild();
        if (!node.isNull())
            d->setQStringValue(NULLMASK_DESCRIPTION_SOURCE, node.nodeValue());

        d->save();

        // Waypoint

        w = new Waypoint(_db);

        w->setIntValue(NULLMASK_WAYPOINT_POINT, p->getID());
        w->setIntValue(NULLMASK_WAYPOINT_DESCRIPTION, d->getID());
        w->save();

        // Cache

        c = new Cache(_db);

        c->setIntValue(NULLMASK_CACHE_WAYPOINT, w->getID());

        c->setQStringValue(NULLMASK_CACHE_NAME, cache_element.elementsByTagName("groundspeak:name").item(0).firstChild().nodeValue());
        c->setQStringValue(NULLMASK_CACHE_PLACEDBY, cache_element.elementsByTagName("groundspeak:placed_by").item(0).firstChild().nodeValue());

        node = cache_element.elementsByTagName("groundspeak:owner").item(0).firstChild();
        c->setQStringValue(NULLMASK_CACHE_OWNERNAME, node.nodeValue());
        c->setIntValue(NULLMASK_CACHE_OWNERID, node.toElement().attribute("id").toInt());
        c->setQStringValue(NULLMASK_CACHE_OWNERGUID, node.toElement().attribute("guid"));

        c->setQStringValue(NULLMASK_CACHE_TYPE, cache_element.elementsByTagName("groundspeak:type").item(0).firstChild().nodeValue());
        c->setQStringValue(NULLMASK_CACHE_CONTAINER, cache_element.elementsByTagName("groundspeak:container").item(0).firstChild().nodeValue());
        c->setFloatValue(NULLMASK_CACHE_DIFFICULTY, cache_element.elementsByTagName("groundspeak:difficulty").item(0).firstChild().nodeValue().toDouble());
        c->setFloatValue(NULLMASK_CACHE_TERRAIN, cache_element.elementsByTagName("groundspeak:terrain").item(0).firstChild().nodeValue().toDouble());
        c->setQStringValue(NULLMASK_CACHE_COUNTRY, cache_element.elementsByTagName("groundspeak:country").item(0).firstChild().nodeValue());
        c->setQStringValue(NULLMASK_CACHE_STATE, cache_element.elementsByTagName("groundspeak:state").item(0).firstChild().nodeValue());
        c->setQStringValue(NULLMASK_CACHE_SHORTDESCRIPTION, cache_element.elementsByTagName("groundspeak:short_description").item(0).firstChild().nodeValue());
        c->setBoolValue(NULLMASK_CACHE_SHORTDESCRIPTIONHTML, cache_element.elementsByTagName("groundspeak:short_description").item(0).firstChild().toElement().attribute("html", "False") == "True");
        c->setQStringValue(NULLMASK_CACHE_LONGDESCRIPTION, cache_element.elementsByTagName("groundspeak:long_description").item(0).firstChild().nodeValue());
        c->setBoolValue(NULLMASK_CACHE_LONGDESCRIPTIONHTML, cache_element.elementsByTagName("groundspeak:long_description").item(0).firstChild().toElement().attribute("html", "False") == "True");
        c->setQStringValue(NULLMASK_CACHE_ENCODEDHINTS, cache_element.elementsByTagName("groundspeak:encoded_hints").item(0).firstChild().nodeValue());

        c->save();


        // Logs

        QDomNodeList cache_log_list = cache_element.elementsByTagName("groundspeak:logs").item(0).toElement().elementsByTagName("groundspeak:log");
        for (int cache_log_i = 0; cache_log_i < cache_log_list.count(); ++cache_log_i)
        {
            QDomElement log_element = cache_log_list.item(cache_log_i).toElement();
            l = new Log(_db);
            l->setIntValue(NULLMASK_LOG_CACHE, c->getID());
            l->setFloatValue(NULLMASK_LOG_LATITUDE, log_element.attribute("lat").toDouble());
            l->setFloatValue(NULLMASK_LOG_LONGITUDE, log_element.attribute("lon").toDouble());
            l->setIntValue(NULLMASK_LOG_LOGID, log_element.attribute("id").toInt());
            l->setQStringValue(NULLMASK_LOG_LOGGUID, log_element.attribute("guid"));
            l->setQStringValue(NULLMASK_LOG_DATE, log_element.elementsByTagName("groundspeak:date").item(0).firstChild().nodeValue());
            l->setQStringValue(NULLMASK_LOG_TYPE, log_element.elementsByTagName("groundspeak:type").item(0).firstChild().nodeValue());

            node = log_element.elementsByTagName("groundspeak:finder").item(0).firstChild();
            l->setIntValue(NULLMASK_LOG_FINDERID, node.toElement().attribute("id").toInt());
            l->setQStringValue(NULLMASK_LOG_FINDERGUID, node.toElement().attribute("guid"));
            l->setQStringValue(NULLMASK_LOG_FINDERNAME, node.nodeValue());

            node = log_element.elementsByTagName("groundspeak:text").item(0).firstChild();
            l->setQStringValue(NULLMASK_LOG_TEXT, node.nodeValue());
            l->setBoolValue(NULLMASK_LOG_TEXTENCODED, node.toElement().attribute("encoded", "False") == "True");
            l->save();
            delete l;
        }
        delete c;
        delete w;
        delete d;
        delete p;
    }
}

/*
 * Converts an sql string to either a specified format, or null (QVariant())
 */
QVariant ReadGpxPlugin::child_value(QDomNodeList list, int format=0)
{
    if (list.size() == 0) {
        switch (format) {
            case DATABASE_DATATYPE_STRING:
                return QVariant::String;
            case DATABASE_DATATYPE_INT:
                return QVariant::Int;
            case DATABASE_DATATYPE_DOUBLE:
                return QVariant::Double;
        }
    } else {
        switch (format) {
            case DATABASE_DATATYPE_STRING:
                return list.item(0).firstChild().nodeValue();
            case DATABASE_DATATYPE_INT:
                return list.item(0).firstChild().nodeValue().toInt();
            case DATABASE_DATATYPE_DOUBLE:
                return list.item(0).firstChild().nodeValue().toDouble();
        }
    }
    std::cerr << "Invalid DATABASE_DATATYPE" << std::endl;
    return QVariant();
}

ReadPlugin *ReadGpxPluginFactory::get_plugin(Database *db)
{
    return new ReadGpxPlugin(db);
}

Q_EXPORT_PLUGIN2(readgpxpluginfactory, ReadGpxPluginFactory);
