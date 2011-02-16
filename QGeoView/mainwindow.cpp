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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treemodel.h"
#include "interfaces.h"

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


/*
 Test function for developement
 Called when "Test" is clicked on the toolbar
*/
void MainWindow::on_actionTest_triggered()
{
    std::cout << "Test Button Does Nothing" << std::endl;
    _db->populate();
}

/*
 Generates the "open dialog" and then sends the file for parsing.
 TODO: pick an appropriate ReadPlugin to use
*/
void MainWindow::on_action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    if (filename.isNull())
        return;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }
    file.close();
}


/*
 Generates the "save dialog" and saves the database.
 TODO: make it ask for a collection ID.
*/
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
    WritePlugin *writer; // TODO: Get one!
    writer->write(file, 0);  // TODO: replace 0 with collection_id
    file.close();
}

void MainWindow::loadPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cdUp();
    pluginsDir.cdUp();
    pluginsDir.cd("plugins");
    pluginsDir.cd("bin");
    std::cout << "Loading plugins from " << pluginsDir.absolutePath().toStdString() << std::endl;
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        std::cout << "Loading from " << pluginsDir.absoluteFilePath(fileName).toStdString() << std::endl;
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            ReadPluginFactory *readPluginFactory = qobject_cast<ReadPluginFactory*>(plugin);
            if (readPluginFactory)
                ReadPlugin *plugin = readPluginFactory->get_plugin();
                //loadReadPlugin(readPluginFactory->get_plugin(_db));
            else
                std::cout << "Not a ReadPluginFactory" << std::endl;
        } else
            std::cout << "Loading " << fileName.toStdString() << " failed: " << pluginLoader.errorString().toStdString() << std::endl;
    }
    std::cout << "Found: " << std::endl;
    std::cout << "\tRead Plugins: \t" << _readPlugins.count() << std::endl;
    std::cout << "\tWrite Plugins:\t" << _readPlugins.count() << std::endl;
    std::cout << "\tMode Plugins: \t" << _readPlugins.count() << std::endl;
}

void MainWindow::loadReadPlugin(ReadPlugin *plugin) {
    std::cout << "loading Read plugin: " << plugin->name().toStdString();
    _readPlugins.append(plugin);
}

void MainWindow::loadWritePlugin(WritePlugin *plugin) {
    std::cout << "loading Write plugin: " << plugin->name().toStdString();
    _writePlugins.append(plugin);
}

void MainWindow::loadModePlugin(ModePlugin *plugin) {
    std::cout << "loading Mode plugin: " << plugin->name().toStdString();
    _modePlugins.append(plugin);
}
