#ifndef READPLUGIN_H
#define READPLUGIN_H

#include <QtPlugin>

#include "db/database.h"

class ReadPlugin : public QObject
{
    Q_OBJECT
public:
    ReadPlugin(Database *db);
    virtual QString name() = 0;
public slots:
    virtual void open() = 0;
protected:
    Database *_db;
};

class ReadPluginFactory
{
public:
    virtual ReadPlugin *get_plugin(Database *db) = 0;
};

Q_DECLARE_INTERFACE(ReadPluginFactory, "org.homelinux.darwinsurvivor.QGeoView.ReadPluginFactory");

#endif // READPLUGIN_H
