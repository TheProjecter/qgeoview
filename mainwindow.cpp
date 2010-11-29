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
    QFile::setPermissions(_settings->value("database/location").toString(), QFile::ReadOwner | QFile::WriteOwner);
}


MainWindow::~MainWindow()
{
    delete _db;
    delete _settings;
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
    _db->import_gpx(&file);
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    // get filename
    QString filename = QFileDialog::getSaveFileName();
    if (filename.isNull())
        return;

    // save file
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Cannot open file for saving." << std::endl;
        return;
    }
    _db->export_gpx(&file, 0);  // TODO: replace 0 with collection_id
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
