#include <iostream>
#include <QDomDocument>
#include "database.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include "treeitem.h"


/*
 Opens the database and ensures that it is available.
*/
Database::Database(QString location, QTreeView *tree, QObject *parent) :
    QObject(parent),
    _tree(tree)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(location);
    if (_db.open()) {
        std::cout << "Connected" << std::endl;
    } else {
        std::cerr << "Error Connecting to Database: " << location.toStdString() << std::endl;
    }
    populate();
}


/*
 Closes the database connection.
*/
Database::~Database()
{
    _db.close();
}


/*
 Populates the list
*/
void Database::populate(int collection_id) {
    QSqlQuery *query;
    // Caches
    if (collection_id < 0) {
        std::cout << "selecting all" << std::endl;
        query = new QSqlQuery("SELECT Caches.id, Caches.name from Caches");
    } else {
        std::cout << "selecting from collection" << std::endl;
        query = new QSqlQuery("SELECT Caches.id, Caches.name from Caches where c.id in (SELECT CachesInCollections.cache FROM CachesInCollections where CachesInCollections.id=?)");
        query->addBindValue(collection_id);
    }
    _tree->setSortingEnabled(1);
    std::cout << "Now Adding " << query->size() << "items" << std::endl;
    std::cerr << "Possible Driver Error: " << query->lastError().driverText().toStdString() << std::endl;
    std::cerr << "Possible Database Error: " << query->lastError().databaseText().toStdString() << std::endl;
    while (query->next()) {
        // TODO: Add Item To Tree
        // std::cout << "Added " << item->text().toStdString() << std::endl;
    }
    // waypoints TODO: finish
    if (collection_id < 0) {
        query = new QSqlQuery("SELECT w.id, d.name from Waypoints w INNER JOIN Descriptions d ON w.description = d.id");
    } else {
        query = new QSqlQuery("SELECT w.id, d.name from Waypoints w INNER JOIN Descriptions d ON w.description = d.id where w.id in (SELECT wc.waypoint FROM WaypointCollections wc where id=?)");
        query->addBindValue(collection_id);
    }
    delete query;
}


