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

#include <iostream>
#include <QDateTime>

#include "mainwindow.h"
#include "details_tab.h"
#include "db/log.h"

DetailsTabPlugin::DetailsTabPlugin(QSqlDatabase *db, QTabWidget *pluginsTabWidget) :
    TabPlugin(db, pluginsTabWidget)
{
    ui.setupUi(this);
    connect(ui.description_link, SIGNAL(clicked()), this, SLOT(open_description_link()));
    connect(ui.logs_selector, SIGNAL(currentIndexChanged(int)), this, SLOT(selectLogIndex(int)));
}

QString DetailsTabPlugin::name()
{
    return "Details";
}

void DetailsTabPlugin::selectCache(Cache *cache)
{
    if (!_active)
        return;
    setCacheData(cache);
    setLogsData(cache->getLogIDs());
    selectWaypoint(cache->getWaypoint());
}

void DetailsTabPlugin::selectWaypoint(Waypoint *waypoint)
{
    if (!_active)
        return;
    Point *point = waypoint->getPoint();
    Description *description = waypoint->getDescription();
    setPointData(point);
    setAccuracyData(point);
    setDescriptionData(description);
}

void DetailsTabPlugin::setCacheData(Cache *cache)
{
    if (cache->isSet(NULLMASK_CACHE_NAME)) {
        ui.cache_name->show();
        ui.cache_name->setText(cache->getName());
    } else
        ui.cache_name->hide();

    if (cache->isSet(NULLMASK_CACHE_PLACEDBY)) {
        ui.cache_placedby->show();
        ui.cache_placedby->setText(cache->getPlacedBy());
    } else
        ui.cache_placedby->hide();

    if (cache->isSet(NULLMASK_CACHE_OWNERNAME)) {
        ui.cache_owner->show();
        ui.cache_owner->setText(cache->getOwnerName());
    } else
        ui.cache_owner->hide();

    if (cache->isSet(NULLMASK_CACHE_TYPE)) {
        ui.cache_type->show();
        ui.cache_type->setText(cache->getType());
    } else
        ui.cache_type->hide();

    if (cache->isSet(NULLMASK_CACHE_CONTAINER)) {
        ui.cache_container->show();
        ui.cache_container->setText(cache->getContainer());
    } else
        ui.cache_container->hide();

    if (cache->isSet(NULLMASK_CACHE_DIFFICULTY)) {
        ui.cache_difficulty->show();
        ui.cache_difficulty->setValue(cache->getDifficulty());
    } else
        ui.cache_difficulty->hide();

    if (cache->isSet(NULLMASK_CACHE_TERRAIN)) {
        ui.cache_terrain->show();
        ui.cache_terrain->setValue(cache->getTerrain());
    } else
        ui.cache_terrain->hide();

    if (cache->isSet(NULLMASK_CACHE_COUNTRY)) {
        ui.cache_country->show();
        ui.cache_country->setText(cache->getCountry());
    } else
        ui.cache_country->hide();

    if (cache->isSet(NULLMASK_CACHE_STATE)) {
        ui.cache_state->show();
        ui.cache_state->setText(cache->getState());
    } else
        ui.cache_state->hide();

    if (cache->isSet(NULLMASK_CACHE_SHORTDESCRIPTION)) {
        ui.cache_shortdescription->show();
        if (cache->isSet(NULLMASK_CACHE_SHORTDESCRIPTIONHTML) ? cache->getShortDescriptionHTML() : false)
            ui.cache_shortdescription->setHtml(cache->getShortDescription());
        else
            ui.cache_shortdescription->setText(cache->getShortDescription());
    } else
        ui.cache_shortdescription->hide();

    if (cache->isSet(NULLMASK_CACHE_LONGDESCRIPTION)) {
        ui.cache_longdescription->show();
        if (cache->isSet(NULLMASK_CACHE_LONGDESCRIPTIONHTML) ? cache->getLongDescriptionHTML() : false)
            ui.cache_longdescription->setHtml(cache->getLongDescription());
        else
            ui.cache_longdescription->setText(cache->getLongDescription());
    } else
        ui.cache_longdescription->hide();

    if (cache->isSet(NULLMASK_CACHE_ENCODEDHINTS)) {
        ui.cache_encodedhints->show();
        ui.cache_encodedhints->setText(cache->getEncodedHints());
    } else
        ui.cache_encodedhints->hide();
}

