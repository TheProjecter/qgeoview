#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>
#include <QSqlDatabase>
#include <QString>
#include <QFile>

#include "db/database.h"

#define COMPATIBLE_NO       0
#define COMPATIBLE_YES      1
#define COMPATIBLE_MAYBE    2

class ReadPlugin
{
public:
    virtual void setup(Database *db) = 0;
    virtual QString name() = 0;
    virtual void read(QFile *file) = 0;
private:
    Database *_db;
};

class WritePlugin
{
public:
    WritePlugin(Database *db);
    QString name() { return "Abstract"; }
    void write(QFile &file, int collection) {}
private:
    Database *_db;
};

class ModePlugin
{
public:
    virtual QString name() = 0;
public slots:
    void start() {};
    void stop() {};
    void activate() {};
    void deactivate() {};
    void selected() {};
    void deselected() {};
};

class ReadPluginFactory
{
public:
    virtual ~ReadPluginFactory() = 0;
    virtual ReadPlugin *get_plugin() = 0;
    virtual ReadPlugin *get_plugin(Database *db) = 0;
};

class WritePluginFactory
{
public:
    virtual WritePlugin *get_plugin(Database *db) = 0;
};

class ModePluginFactory
{
public:
    virtual ModePlugin *get_plugin() = 0;
};

Q_DECLARE_INTERFACE(ReadPluginFactory, "org.homelinux.darwinsurvivor.QGeoView.ReadPluginFactory");
Q_DECLARE_INTERFACE(WritePluginFactory, "org.homelinux.darwinsurvivor.QGeoView.WritePluginFactory");
Q_DECLARE_INTERFACE(ModePluginFactory, "org.homelinux.darwinsurvivor.QGeoView.ModePluginFactory");

#endif
