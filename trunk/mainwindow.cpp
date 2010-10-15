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
#include <QCoreApplication>
#include "newitemdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treemodel.h"

#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Settings
    QCoreApplication::setOrganizationName("DarwinSurvivor");
    QCoreApplication::setOrganizationDomain("http://code.google.com/p/qgeoview/");
    QCoreApplication::setApplicationName("QGeoView");
    _settings = new QSettings;
    if (!_settings->contains("installed")) {
        firstRun();
    }

    // Database
    _db = new Database(_settings->value("database/location").toString());

    // UI
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/application.svg"));
    ui->item_list->setModel(new TreeModel);

    // Map
    ui->map->centerOn(49, 122, true);
    infoType(INFO_TYPE_NONE);

    // Test
}

void MainWindow::firstRun()
{
    std::cout << "First run detected, setting defaults" << std::endl;
    // Settings
    _settings->setValue("installed", true);
    QString database_location = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    database_location.append("/db.sqlite3");
    _settings->setValue("database/location", database_location);

    // Directories
    QDir dir;
    if (!dir.mkpath(QString(QDesktopServices::storageLocation(QDesktopServices::DataLocation)))) {
        std::cerr << "Error creating dataStorage folder" << std::endl;
    }

    // Empty DB File
    std::cout << "copying database to " << _settings->value("database/location").toString().toStdString() << std::endl;
    QFile(":/db.sqlite3.empty").copy(_settings->value("database/location").toString());
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



void MainWindow::on_actionTest_triggered()
{
    //NewItemDialog(this).exec();
    openFile("/home/doug/test.gpx");
}


void MainWindow::view_row_selected(const QModelIndex & index)
{
    if (!index.isValid())
        return;
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
    if (_db->import_gpx(&file)) {
        std::cout << "Successfully Imported " << filename.toStdString() << "as GPX" << std::endl;
    } else {
        std::cerr << "Error Importing " << filename.toStdString() << " as GPX" << std::endl;
    }
    file.close();
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

QDomDocument *MainWindow::genGPX(QList<Cache*> caches)
{
    return new QDomDocument;
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
    return doc;*/
}
