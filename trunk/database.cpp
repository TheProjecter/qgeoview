#include <iostream>
#include <QDomDocument>
#include "database.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

Database::Database(QString location, QObject *parent) :
    QObject(parent)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(location);
    if (_db.open()) {
        std::cout << "Connected" << std::endl;
    } else {
        std::cerr << "Error Connecting to Database: " << location.toStdString() << std::endl;
    }
}

Database::~Database()
{
    _db.close();
}

bool Database::import_gpx(QFile *file)
{
    QDomDocument doc;
    QSqlQuery query;
    if (!doc.setContent(file)) {
        std::cerr << "Unusable GPX file" << std::endl;
        return false;
    }
    QDomElement gpx_element = doc.documentElement();
    if (gpx_element.tagName() != "gpx")
    {
        std::cerr << "Not an XML file" << std::endl;
        return false;
    }

    // read data
    QDomNodeList wpt_list = gpx_element.elementsByTagName("wpt");
    int point_id, cache_id, waypoint_id, description_id;
    for (int wpt_i = 0; wpt_i < wpt_list.count(); ++wpt_i)
    {
        QDomElement wpt_element = wpt_list.item(wpt_i).toElement();
        QDomElement cache_element = wpt_element.elementsByTagName("groundspeak:cache").item(0).toElement();
        // Point
        query.prepare("INSERT INTO Points (time, elevation, magneticVariation, geoIDHeight, symbox, fix, statelites, horizontalDOP, verticalDOP, positionDOP, ageofDGPSData, DGPSID, latitude, longitude) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(wpt_element.elementsByTagName("time").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("ele").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("magvar").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("geoidheight").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("sym").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("fix").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("sat").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("hdop").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("vdop").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("pdop").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("ageofdgpsdata").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("dgpsid").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.attribute("lat").toDouble());
        query.addBindValue(wpt_element.attribute("lon").toDouble());
        if (query.exec()) {
            std::cout << "query.exec() DONE" << std::endl;
        } else {
            std::cout << "query.exec() FAIL" << std::endl;
            std::cout << "ERROR Message: \"" << query.lastError().driverText().toStdString() << "\"" << std::endl;
            return false;
        }
        point_id = query.lastInsertId().toInt();

        // Description
        query.prepare("INSERT INTO Descriptions (name, link_url, link_name, comments, source, type) VALUES (?,?,?,?,?,?)");
        query.addBindValue(wpt_element.elementsByTagName("name").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("link").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("link").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("cmt").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("src").item(0).firstChild().nodeValue());
        query.addBindValue(wpt_element.elementsByTagName("type").item(0).firstChild().nodeValue());
        if (query.exec()) {
            std::cout << "query.exec() DONE" << std::endl;
        } else {
            std::cout << "query.exec() FAIL" << std::endl;
            std::cout << "ERROR Message: \"" << query.lastError().driverText().toStdString() << "\"" << std::endl;
            return false;
        }
        description_id = query.lastInsertId().toInt();

        // Waypoint
        query.prepare("INSERT INTO Waypoints (description, point) VALUES(?,?)");
        query.addBindValue(description_id);
        query.addBindValue(point_id);
        if (query.exec()) {
            std::cout << "query.exec() DONE" << std::endl;
        } else {
            std::cout << "query.exec() FAIL" << std::endl;
            std::cout << "ERROR Message: \"" << query.lastError().driverText().toStdString() << "\"" << std::endl;
            return false;
        }
        waypoint_id = query.lastInsertId().toInt();

        // Cache
        query.prepare("INSERT INTO Caches (name, placed_by, owner, owner_guid, owner_name, type, container, difficulty, terrain, country, state, short_description, short_description_encoded, long_description, long_description_encoded, encoded_hints, waypoint) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(cache_element.elementsByTagName("groundspeak:name").item(0).firstChild().nodeValue());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:placed_by").item(0).firstChild().nodeValue());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:owner").item(0).toElement().attribute("id"));
        query.addBindValue(cache_element.elementsByTagName("groundspeak:owner").item(0).toElement().attribute("guid"));
        query.addBindValue(cache_element.elementsByTagName("groundspeak:owner").item(0).firstChild().nodeValue());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:type").item(0).firstChild().nodeValue());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:container").item(0).firstChild().nodeValue());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:difficulty").item(0).firstChild().nodeValue());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:terrain").item(0).firstChild().nodeValue());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:country").item(0).firstChild().nodeValue());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:state").item(0).firstChild().nodeValue());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:short_description").item(0).firstChild().nodeValue());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:short_description").item(0).toElement().attribute("html").toInt());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:long_description").item(0).firstChild().nodeValue());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:long_description").item(0).toElement().attribute("html").toInt());
        query.addBindValue(cache_element.elementsByTagName("groundspeak:encoded_hints").item(0).firstChild().nodeValue());
        query.addBindValue(waypoint_id);
        if (query.exec()) {
            std::cout << "query.exec() DONE" << std::endl;
        } else {
            std::cout << "query.exec() FAIL" << std::endl;
            std::cout << "ERROR Message: \"" << query.lastError().driverText().toStdString() << "\"" << std::endl;
            return false;
        }
        cache_id = query.lastInsertId().toInt();

        QDomNodeList cache_log_list = cache_element.elementsByTagName("groundspeak:logs").item(0).toElement().elementsByTagName("groundspeak:log");
        for (int cache_log_i = 0; cache_log_i < cache_log_list.count(); ++cache_log_i)
        {
            QDomElement log_element = cache_log_list.item(cache_log_i).toElement();
            query.prepare("INSERT INTO Logs (log_id, log_guid, date, type, finder_id, finder_guid, finder_name, text, text_encoded, latitude, longitude, cache) VALUES (?,?,?,?,?,?,?,?,?,?,?)");
            query.addBindValue(cache_element.attribute("id"));
            query.addBindValue(cache_element.attribute("guid"));
            query.addBindValue(cache_element.elementsByTagName("groundspeak:date").item(0).firstChild().nodeValue());
            query.addBindValue(cache_element.elementsByTagName("groundspeak:type").item(0).firstChild().nodeValue());
            query.addBindValue(cache_element.elementsByTagName("groundspeak:finder").item(0).toElement().attribute("id"));
            query.addBindValue(cache_element.elementsByTagName("groundspeak:finder").item(0).toElement().attribute("guid"));
            query.addBindValue(cache_element.elementsByTagName("groundspeak:finder").item(0).firstChild().nodeValue());
            query.addBindValue(cache_element.elementsByTagName("groundspeak:text").item(0).firstChild().nodeValue());
            query.addBindValue(cache_element.elementsByTagName("groundspeak:text").item(0).toElement().attribute("encoded").toInt());
            query.addBindValue(cache_element.attribute("lat"));
            query.addBindValue(cache_element.attribute("lon"));
            query.addBindValue(cache_id);
            if (query.exec()) {
                std::cout << "query.exec() DONE" << std::endl;
            } else {
                std::cout << "query.exec() FAIL" << std::endl;
                std::cout << "ERROR Message: \"" << query.lastError().driverText().toStdString() << "\"" << std::endl;
                return false;
            }
        }
    }
    return true;
}