void DetailsTabPlugin::setDescriptionData(Description *description)
{
    if (description->isSet(NULLMASK_DESCRIPTION_NAME)) {
        ui.description_name->show();
        ui.description_name->setText(description->getName());
    } else
        ui.description_name->hide();

    if (description->isSet(NULLMASK_DESCRIPTION_LINKNAME)) {
        ui.description_link->show();
        ui.description_link->setText(description->getLinkName());
    } else
        ui.description_link->hide();

    if (description->isSet(NULLMASK_DESCRIPTION_LINKURL))
        _link_url = description->getLinkURL();
    else
        _link_url = "";

    if (description->isSet(NULLMASK_DESCRIPTION_COMMENTS)) {
        ui.description_comments->show();
        ui.description_comments->setText(description->getComments());
    } else
        ui.description_comments->hide();

    if (description->isSet(NULLMASK_DESCRIPTION_SOURCE)) {
        ui.description_source->show();
        ui.description_source->setText(description->getSource());
    } else
        ui.description_source->hide();

    if (description->isSet(NULLMASK_DESCRIPTION_TYPE)) {
        ui.description_type->show();
        ui.description_type->setText(description->getType());
    } else
        ui.description_type->hide();
}

void DetailsTabPlugin::setPointData(Point *point)
{
    if (point->isSet(NULLMASK_POINT_LATITUDE)) {
        ui.point_latitude->show();
        ui.point_latitude->setValue(point->getLatitude());
    } else
        ui.point_latitude->hide();

    if (point->isSet(NULLMASK_POINT_LONGITUDE)) {
        ui.point_longitude->show();
        ui.point_longitude->setValue(point->getLongitude());
    } else
        ui.point_longitude->hide();

    if (point->isSet(NULLMASK_POINT_TIME)) {
        ui.point_time->show();
        ui.point_time->setDateTime(QDateTime::fromString(point->getTime(), Qt::ISODate));  // TODO: convert QString to datetime.
    } else
        ui.point_time->hide();

    if (point->isSet(NULLMASK_POINT_ELEVATION)) {
        ui.point_elevation->show();
        ui.point_elevation->setValue(point->getElevation());
    } else
        ui.point_elevation->hide();

    if (point->isSet(NULLMASK_POINT_GEOIDHEIGHT)) {
        ui.point_geoidheight->show();
        ui.point_geoidheight->setValue(point->getGeoIDHeight());
    } else
        ui.point_geoidheight->hide();

    if (point->isSet(NULLMASK_POINT_SYMBOL)) {
        ui.point_symbol->show();
        ui.point_symbol->setText(point->getSymbol());
    } else
        ui.point_symbol->hide();
}

