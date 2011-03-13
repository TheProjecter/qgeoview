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
    std::cout << name().toStdString() << " Activated and added to " << _tab_id << std::endl;
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
    std::cout << name().toStdString() << " Deactivated" << std::endl;
}

void TabPlugin::cacheSelected(Cache cache)
{}

void TabPlugin::waypointSelected(Waypoint waypoint)
{}
