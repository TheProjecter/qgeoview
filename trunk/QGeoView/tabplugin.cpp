#include <iostream>
#include "tabplugin.h"

TabPlugin::TabPlugin(QSqlDatabase *db, QTabWidget *pluginsTabWidget) :
    _db(db),
    _pluginsTabWidget(pluginsTabWidget),
    _active(false)
{}

TabPlugin::~TabPlugin()
{
    delete _pluginsTabWidget;
}

void TabPlugin::toggle()
{
    if (_active)
        deactivate();
    else
        activate();
}

void TabPlugin::activate()
{
    if (_active)
        return;
    // TODO: Activate myself
    _active = true;
    _pluginsTabWidget->addTab(this, name());
    this->show();
}

void TabPlugin::deactivate()
{
    if (!_active)
        return;
    // TODO: Deactivate myself
    _active = false;
    this->hide();
    _pluginsTabWidget->removeTab(_pluginsTabWidget->indexOf(this));
}

// The following are unused in case a TabWidget wishes to extends them.
void TabPlugin::selectCache(Cache *cache)
{
    Q_UNUSED(cache)
}

void TabPlugin::selectWaypoint(Waypoint *waypoint)
{
    Q_UNUSED(waypoint)
}

void TabPlugin::selectCollection(Collection *collection)
{
    Q_UNUSED(collection)
}

void TabPlugin::selectNoCollections()
{}


void TabPlugin::selectAllCollections()
{}

