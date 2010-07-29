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
    _cacheTableProxy(new QSortFilterProxyModel(this)),
    _cacheTable(new CacheTable(ui->caches_list, _cacheTableProxy))
{
    ui->setupUi(this);

    _cacheTableProxy->setSourceModel(_cacheTable);
    _cacheTableProxy->setDynamicSortFilter(true);

    ui->caches_list->setModel(_cacheTableProxy);

    // TODO: Remove next line
    //openFile("test.gpx");

    connect(ui->caches_list, SIGNAL(clicked(QModelIndex)), this, SLOT(view_row_selected(QModelIndex)));
    connect(this, SIGNAL(row_selected(QModelIndex)), _cacheTable, SLOT(row_selected(QModelIndex)));
    connect(_cacheTable, SIGNAL(cache_selected(Cache*)), this, SLOT(cache_selected(Cache*)));
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


void MainWindow::cache_selected(Cache *cache)
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
    ui->map->setUrl(tr("http://local.google.ca/?ll=%1,%2").arg(QString::number(cache->latitude), QString::number(cache->longitude)));
}


void MainWindow::on_actionTest_triggered()
{
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
    _cacheTable->openGPX(&gpx_file);
}

void MainWindow::on_actionSave_triggered()
{
    // get filename
    QString filename = QFileDialog::getSaveFileName();
    if (filename.isNull())
        return;

    // create gpx structure
    QList<Cache*> caches = _cacheTable->selected_caches();
    if (caches.empty())
        return;
    Cache *cache = caches.at(0);
    double minlat = cache->latitude;
    double minlon = cache->longitude;
    double maxlat = minlat;
    double maxlon = minlon;
    if (caches.count() > 1) {
        for (int i = 1; i < caches.count(); ++i) {
            std::cout << "checking " << i << std::endl;
            cache = caches.at(i);
            if (cache->latitude < minlat) {
                std::cout << cache->latitude << " < " << minlat << std::endl;
                minlat = cache->latitude;
            }
            if (cache->latitude > maxlat) {
                std::cout << cache->latitude << " > " << maxlat << std::endl;
                maxlat = cache->latitude;
            }
            if (cache->longitude < minlon) {
                std::cout << cache->longitude << " < " << minlon << std::endl;
                minlon = cache->longitude;
            }
            if (cache->longitude > maxlon) {
                std::cout << cache->longitude << " > " << maxlon << std::endl;
                maxlon = cache->longitude;
            }
        }
    }
    QDomDocument doc("Gpx");
    QDomElement gpx = doc.createElement("gpx");
    gpx.setAttribute("xmlns:xsi", "http://www.w3.org/2010/XMLSchema-instance");
    gpx.setAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
    gpx.setAttribute("version", "1.0");
    gpx.setAttribute("creator", "qgeoview");
    gpx.setAttribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd http://www.groundspeak.com/cache/1/0 http://www.groundspeak.com/cache/1/0/cache.xsd");
    gpx.setAttribute("xmlns", "http://www.topografix.com/GPS/1/0");
    QDomElement name = doc.createElement("name");
    name.appendChild(doc.createTextNode("New Query"));
    gpx.appendChild(name);
    QDomElement desc = doc.createElement("desc");
    desc.appendChild(doc.createTextNode("Geocaching file modified by qgeoview"));
    gpx.appendChild(desc);
    QDomElement author = doc.createElement("author");
    author.appendChild(doc.createTextNode("Doug Penner"));
    gpx.appendChild(author);
    QDomElement email = doc.createElement("email");
    email.appendChild(doc.createTextNode("darwinsurvivor@gmail.com"));
    gpx.appendChild(email);
    QDomElement time = doc.createElement("time");
    time.appendChild(doc.createTextNode("2010-06-18T14:37:42.2184239Z"));    // TODO: add actual time
    gpx.appendChild(time);
    QDomElement keywords = doc.createElement("keywords");
    keywords.appendChild(doc.createTextNode("cache, geocache, groundspeak"));
    gpx.appendChild(keywords);
    QDomElement bounds = doc.createElement("bounds");
    bounds.setAttribute("minlat", minlat);
    bounds.setAttribute("minlon", minlon);
    bounds.setAttribute("maxlat", maxlat);
    bounds.setAttribute("maxlon", maxlon);
    gpx.appendChild(bounds);

    // add caches
    for (int i = 0; i < caches.count(); ++i) {
        cache = caches.at(i);
        gpx.appendChild(cache->xmlElement);
        std::cout << "Adding " << cache->number.toStdString() << std::endl;
    }
    doc.appendChild(gpx);

    // save file
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Cannot open file for saving." << std::endl;
        return;
    }
    QTextStream stream(&file);
    stream << doc.toString();
    file.close();
}
