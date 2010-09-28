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


#include <QDomDocument>
#include <QFile>
#include <iostream>
#include <QFileDialog>
#include <QProcess>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _cacheTableProxy(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/application.svg"));

    _db = new QSqlQueryModel;
    _db->setQuery("select * from caches");    

    ui->map->centerOn(49, 122, true);
    infoType(INFO_TYPE_NONE);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::on_action_Quit_triggered()
{
    emit quit();
}


void MainWindow::activate_cache(Cache *cache)
{
    emit cache_changed(cache);
    emit cache_lat_changed(cache->latitude);
    emit cache_lon_changed(cache->longitude);
    emit cache_number_changed(cache->number);
    emit cache_name_changed(cache->name);
    emit cache_long_name_changed(cache->long_name);
    emit cache_url_changed(cache->url);
    emit cache_url_name_changed(cache->url_name);
    emit cache_placed_by_changed(cache->placed_by);
    emit cache_owner_changed(cache->owner);
    emit cache_terrain_changed(cache->terrain);
    emit cache_type_changed(cache->type);
    emit cache_container_changed(cache->container);
    emit cache_difficulty_changed(cache->difficulty);
    if (cache->desc_long_html)
        emit cache_desc_long_html_changed(cache->desc_long);
    else
        emit cache_desc_long_changed(cache->desc_long);
    if (cache->desc_long_html)
        emit cache_desc_short_html_changed(cache->desc_short);
    else
        emit cache_desc_short_changed(cache->desc_short);
    emit cache_hint_changed(cache->hint);
    ui->cache_page->setUrl(cache->url);
    // TODO: move map
    ui->statusBar->showMessage(cache->number + " - " + cache->name);
}


void MainWindow::on_actionTest_triggered()
{
    openFile("/home/doug/test.gpx");
    ui->map->openGpxFile("/home/doug/test.gpx");
}


void MainWindow::view_row_selected(const QModelIndex & index)
{
    if (!index.isValid())
        return;
    emit row_selected(_cacheTableProxy->mapToSource(index));
}


void MainWindow::on_action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    if (filename.isNull())
        return;
    openFile(filename);
}


void MainWindow::openFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }

    if (!gpx_file.setContent(&file)) {
        std::cerr << "Unusable file" << std::endl;
        file.close();
        return;
    }
    file.close();
    // TODO: _cacheTable->openGPX(&gpx_file);
}


void MainWindow::on_actionSave_triggered()
{
    // get filename
    QString filename = QFileDialog::getSaveFileName();
    if (filename.isNull())
        return;
    //QDomDocument *doc = _cacheTable->genGPX();
    QDomDocument *doc = new QDomDocument;

    // save file
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Cannot open file for saving." << std::endl;
        return;
    }
    QTextStream stream(&file);
    stream << doc->toString();
    file.close();
}


void MainWindow::infoType(int type) {
    ui->route_info->setVisible(false);
    ui->track_info->setVisible(false);
    ui->waypoint_info->setVisible(false);
    switch(type) {
    case INFO_TYPE_WAYPOINT:
        ui->waypoint_info->setVisible(true);
        break;
    case INFO_TYPE_TRACK:
        ui->track_info->setVisible(true);
        break;
    case INFO_TYPE_ROUTE:
        ui->route_info->setVisible(true);
        break;
    }
}


void MainWindow::MapSourceChanged(QString src)
{
    if (src == "Open Street Map") {
        ui->map->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    } else if (src == "Blue Marble") {
        ui->map->setMapThemeId("earth/bluemarble/bluemarble.dgml");
    } else if (src == "Plain") {
        ui->map->setMapThemeId("earth/plain/plain.dgml");
    } else {
        std::cerr << "Unknwon Map Source: \"" << src.toStdString() << "\"" << std::endl;
    }
    std::cout << "Loading \"" << src.toStdString() << "\" Map Source" << std::endl;
}

