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
    for (int wpt_i = 0; wpt_i < wpt_list.count(); ++wpt_i)
    {
        QDomElement wpt_element = wpt_list.item(wpt_i).toElement();
        QDomElement cache_element = wpt_element.elementsByTagName("groundspeak:cache").item(0).toElement();
        // Point
        p = new Point(_db);
        QDomNode node;

        node = wpt_element.elementsByTagName("time").item(0).firstChild();
        if (!node.isNull())
            p->setQStringValue(NULLMASK_TIME, node.nodeValue());
        
        node = wpt_element.elementsByTagName("ele").item(0).firstChild();
        if (!node.isNull())
            p->setFloatValue(NULLMASK_ELEVATION, node.nodeValue().toFloat());

        node = wpt_element.elementsByTagName("magvar").item(0).firstChild();
        if (!node.isNull())
            p->setFloatValue(NULLMASK_MAGNETICVARIATION, node.nodeValue().toFloat());

        node = wpt_element.elementsByTagName("geoidheight").item(0).firstChild();
        if (!node.isNull())
            p->setFloatValue(NULLMASK_GEOIDHEIGHT, node.nodeValue().toFloat());

        node = wpt_element.elementsByTagName("sym").item(0).firstChild();
        if (!node.isNull())
            p->setQStringValue(NULLMASK_SYMBOL, node.nodeValue());

        node = wpt_element.elementsByTagName("fix").item(0).firstChild();
        if (!node.isNull())
            p->setQStringValue(NULLMASK_FIX, node.nodeValue());

        node = wpt_element.elementsByTagName("sat").item(0).firstChild();
        if (!node.isNull())
            p->setIntValue(NULLMASK_SATELITES, node.nodeValue().toInt());

        node = wpt_element.elementsByTagName("hdop").item(0).firstChild();
        if (!node.isNull())
            p->setFloatValue(NULLMASK_HORIZONTALDOP, node.nodeValue().toFloat());

        node = wpt_element.elementsByTagName("vdop").item(0).firstChild();
        if (!node.isNull())
            p->setFloatValue(NULLMASK_VERTICALDOP, node.nodeValue().toFloat());

        node = wpt_element.elementsByTagName("pdop").item(0).firstChild();
        if (!node.isNull())
            p->setFloatValue(NULLMASK_POSITIONDOP, node.nodeValue().toFloat());

        node = wpt_element.elementsByTagName("ageofdgpsdata").item(0).firstChild();
        if (!node.isNull())
            p->setFloatValue(NULLMASK_AGEOFDGPSDATA, node.nodeValue().toFloat());

        node = wpt_element.elementsByTagName("dgpsid").item(0).firstChild();
        if (!node.isNull())
            p->setIntValue(NULLMASK_DGPSID, node.nodeValue().toInt());

        node = wpt_element.elementsByTagName("lat").item(0).firstChild();
        if (!node.isNull())
            p->setFloatValue(NULLMASK_LATITUDE, node.nodeValue().toFloat());

        node = wpt_element.elementsByTagName("lon").item(0).firstChild();
        if (!node.isNull())
            p->setFloatValue(NULLMASK_LONGITUDE, node.nodeValue().toFloat());
        p->save();

        /*
        // Description
        query.prepare("INSERT INTO Descriptions (name, link_url, link_name, comments, source, type) VALUES (?,?,?,?,?,?)");
        query.addBindValue(child_value(wpt_element.elementsByTagName("name"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("link"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("link"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("cmt"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("src"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("type"), DATABASE_DATATYPE_STRING));
        std::cout << "executing query 2" << std::endl;
        if (query.exec()) {
            std::cout << "query.exec() DONE" << std::endl;
        } else {
            std::cout << "query.exec() FAIL" << std::endl;
            std::cout << "ERROR Message: \"" << query.lastError().driverText().toStdString() << "\"" << std::endl;
            return;
        }
        description_id = query.lastInsertId().toInt();

        // Waypoint
        query.prepare("INSERT INTO Waypoints (description, point) VALUES(?,?)");
        query.addBindValue(description_id);
        query.addBindValue(point_id);
        std::cout << "executing query 3" << std::endl;
        if (query.exec()) {
            std::cout << "query.exec() DONE" << std::endl;
        } else {
            std::cout << "query.exec() FAIL" << std::endl;
            std::cout << "ERROR Message: \"" << query.lastError().driverText().toStdString() << "\"" << std::endl;
            return;
        }
        waypoint_id = query.lastInsertId().toInt();

        // Cache
        query.prepare("INSERT INTO Caches (name, placed_by, owner_id, owner_guid, owner_name, type, container, difficulty, terrain, country, state, short_description, short_description_html, long_description, long_description_html, encoded_hints, waypoint) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:name"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:placed_by"), DATABASE_DATATYPE_STRING));
        query.addBindValue(cache_element.elementsByTagName("groundspeak:owner").item(0).toElement().attribute("id"));
        query.addBindValue(cache_element.elementsByTagName("groundspeak:owner").item(0).toElement().attribute("guid"));
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:owner"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:type"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:container"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:difficulty"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:terrain"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:country"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:state"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:short_description"), DATABASE_DATATYPE_STRING));
        query.addBindValue(cache_element.elementsByTagName("groundspeak:short_description").item(0).toElement().attribute("html").toInt());
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:long_description"), DATABASE_DATATYPE_STRING));
        query.addBindValue(cache_element.elementsByTagName("groundspeak:long_description").item(0).toElement().attribute("html").toInt());
        query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:encoded_hints"), DATABASE_DATATYPE_STRING));
        query.addBindValue(waypoint_id);
        std::cout << "executing query 4" << std::endl;
        if (query.exec()) {
            std::cout << "query.exec() DONE" << std::endl;
        } else {
            std::cout << "query.exec() FAIL" << std::endl;
            std::cout << "ERROR Message: \"" << query.lastError().driverText().toStdString() << "\"" << std::endl;
            return;
        }
        cache_id = query.lastInsertId().toInt();

        QDomNodeList cache_log_list = cache_element.elementsByTagName("groundspeak:logs").item(0).toElement().elementsByTagName("groundspeak:log");
        for (int cache_log_i = 0; cache_log_i < cache_log_list.count(); ++cache_log_i)
        {
            QDomElement log_element = cache_log_list.item(cache_log_i).toElement();
            query.prepare("INSERT INTO Logs (log_id, log_guid, date, type, finder_id, finder_guid, finder_name, text, text_encoded, latitude, longitude, cache) VALUES (?,?,?,?,?,?,?,?,?,?,?,?)");
            query.addBindValue(cache_element.attribute("id"));
            query.addBindValue(cache_element.attribute("guid"));
            query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:date"), DATABASE_DATATYPE_STRING));
            query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:type"), DATABASE_DATATYPE_STRING));
            query.addBindValue(cache_element.elementsByTagName("groundspeak:finder").item(0).toElement().attribute("id"));
            query.addBindValue(cache_element.elementsByTagName("groundspeak:finder").item(0).toElement().attribute("guid"));
            query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:finder"), DATABASE_DATATYPE_STRING));
            query.addBindValue(child_value(wpt_element.elementsByTagName("groundspeak:text"), DATABASE_DATATYPE_STRING));
            query.addBindValue(cache_element.elementsByTagName("groundspeak:text").item(0).toElement().attribute("encoded").toInt());
            query.addBindValue(cache_element.attribute("lat"));
            query.addBindValue(cache_element.attribute("lon"));
            query.addBindValue(cache_id);
            std::cout << "executing query 5" << std::endl;
            if (query.exec()) {
                std::cout << "query.exec() DONE" << std::endl;
            } else {
                std::cout << "query.exec() FAIL" << std::endl;
                std::cout << "ERROR Message: \"" << query.lastError().driverText().toStdString() << "\"" << std::endl;
                return;
            }
        }
    */
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
