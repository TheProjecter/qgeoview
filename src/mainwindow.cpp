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
    setWindowIcon(QIcon(":/icons/application.svg"));

    _cacheTableProxy->setSourceModel(_cacheTable);
    _cacheTableProxy->setDynamicSortFilter(true);

    ui->caches_list->setModel(_cacheTableProxy);

    
    _map = new qmapcontrol::MapControl(QSize(380, 540));
    _map_adapter = new qmapcontrol::OSMMapAdapter();
    ui->tab_map_layout->addWidget(_map);

    _map_layer_main = new qmapcontrol::MapLayer("OpenStreetMap-Layer", _map_adapter);
    _map->addLayer(_map_layer_main);

    _map_layer_caches = new qmapcontrol::GeometryLayer("Caches", _map_adapter);
    _map->addLayer(_map_layer_caches);

    _map->showScale(true);

    connect(_map_layer_caches, SIGNAL(geometryClicked(Geometry *, QPoint)), this, SLOT(cache_clicked(Geometry*, QPoint)));
    connect(ui->map_zoomin, SIGNAL(clicked(bool)), _map, SLOT(zoomIn()));
    connect(ui->map_zoomout, SIGNAL(clicked(bool)), _map, SLOT(zoomOut()));


    connect(_cacheTable, SIGNAL(cache_added(Cache*)), this, SLOT(cache_added(Cache*)));
    connect(ui->caches_list, SIGNAL(clicked(QModelIndex)), this, SLOT(view_row_selected(QModelIndex)));
    connect(this, SIGNAL(row_selected(QModelIndex)), _cacheTable, SLOT(row_selected(QModelIndex)));
    connect(_cacheTable, SIGNAL(activate_cache(Cache*)), this, SLOT(activate_cache(Cache*)));
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
    _map->moveTo(QPointF(cache->longitude, cache->latitude));
    ui->statusBar->showMessage(cache->number + " - " + cache->name);
}


void MainWindow::on_actionTest_triggered()
{
    openFile("/home/doug/Desktop/test.gpx");
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
    QDomDocument *doc = _cacheTable->genGPX();

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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // TODO: Determine available size.
    _map->resize(QSize(event->size().width()/2, (2*event->size().height())/3));
}

void MainWindow::cache_added(Cache *cache)
{
    qmapcontrol::Point* cachepoint = new qmapcontrol::ImagePoint(cache->longitude, cache->latitude, ":/icons/traditional.gif", cache->number);
    _map_layer_caches->addGeometry(cachepoint);
}


void MainWindow::cache_clicked(qmapcontrol::Geometry *geometry, QPoint point)
{
    Q_UNUSED(point)
    Cache *cache = _cacheTable->cacheByNumber(geometry->name());
    if (cache != NULL)
        activate_cache(cache);
}

void MainWindow::MapSourceChanged(QString src)
{
    int zoom = _map_adapter->adaptedZoom();
    _map->setZoom(0);
    if (src == "Open Street Map") {
        _map_adapter = new qmapcontrol::OSMMapAdapter();
    } else if (src == "Google Map") {
        _map_adapter = new qmapcontrol::GoogleMapAdapter();
    } else if (src == "Google Map (Satelite") {
        _map_adapter = new qmapcontrol::GoogleSatMapAdapter();
    } else if (src == "Yahoo Map") {
        _map_adapter = new qmapcontrol::YahooMapAdapter();
    } else if (src == "Yahoo Map (Satelite)") {
        _map_adapter = new qmapcontrol::YahooMapAdapter("us.maps3.yimg.com", "/aerial.maps.yimg.com/png?v=1.7&t=a&s=256&x=%2&y=%3&z=%1");
    } else {
        std::cerr << "Unknwon Map Source: \"" << src.toStdString() << "\"" << std::endl;
        _map->setZoom(zoom);
    }
    std::cout << "Loading \"" << src.toStdString() << "\" Map Source" << std::endl;
    _map->updateRequestNew();
    _map->setZoom(zoom);
    _map_layer_main->setMapAdapter(_map_adapter);
    _map_layer_caches->setMapAdapter(_map_adapter);
}