void MainWindow::openGPX(QDomDocument *doc)
{
    QDomElement gpx_element = doc->documentElement();
    if (gpx_element.tagName() != "gpx")
    {
        std::cerr << "Not an XML file" << std::endl;
        return;
    }

    // read data
    QDomNodeList wpt_list = gpx_element.elementsByTagName("wpt");
    for (int wpt_i = 0; wpt_i < wpt_list.count(); ++wpt_i)
    {
        QDomElement wpt_element = wpt_list.item(wpt_i).toElement();
        QDomElement cache_element = wpt_element.elementsByTagName("groundspeak:cache").item(0).toElement();
        Cache *cache = new Cache;
        cache->xmlElement = wpt_element;
        cache->selected = false;
        cache->latitude = wpt_element.attribute("lat").toDouble();
        cache->longitude = wpt_element.attribute("lon").toDouble();
        cache->number = wpt_element.elementsByTagName("name").item(0).firstChild().nodeValue();
        cache->name = cache_element.elementsByTagName("groundspeak:name").item(0).firstChild().nodeValue();
        cache->long_name = wpt_element.elementsByTagName("desc").item(0).firstChild().nodeValue();
        cache->url = wpt_element.elementsByTagName("url").item(0).firstChild().nodeValue();
        cache->url_name = wpt_element.elementsByTagName("name").item(0).firstChild().nodeValue();
        cache->placed_by = cache_element.elementsByTagName("groundspeak:placed_by").item(0).firstChild().nodeValue();
        cache->owner = cache_element.elementsByTagName("groundspeak:owner").item(0).firstChild().nodeValue();
        cache->type = cache_element.elementsByTagName("groundspeak:type").item(0).firstChild().nodeValue();
        cache->container = cache_element.elementsByTagName("groundspeak:container").item(0).firstChild().nodeValue();
        cache->difficulty = cache_element.elementsByTagName("groundspeak:difficulty").item(0).firstChild().nodeValue().toFloat();
        cache->terrain = cache_element.elementsByTagName("groundspeak:terrain").item(0).firstChild().nodeValue().toFloat();
        QDomElement short_description_element = cache_element.elementsByTagName("groundspeak:short_description").item(0).toElement();
        cache->desc_short_html = short_description_element.attribute("html", "False") == "True";
        cache->desc_short = short_description_element.firstChild().nodeValue();
        QDomElement long_description_element = cache_element.elementsByTagName("groundspeak:long_description").item(0).toElement();
        cache->desc_long_html = long_description_element.attribute("html", "False") == "True";
        cache->desc_long = long_description_element.firstChild().nodeValue();
        cache->hint = cache_element.elementsByTagName("groundspeak:encoded_hints").item(0).firstChild().nodeValue();
        QDomNodeList cache_log_list = cache_element.elementsByTagName("groundspeak:logs").item(0).toElement().elementsByTagName("groundspeak:log");
        for (int cache_log_i = 0; cache_log_i < cache_log_list.count(); ++cache_log_i)
        {
            QDomElement log_element = cache_log_list.item(cache_log_i).toElement();
            CacheLog *log = new CacheLog;
            log->datetime = QDateTime::fromString(log_element.elementsByTagName("groundspeak:date").item(0).firstChild().nodeValue());
            log->type = log_element.elementsByTagName("groundspeak:type").item(0).firstChild().nodeValue();
            log->poster = log_element.elementsByTagName("groundspeak:finder").item(0).firstChild().nodeValue();
            QDomElement log_text_element = log_element.elementsByTagName("groundspeak:text").item(0).toElement();
            log->text_encoded = log_text_element.attribute("encoded", "False") == "True";
            log->text = log_text_element.nodeValue();
            cache->logs.append(log);
        }
        emit new_cache(cache);
    }
}

QDomDocument *MainWindow::genGPX(QList<Cache*> caches)
{
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
    return doc;
}
