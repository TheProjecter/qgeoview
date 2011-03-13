#ifndef WRITEPLUGIN_H
#define WRITEPLUGIN_H

#include <QtPlugin>

#include "db/database.h"
#include "db/point.h"

class WritePlugin : public QObject
{
    Q_OBJECT
public:
    WritePlugin(Database *db);
    virtual QString name() = 0;
public slots:
    virtual void save() = 0;
protected:
    Database *_db;
};

class WritePluginFactory
{
public:
    virtual WritePlugin *get_plugin(Database *db) = 0;
};

Q_DECLARE_INTERFACE(WritePluginFactory, "org.homelinux.darwinsurvivor.QGeoView.WritePluginFactory");

#endif // WRITEPLUGIN_H