void DetailsTabPlugin::setAccuracyData(Point *point)
{
    if (point->isSet(NULLMASK_POINT_FIX)) {
        ui.accuracy_fix->show();
        ui.accuracy_fix->setText(point->getFix());
    } else
        ui.accuracy_fix->hide();

    if (point->isSet(NULLMASK_POINT_MAGNETICVARIATION)) {
        ui.accuracy_magvar->show();
        ui.accuracy_magvar->setValue(point->getMagneticVariation());
    } else
        ui.accuracy_magvar->hide();

    if (point->isSet(NULLMASK_POINT_HORIZONTALDOP)) {
        ui.accuracy_hdop->show();
        ui.accuracy_hdop->setValue(point->getHorizontalDOP());
    } else
        ui.accuracy_hdop->hide();

    if (point->isSet(NULLMASK_POINT_VERTICALDOP)) {
        ui.accuracy_vdop->show();
        ui.accuracy_vdop->setValue(point->getVerticalDOP());
    } else
        ui.accuracy_vdop->hide();

    if (point->isSet(NULLMASK_POINT_POSITIONDOP)) {
        ui.accuracy_pdop->show();
        ui.accuracy_pdop->setValue(point->getPositionDOP());
    } else
        ui.accuracy_pdop->hide();

    if (point->isSet(NULLMASK_POINT_AGEOFDGPSDATA)) {
        ui.accuracy_ageofdgpsdata->show();
        ui.accuracy_ageofdgpsdata->setValue(point->getAgeOfDGPSData());
    } else
        ui.accuracy_ageofdgpsdata->hide();

    if (point->isSet(NULLMASK_POINT_SATELITES)) {
        ui.accuracy_satelites->show();
        ui.accuracy_satelites->setValue(point->getSatelites());
    } else
        ui.accuracy_satelites->hide();

    if (point->isSet(NULLMASK_POINT_DGPSID)) {
        ui.accuracy_dgpsid->show();
        ui.accuracy_dgpsid->setValue(point->getDGPSID());
    } else
        ui.accuracy_dgpsid->hide();
}

void DetailsTabPlugin::setLogsData(QList<int> logIDs)
{
    ui.logs_selector->clear();
    QSqlQuery query;
    QString query_string("SELECT l.id, l." + Log::fieldNames().join(", l.") + " FROM Log l WHERE l.id IN (");
    bool first=true;
    foreach(int id, logIDs) {
        if (first)
            first = false;
        else
            query_string.append(", ");
        query_string.append(QString::number(id));
    }
    query_string.append(");");
    query.prepare(query_string);
    if (!query.exec())
        throw query;
    while(query.next()) {
        Log log(_db, query);
        ui.logs_selector->addItem(log.summary(), log.getID());
    }
}

void DetailsTabPlugin::selectLogIndex(int index)
{
    Log log(_db, ui.logs_selector->itemData(index, Qt::UserRole).toInt());

    if (log.isSet(NULLMASK_LOG_DATE)) {
        ui.logs_date->show();
        ui.logs_date->setDateTime(QDateTime::fromString(log.getDate()));
    } else
        ui.logs_date->hide();

    if (log.isSet(NULLMASK_LOG_TYPE)) {
        ui.logs_type->show();
        ui.logs_type->setText(log.getType());
    } else
        ui.logs_type->hide();

    if (log.isSet(NULLMASK_LOG_FINDERNAME)) {
        ui.logs_finder->show();
        ui.logs_finder->setText(log.getFinderName());
    } else
        ui.logs_finder->hide();

    if (log.isSet(NULLMASK_LOG_TEXT)) {
        ui.logs_text->show();
        ui.logs_text->setText(log.getText());
    } else
        ui.logs_text->hide();

    if (log.isSet(NULLMASK_LOG_LATITUDE)) {
        ui.logs_latitude->show();
        ui.logs_latitude->setValue(log.getLatitude());
    } else
        ui.logs_latitude->hide();

    if (log.isSet(NULLMASK_LOG_LONGITUDE)) {
        ui.logs_longitude->show();
        ui.logs_longitude->setValue(log.getLongitude());
    } else
        ui.logs_longitude->hide();
}

void DetailsTabPlugin::open_description_link()
{
    // TODO: Open Link!
    if (_link_url.isEmpty())
        return;
    std::cout << "Opening " << _link_url.toStdString() << std::endl;
}

TabPlugin *DetailsTabPluginFactory::get_plugin(QSqlDatabase *db, QTabWidget *pluginsTabWidget)
{
    return new DetailsTabPlugin(db, pluginsTabWidget);
}

Q_EXPORT_PLUGIN2(detailstabpluginfactory, DetailsTabPluginFactory);
