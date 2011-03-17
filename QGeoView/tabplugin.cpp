#include <iostream>
#include "tabplugin.h"

TabPlugin::TabPlugin(Database *db, QTabWidget *pluginsTabWidget) :
    _db(db),
    _pluginsTabWidget(pluginsTabWidget),
    _active(false),
    _tab_id(0)
{
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
    _tab_id = _pluginsTabWidget->addTab(this, name());
    this->show();
}

void TabPlugin::deactivate()
{
    if (!_active)
        return;
    // TODO: Deactivate myself
    _active = false;
    this->hide();
    _pluginsTabWidget->removeTab(_tab_id);
    _tab_id = 0;
}

void TabPlugin::selectCache(Cache cache)
{
    Q_UNUSED(cache)
}

void TabPlugin::selectWaypoint(Waypoint waypoint)
{
    Q_UNUSED(waypoint)
}

void TabPlugin::selectCollection(Collection collection)
{
    Q_UNUSED(collection)
}

void TabPlugin::selectNoCollections()
{}


void TabPlugin::selectAllCollections()
{}

