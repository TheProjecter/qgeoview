#ifndef TABPLUGIN_H
#define TABPLUGIN_H

#include <QObject>

#include "db/database.h"

class TabPlugin : public QObject
{
    Q_OBJECT
public:
    TabPlugin(Database *db);
    virtual QString name() = 0;
public slots:
    virtual void toggle() = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
protected:
    Database *_db;
};

class TabPluginFactory
{
public:
    virtual TabPlugin *get_plugin(Database *db) = 0;
};

Q_DECLARE_INTERFACE(TabPluginFactory, "org.homelinux.darwinsurvivor.QGeoView.TabPluginFactory");

#endif // TABPLUGIN_H
