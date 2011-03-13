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

#include <QFile>
#include <iostream>
#include <QFileDialog>
#include <QProcess>
#include <QTextStream>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QSqlError>
#include <QStandardItem>
#include <QStandardItemModel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db/cache.h"
#include "treeitemidentifier.h"
#include "exceptions.h"

#include <QDesktopServices>

/*
 Sets up the application.

 QWidget *parent : paret Widget
*/
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

    // UI
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/application.svg"));

    // Database
    _db = new Database(_settings->value("database/location").toString(), ui->tree);
    
    // Plugins
    loadPlugins();
    refreshTree();
}

/*
 Sets defaults and creates the database.
 This method is only called if the application detects that it has not yet been set up.
*/
void MainWindow::firstRun()
{
    std::cout << "First run detected, setting defaults" << std::endl;
    // Settings
    _settings->setValue("installed", true);
    QString database_location = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    database_location.append("/db.sqlite3");
    _settings->setValue("database/location", database_location);
    QString plugins_location = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    plugins_location.append("/plugins");
    _settings->setValue("plugins/location", plugins_location);

    // Directories
    QDir dir;
    if (!dir.mkpath(QString(QDesktopServices::storageLocation(QDesktopServices::DataLocation)))) {
        std::cerr << "Error creating dataStorage folder" << std::endl;
    }

    // Empty DB File
    std::cout << "copying database to " << _settings->value("database/location").toString().toStdString() << std::endl;
    QFile(":/db/db.sqlite3.empty").copy(_settings->value("database/location").toString());
    QFile::setPermissions(_settings->value("database/location").toString(), QFile::ReadOwner | QFile::WriteOwner);
}


/*
 Removes private variables from memory.
*/
MainWindow::~MainWindow()
{
    delete _db;
    delete _settings;
    delete ui;
}

/*
 TODO: document (can't actually remember this one's purpose...) :(

 QEvent *e : ?
*/
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


/*
 Quit the application.
 Called when "Quit" is clicked (either on the toolbar or in the menu)
*/
void MainWindow::on_action_Quit_triggered()
{
    emit quit();
}


void MainWindow::loadPlugins()
{
    QDir pluginsDir(_settings->value("plugins/location").toString());
    std::cout << "Loading plugins from " << pluginsDir.absolutePath().toStdString() << std::endl;
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        std::cout << "Loading from " << pluginsDir.absoluteFilePath(fileName).toStdString() << std::endl;
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            DummyPluginFactory *dummyPluginFactory = qobject_cast<DummyPluginFactory*>(plugin);
            ReadPluginFactory *readPluginFactory = qobject_cast<ReadPluginFactory*>(plugin);
            WritePluginFactory *writePluginFactory = qobject_cast<WritePluginFactory*>(plugin);
            if (dummyPluginFactory)
                loadDummyPlugin(dummyPluginFactory->get_plugin());
            if (readPluginFactory)
                loadReadPlugin(readPluginFactory->get_plugin(_db));
            if (writePluginFactory)
                loadWritePlugin(writePluginFactory->get_plugin(_db));
        } else {
            std::cout << "Loading " << fileName.toStdString() << " failed: " << pluginLoader.errorString().toStdString() << std::endl;
            std::cout << "\tyou should fix this" << std::endl;
        }
    }
    std::cout << "Found: " << std::endl;
    std::cout << "\tDummy Plugins: \t" << _dummyPlugins.count() << std::endl;
    std::cout << "\tRead Plugins: \t" << _readPlugins.count() << std::endl;
    std::cout << "\tWrite Plugins: \t" << _writePlugins.count() << std::endl;
}

void MainWindow::loadDummyPlugin(DummyPlugin *plugin) {
    std::cout << "Loading Dummy Plugin: " << plugin->name().toStdString() << std::endl;
    _dummyPlugins.append(plugin);
}

void MainWindow::loadReadPlugin(ReadPlugin *plugin) {
    std::cout << "Loading Read Plugin: " << plugin->name().toStdString() << std::endl;
    _readPlugins.append(plugin);
    ui->menu_Read->addAction(plugin->name(), plugin, SLOT(open()));
}

void MainWindow::loadWritePlugin(WritePlugin *plugin) {
    std::cout << "Loading Write Plugin: " << plugin->name().toStdString() << std::endl;
    _writePlugins.append(plugin);
    ui->menu_Write->addAction(plugin->name(), plugin, SLOT(save()));
}

void MainWindow::refreshTree()
{
    QStandardItemModel *model = new QStandardItemModel();

    // Caches
    QStandardItem *caches = new QStandardItem("Caches");
    caches->setData(QVariant::fromValue<int>(TREE_CATEGORY_CACHES), Qt::UserRole);
    model->appendRow(caches);
    foreach (int i, _db->getCacheIDs()) {
        Cache cache(_db, i);
        QStandardItem *item = new QStandardItem(cache.treeDisplay());
        item->setData(QVariant::fromValue<int>(cache.getID()), Qt::UserRole);
        caches->appendRow(item);
    }

    // Waypoints
    QStandardItem *waypoints = new QStandardItem("Waypoints");
    waypoints->setData(QVariant::fromValue<int>(TREE_CATEGORY_WAYPOINTS), Qt::UserRole);
    model->appendRow(waypoints);
    foreach (int i, _db->getWaypointIDs()) {
        Waypoint waypoint(_db, i);
        QStandardItem *item = new QStandardItem(waypoint.treeDisplay());
        item->setData(QVariant::fromValue<int>(waypoint.getID()), Qt::UserRole);
        waypoints->appendRow(item);
    }

    ui->tree->setModel(model);
    ui->tree->expandAll();
}

void MainWindow::on_tree_clicked(QModelIndex index)
{
    QVariant data = index.data(Qt::UserRole);
    QModelIndex parent = index.parent();
    if (parent.isValid()) {
        // Item
        QVariant parent_data = parent.data(Qt::UserRole);
        std::cout << "Found Item ";
        if (data.canConvert<int>())
            std::cout << data.value<int>();
        else
            std::cout << "invalid";
        std::cout << " with parent ";
        if (parent_data.canConvert<int>())
            std::cout << parent_data.value<int>();
        else
            std::cout << "invalid";
        std::cout << std::endl;
    } else {
        // Category
        std::cout << "Found Category ";
        if (data.canConvert<int>())
            std::cout << data.value<int>();
        else
            std::cout << "invalid";
        std::cout << std::endl;
    }
}



void MainWindow::on_comboBox_activated(int index)
{
    // TODO: Get collection ID.
    refreshTree();
}


void MainWindow::on_action_Test_triggered()
{
    QVariant q1 = 42;
    QVariant q2 = QVariant::fromValue<TreeItemIdentifier>(TreeItemIdentifier(_db, TREE_TYPE_CATEGORY, TREE_CATEGORY_CACHES));
    std::cout << "q1: " << (q1.canConvert<int>() ? "yes" : "no") << std::endl;
    std::cout << "q2: " << (q2.canConvert<TreeItemIdentifier>() ? "yes" : "no") << std::endl;
    std::cout << q2.value<TreeItemIdentifier>().categoryName().toStdString() << std::endl;
    QStandardItem *caches = new QStandardItem("Caches");
    caches->setData(QVariant::fromValue<int>(41));
    std::cout << "int: " << (caches->data().canConvert<int>() ? "yes" : "no") << std::endl;
    std::cout << caches->data().value<int>() << std::endl;
}
