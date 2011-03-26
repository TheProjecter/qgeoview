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
#include <QTime>
#include <QTextStream>
#include <QVariant>
#include <iostream>
#include <QSqlError>
#include <QFileDialog>

#include "write_gpx.h"


WriteGpxPlugin::WriteGpxPlugin(QSqlDatabase *db) :
    WritePlugin(db)
{
}

QString WriteGpxPlugin::name()
{
    return "GPX Writer";
}

void WriteGpxPlugin::save()
{
    QString filename = QFileDialog::getSaveFileName();
    if (filename.isNull())
        return;
    std::cout << "Saving to: " << filename.toStdString() << std::endl;
    QFile file(filename);
    write(&file, 0); // TODO: get collection number from somewhere's
}

/*
 Exports a collection to a GPX file.
*/
void WriteGpxPlugin::write(QFile *file, int collection_id) {
    // create gpx structure
    QList<Cache*> caches;
    QList<Waypoint*> waypoints;
    if (collection_id) {
        QPointer<Collection> collection = new Collection(_db, collection_id);
        caches = collection->caches();
        waypoints = collection->waypoints();
    } else {
        caches = Cache::getAll(_db);
        waypoints = Waypoint::getAll(_db);
    }
    double minlat = caches.at(0)->getWaypoint()->getPoint()->getLatitude();
    double minlon = caches.at(0)->getWaypoint()->getPoint()->getLongitude();
    double maxlat = minlat;
    double maxlon = minlon;
    if (caches.count() > 1) {
        for (QList<Cache*>::iterator i = caches.begin(); i != caches.end(); ++i) {
            double lat = (*i)->getWaypoint()->getPoint()->getLatitude();
            double lon = (*i)->getWaypoint()->getPoint()->getLongitude();
            if (lat < minlat) {
                minlat = lat;
            }
            if (lat > maxlat) {
                maxlat = lat;
            }
            if (lon < minlon) {
                minlon = lon;
            }
            if (lon > maxlon) {
                maxlon = lon;
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
    QTime current_time = QTime::currentTime();
    QDomElement time = doc->createElement("time");
    time.appendChild(doc->createTextNode(current_time.toString(Qt::ISODate).append(".").append(current_time.msec())));    // Format: 2010-06-18T14:37:42.2184239Z
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
    for (QList<Cache*>::iterator i = caches.begin(); i != caches.end(); ++i) {
        QDomElement wpt_e = waypoint2gpx(doc, (*i)->getWaypoint());
        wpt_e.appendChild(cache2gpx(doc, *i));
        gpx.appendChild(wpt_e);
    }

    // add waypoints
    for (QList<Waypoint*>::iterator i = waypoints.begin(); i != waypoints.end(); ++i) {
        gpx.appendChild(waypoint2gpx(doc, *i));
    }

    doc->appendChild(gpx);
    QTextStream stream(file);
    stream << doc->toString();
}

QDomElement WriteGpxPlugin::cache2gpx(QDomDocument *doc, Cache *cache)
{
    QDomElement e = doc->createElement("groundspeak:name");
    if (cache->isSet(NULLMASK_CACHE_NAME))
        e.appendChild(createTextElement(doc, "name", cache->getName()));
    if (cache->isSet(NULLMASK_CACHE_PLACEDBY))
        e.appendChild(createTextElement(doc, "placed_by", cache->getPlacedBy()));
    if (cache->isSet(NULLMASK_CACHE_OWNERNAME)) {
        QDomElement owner_e = doc->createElement("groundspeak:owner");
        if (cache->isSet(NULLMASK_CACHE_OWNERID))
            owner_e.setAttribute("id", cache->getOwnerID());
        if (cache->isSet(NULLMASK_CACHE_OWNERGUID))
            owner_e.setAttribute("guid", cache->getOwnerGUID());
        e.appendChild(owner_e);
    }
    if (cache->isSet(NULLMASK_CACHE_TYPE))
        e.appendChild(createTextElement(doc, "groundspeak:type", cache->getType()));
    if (cache->isSet(NULLMASK_CACHE_CONTAINER))
        e.appendChild(createTextElement(doc, "groundspeak:container", cache->getContainer()));
    if (cache->isSet(NULLMASK_CACHE_DIFFICULTY))
        e.appendChild(createTextElement(doc, "groundspeak:difficulty", QVariant(cache->getDifficulty()).toString()));
    if (cache->isSet(NULLMASK_CACHE_TERRAIN))
        e.appendChild(createTextElement(doc, "groundspeak:terrain", QVariant(cache->getTerrain()).toString()));
    if (cache->isSet(NULLMASK_CACHE_COUNTRY))
        e.appendChild(createTextElement(doc, "groundspeak:country", cache->getCountry()));
    if (cache->isSet(NULLMASK_CACHE_STATE))
        e.appendChild(createTextElement(doc, "groundspeak:state", cache->getState()));
    if (cache->isSet(NULLMASK_CACHE_SHORTDESCRIPTION)) {
        QDomElement sd_e = doc->createElement("groundspeak:short_description");
        sd_e.setAttribute("html", (cache->isSet(NULLMASK_CACHE_SHORTDESCRIPTIONHTML) && cache->getShortDescriptionHTML() ? "True" : "False"));
        e.appendChild(sd_e);
    }
    if (cache->isSet(NULLMASK_CACHE_LONGDESCRIPTION)) {
        QDomElement ld_e = doc->createElement("groundspeak:long_description");
        ld_e.setAttribute("html", (cache->isSet(NULLMASK_CACHE_LONGDESCRIPTIONHTML) && cache->getLongDescriptionHTML() ? "True" : "False"));
        e.appendChild(ld_e);
    }
    if (cache->isSet(NULLMASK_CACHE_ENCODEDHINTS))
        e.appendChild(createTextElement(doc, "groundspeak:encoded_hints", cache->getEncodedHints()));
    return e;
}

QDomElement WriteGpxPlugin::waypoint2gpx(QDomDocument *doc, Waypoint*waypoint)
{
    QDomElement e = doc->createElement("groundspeak:name");
    e.setAttribute("lat", waypoint->getPoint()->getLatitude());
    e.setAttribute("lon", waypoint->getPoint()->getLongitude());

    QList<QDomElement> pel = point2gpx(doc, waypoint->getPoint());
    for (QList<QDomElement>::iterator i = pel.begin(); i != pel.end(); ++i) {
        e.appendChild((*i));
    }

    QList<QDomElement> del = description2gpx(doc, waypoint->getDescription());
    for (QList<QDomElement>::iterator i = del.begin(); i != del.end(); ++i) {
        e.appendChild((*i));
    }
    return e;
}

/*
 * WARNING: Does not handle latitude/longitude, those need to be handled by the parent function since lat/lon are ATTRIBUTES, not elements!
*/
QList<QDomElement> WriteGpxPlugin::point2gpx(QDomDocument *doc, Point *point)
{
    QList<QDomElement> el;
    if (point->isSet(NULLMASK_POINT_TIME))
        el.append(createTextElement(doc, "time", point->getTime()));
    if (point->isSet(NULLMASK_POINT_ELEVATION))
        el.append(createTextElement(doc, "ele", QVariant(point->getElevation()).toString()));
    if (point->isSet(NULLMASK_POINT_MAGNETICVARIATION))
        el.append(createTextElement(doc, "magvar", QVariant(point->getMagneticVariation()).toString()));
    if (point->isSet(NULLMASK_POINT_GEOIDHEIGHT))
        el.append(createTextElement(doc, "geoidheigt", QVariant(point->getGeoIDHeight()).toString()));
    if (point->isSet(NULLMASK_POINT_SYMBOL))
        el.append(createTextElement(doc, "sym", point->getSymbol()));
    if (point->isSet(NULLMASK_POINT_FIX))
        el.append(createTextElement(doc, "fix", point->getFix()));
    if (point->isSet(NULLMASK_POINT_SATELITES))
        el.append(createTextElement(doc, "sat", QVariant(point->getSatelites()).toString()));
    if (point->isSet(NULLMASK_POINT_HORIZONTALDOP))
        el.append(createTextElement(doc, "hdop", QVariant(point->getHorizontalDOP()).toString()));
    if (point->isSet(NULLMASK_POINT_VERTICALDOP))
        el.append(createTextElement(doc, "vdop", QVariant(point->getVerticalDOP()).toString()));
    if (point->isSet(NULLMASK_POINT_POSITIONDOP))
        el.append(createTextElement(doc, "pdop", QVariant(point->getPositionDOP()).toString()));
    if (point->isSet(NULLMASK_POINT_AGEOFDGPSDATA))
        el.append(createTextElement(doc, "ageofdgpsdata", QVariant(point->getAgeOfDGPSData()).toString()));
    if (point->isSet(NULLMASK_POINT_DGPSID))
        el.append(createTextElement(doc, "dgpsid", QVariant(point->getDGPSID()).toString()));
    return el;
}

QList<QDomElement> WriteGpxPlugin::description2gpx(QDomDocument *doc, Description *description)
{
    QList<QDomElement> el;
    if (description->isSet(NULLMASK_DESCRIPTION_NAME))
        el.append(createTextElement(doc, "name", description->getName()));
    if (description->isSet(NULLMASK_DESCRIPTION_LINKURL))
        el.append(createTextElement(doc, "url", description->getLinkURL()));
    if (description->isSet(NULLMASK_DESCRIPTION_LINKNAME))
        el.append(createTextElement(doc, "urlname", description->getLinkName()));
    if (description->isSet(NULLMASK_DESCRIPTION_COMMENTS))
        el.append(createTextElement(doc, "cmt", description->getComments()));
    if (description->isSet(NULLMASK_DESCRIPTION_SOURCE))
        el.append(createTextElement(doc, "src", description->getSource()));
    if (description->isSet(NULLMASK_DESCRIPTION_TYPE))
        el.append(createTextElement(doc, "type", description->getType()));
    return el;
}

QDomElement WriteGpxPlugin::createTextElement(QDomDocument *doc, QString name, QString value) {
    QDomElement e = doc->createElement(name);
    e.appendChild(doc->createTextNode(value));
    return e;
}

WritePlugin *WriteGpxPluginFactory::get_plugin(QSqlDatabase *db)
{
    return new WriteGpxPlugin(db);
}

Q_EXPORT_PLUGIN2(writegpxpluginfactory, WriteGpxPluginFactory);
