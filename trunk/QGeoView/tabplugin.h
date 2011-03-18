#ifndef TABPLUGIN_H
#define TABPLUGIN_H

#include <QWidget>
#include <QTabWidget>

#include "db/cache.h"
#include "db/waypoint.h"
#include "db/collection.h"

class TabPlugin : public QWidget
{
    Q_OBJECT
public:
    TabPlugin(QSqlDatabase *db, QTabWidget *pluginsTabWidget);
    ~TabPlugin();
    virtual QString name() = 0;
    int active();
public slots:
    void toggle();
    void activate();
    void deactivate();
    void selectCache(Cache cache);
    void selectWaypoint(Waypoint waypoint);
    void selectCollection(Collection collection);
    void selectAllCollections();
    void selectNoCollections();
protected:
    QSqlDatabase *_db;
    QTabWidget *_pluginsTabWidget;
    bool _active;
};

class TabPluginFactory
{
public:
    virtual TabPlugin *get_plugin(QSqlDatabase *db, QTabWidget *pluginsTabWidget) = 0;
};

Q_DECLARE_INTERFACE(TabPluginFactory, "org.homelinux.darwinsurvivor.QGeoView.TabPluginFactory");

#endif // TABPLUGIN_H