/*
 Imports a GPX file into the database
 TODO: Detect duplicates.
*/
void Database::import_gpx(QFile *file)
{
    QDomDocument doc;
    QSqlQuery query;
    if (!doc.setContent(file)) {
        std::cerr << "Unusable GPX file" << std::endl;
        return;
    }
    QDomElement gpx_element = doc.documentElement();
    if (gpx_element.tagName() != "gpx")
    {
        std::cerr << "Not an XML file" << std::endl;
        return;
    }
    _db.transaction();

    // read data
    QDomNodeList wpt_list = gpx_element.elementsByTagName("wpt");
    int point_id, cache_id, waypoint_id, description_id;
    for (int wpt_i = 0; wpt_i < wpt_list.count(); ++wpt_i)
    {
        QDomElement wpt_element = wpt_list.item(wpt_i).toElement();
        QDomElement cache_element = wpt_element.elementsByTagName("groundspeak:cache").item(0).toElement();
        // Point
        query.prepare("INSERT INTO Points (time, elevation, magneticVariation, geoIDHeight, symbol, fix, satelites, horizontalDOP, verticalDOP, positionDOP, ageofDGPSData, DGPSID, latitude, longitude) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
        query.addBindValue(child_value(wpt_element.elementsByTagName("time"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("ele"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("magvar"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("geoidheight"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("sym"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("fix"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("sat"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("hdop"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("vdop"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("pdop"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("ageofdgpsdata"), DATABASE_DATATYPE_STRING));
        query.addBindValue(child_value(wpt_element.elementsByTagName("dgpsid"), DATABASE_DATATYPE_STRING));
        query.addBindValue(wpt_element.attribute("lat").toDouble());
        query.addBindValue(wpt_element.attribute("lon").toDouble());
        std::cout << "executing query 1" << std::endl;
        if (query.exec()) {
            std::cout << "query.exec() DONE" << std::endl;
        } else {
            std::cout << "query.exec() FAIL" << std::endl;
            std::cout << "ERROR Message: \"" << query.lastError().driverText().toStdString() << "\" and \"" << query.lastError().databaseText().toStdString() << "\"" << std::endl;
            return;
        }
        point_id = query.lastInsertId().toInt();

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
    }
    _db.commit();
}


/*
 Exports a collection to a GPX file.
*/
void Database::export_gpx(QFile *file, int collection_id) {
    return;
    /*
    // create gpx structure
    if (caches.empty())
        return NULL;
    Cache *cache = caches.at(0);
    double minlat = cache->latitude;
    double minlon = cache->longitude;
    double maxlat = minlat;
    double maxlon = minlon;
    if (caches.count() > 1) {
        for (int i = 1; i < caches.count(); ++i) {
            cache = caches.at(i);
            if (cache->latitude < minlat) {
                minlat = cache->latitude;
            }
            if (cache->latitude > maxlat) {
                maxlat = cache->latitude;
            }
            if (cache->longitude < minlon) {
                minlon = cache->longitude;
            }
            if (cache->longitude > maxlon) {
                maxlon = cache->longitude;
            }
        }
    }
    QDomDocument *doc = new QDomDocument("Gpx");
    QDomElement gpx = doc->createElement("gpx");
    gpx.setAttribute("xmlns:xsi", "http://www.w3.org/2010/XMLSchema-instance");
    gpx.setAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
    gpx.setAttribute("version", "1.0");
    gpx.setAttribute("creator", "qgeoview");
    gpx.setAttribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd http://www.groundspeak.com/cache/1/0 http://www.groundspeak.com/cache/1/0/cache.xsd");
    gpx.setAttribute("xmlns", "http://www.topografix.com/GPS/1/0");
    QDomElement name = doc->createElement("name");
    name.appendChild(doc->createTextNode("New Query"));
    gpx.appendChild(name);
    QDomElement desc = doc->createElement("desc");
    desc.appendChild(doc->createTextNode("Geocaching file modified by qgeoview"));
    gpx.appendChild(desc);
    QDomElement author = doc->createElement("author");
    author.appendChild(doc->createTextNode("Doug Penner"));
    gpx.appendChild(author);
    QDomElement email = doc->createElement("email");
    email.appendChild(doc->createTextNode("darwinsurvivor@gmail.com"));
    gpx.appendChild(email);
    QDomElement time = doc->createElement("time");
    time.appendChild(doc->createTextNode("2010-06-18T14:37:42.2184239Z"));    // TODO: add actual time
    gpx.appendChild(time);
    QDomElement keywords = doc->createElement("keywords");
    keywords.appendChild(doc->createTextNode("cache, geocache, groundspeak"));
    gpx.appendChild(keywords);
    QDomElement bounds = doc->createElement("bounds");
    bounds.setAttribute("minlat", minlat);
    bounds.setAttribute("minlon", minlon);
    bounds.setAttribute("maxlat", maxlat);
    bounds.setAttribute("maxlon", maxlon);
    gpx.appendChild(bounds);

    // add caches
    for (int i = 0; i < caches.count(); ++i) {
        cache = caches.at(i);
        gpx.appendChild(cache->xmlElement);
    }
    doc->appendChild(gpx);
    QTextStream stream(file);
    stream << doc->toString();*/
}


/*
 Converts a sql string to either a specified format, or null (QVariant())
*/
QVariant Database::child_value(QDomNodeList list, int format=0) {
    if (list.size() == 0) {
        switch (format) {
            case DATABASE_DATATYPE_STRING:
                return QVariant::String;
            case DATABASE_DATATYPE_INT:
                return QVariant::Int;
            case DATABASE_DATATYPE_DOUBLE:
                return QVariant::Double;
            default:
                std::cerr << "Invalid DATABASE_DATATYPE" << std::endl;
        }
    }
    switch (format) {
        case DATABASE_DATATYPE_STRING:
            return list.item(0).firstChild().nodeValue();
        case DATABASE_DATATYPE_INT:
            return list.item(0).firstChild().nodeValue().toInt();
        case DATABASE_DATATYPE_DOUBLE:
            return list.item(0).firstChild().nodeValue().toDouble();
    }
    std::cerr << "Invalid DATABASE_DATATYPE" << std::endl;
    return QVariant();
}
