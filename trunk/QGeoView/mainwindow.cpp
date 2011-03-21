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
    if (!_settings->value("installed", false).toBool()) {
        firstRun();
    }

    // Database
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(_settings->value("database/location").toString());
    if (!_db.open())
        std::cerr << "Error Connecting to Database: " << _settings->value("database/location").toString().toStdString() << std::endl;
    
    // UI
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/application.svg"));

    // Collection Selector
    _collection_selector_model = new CollectionSelectorModel(&_db, true);
    ui->collections->setModel(_collection_selector_model);

    // Item Tree
    _item_tree_model = new TreeModel(&_db);
    ui->tree->setModel(_item_tree_model);
    ui->tree->expandAll();

    // Connections
    connect(ui->collections, SIGNAL(currentIndexChanged(int)), _collection_selector_model, SLOT(indexChanged(int)));
    connect(ui->tree, SIGNAL(clicked(QModelIndex)), _item_tree_model, SLOT(itemSelected(QModelIndex)));
    connect(_collection_selector_model, SIGNAL(collectionSelected(int)), _item_tree_model, SLOT(showCollection(int)));
    connect(_collection_selector_model, SIGNAL(noneSelected()), _item_tree_model, SLOT(showAll()));
    connect(_collection_selector_model, SIGNAL(allSelected()), _item_tree_model, SLOT(showAll()));
    connect(_collection_selector_model, SIGNAL(noneSelected()), _item_tree_model, SLOT(showNone()));
    connect(_collection_selector_model, SIGNAL(refreshed()), _item_tree_model, SLOT(refresh()));
    _collection_selector_model->refresh();

    // Plugins
    loadPlugins();
}

/*
 Removes private variables from memory.
*/
MainWindow::~MainWindow()
{
    _db.close();
    delete _settings;
    delete ui;
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
    if (!dir.mkpath(QDesktopServices::storageLocation(QDesktopServices::DataLocation))) {
        std::cerr << "Error creating dataStorage folder" << std::endl;
    }
    dir.cd(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    if (!dir.mkdir("plugins")) {
        std::cerr << "Error creating plugins folder" << std::endl;
    }

    // Empty DB File
    std::cout << "copying database to " << _settings->value("database/location").toString().toStdString() << std::endl;
    QFile(":/db/db.sqlite3.empty").copy(_settings->value("database/location").toString());
    QFile::setPermissions(_settings->value("database/location").toString(), QFile::ReadOwner | QFile::WriteOwner);
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
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            ReadPluginFactory *readPluginFactory = qobject_cast<ReadPluginFactory*>(plugin);
            WritePluginFactory *writePluginFactory = qobject_cast<WritePluginFactory*>(plugin);
            TabPluginFactory *tabPluginFactory = qobject_cast<TabPluginFactory*>(plugin);
            if (readPluginFactory)
                loadReadPlugin(readPluginFactory->get_plugin(&_db));
            if (writePluginFactory)
                loadWritePlugin(writePluginFactory->get_plugin(&_db));
            if (tabPluginFactory)
                loadTabPlugin(tabPluginFactory->get_plugin(&_db, ui->tabPluginsWidget));
        } else {
            std::cout << "Loading " << fileName.toStdString() << " failed: " << pluginLoader.errorString().toStdString() << std::endl;
        }
    }
    std::cout << "Found: " << std::endl;
    std::cout << "\tRead Plugins: \t" << _readPlugins.count() << std::endl;
    std::cout << "\tWrite Plugins: \t" << _writePlugins.count() << std::endl;
    std::cout << "\tTab Plugins: \t" << _tabPlugins.count() << std::endl;
}

void MainWindow::loadReadPlugin(ReadPlugin *plugin) {
    _readPlugins.append(plugin);
    ui->menu_Read->addAction(plugin->name(), plugin, SLOT(open()));
    connect(plugin, SIGNAL(done()), _item_tree_model, SLOT(refresh()));
    connect(plugin, SIGNAL(done()), _collection_selector_model, SLOT(refresh()));
}

void MainWindow::loadWritePlugin(WritePlugin *plugin) {
    _writePlugins.append(plugin);
    ui->menu_Write->addAction(plugin->name(), plugin, SLOT(save()));
}

void MainWindow::loadTabPlugin(TabPlugin *plugin) {
    _tabPlugins.append(plugin);
    ui->menu_Plugins->addAction(plugin->name(), plugin, SLOT(toggle()));
    connect(_item_tree_model, SIGNAL(cacheSelected(Cache*)), plugin, SLOT(selectCache(Cache*)));
    connect(_item_tree_model, SIGNAL(waypointSelected(Waypoint*)), plugin, SLOT(selectWaypoint(Waypoint*)));
    connect(_collection_selector_model, SIGNAL(collectionSelected(int)), plugin, SLOT(selectCollection(int)));
    connect(_collection_selector_model, SIGNAL(allSelected()), plugin, SLOT(selectAllCollections()));
    connect(_collection_selector_model, SIGNAL(noneSelected()), plugin, SLOT(selectNoCollections()));
}
