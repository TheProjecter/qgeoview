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

#include "write_gpx.h"


WriteGpxPlugin::WriteGpxPlugin(Database *db) :
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

WritePlugin *WriteGpxPluginFactory::get_plugin(Database *db)
{
    return new WriteGpxPlugin(db);
}

Q_EXPORT_PLUGIN2(writegpxpluginfactory, WriteGpxPluginFactory);
