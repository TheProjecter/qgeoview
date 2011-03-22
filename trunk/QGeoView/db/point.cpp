#include <QVariant>
#include <QStringList>
#include <iostream>
#include "point.h"
#include "exceptions.h"

Point::Point(QSqlDatabase *db, int id) :
    DatabaseObject(db, id)
{
    if (id)
        load();
}

Point::Point(QSqlDatabase *db, QSqlQuery query) :
    DatabaseObject(db)
{
    loadValues(query, true);
}

QString Point::table()
{
    return Point::tableName();
}

QString Point::tableName()
{
    return "Point";
}

QStringList Point::fields()
{
    return Point::fieldNames();
}

QStringList Point::fieldNames()
{
    QStringList list;
    list << "time" << "elevation" << "magneticVariation" << "geoIDHeight" << "symbol" << "fix" << "satelites" << "horizontalDOP" << "verticalDOP" << "positionDOP" << "ageofDGPSData" << "DGPSID" << "latitude" << "longitude";
    return list;
}

void Point::addBindValues(QSqlQuery query)
{
    query.addBindValue(isSet(NULLMASK_POINT_TIME) ? _time : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_POINT_ELEVATION) ? _elevation : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_MAGNETICVARIATION) ? _magnetic_variation : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_GEOIDHEIGHT) ? _geo_id_height: QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_SYMBOL) ? _symbol : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_POINT_FIX) ? _fix : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_POINT_SATELITES) ? _satelites : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_POINT_HORIZONTALDOP) ? _horizontal_dop : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_VERTICALDOP) ? _vertical_dop: QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_POSITIONDOP) ? _position_dop: QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_AGEOFDGPSDATA) ? _age_of_dgps_data: QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_DGPSID) ? _dgps_id: QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_POINT_LATITUDE) ? _latitude : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_LONGITUDE) ? _longitude : QVariant(QVariant::Double));
}

void Point::loadValues(QSqlQuery query, bool loadID)
{
    int i=-1;
    if (loadID)
        setID(query.value(++i).toInt());
    if (query.value(++i).isValid())
        setTime(query.value(i).toString());
    if (query.value(++i).isValid())
        setElevation(query.value(i).toDouble());
    if (query.value(++i).isValid())
        setMagneticVariation(query.value(i).toDouble());
    if (query.value(++i).isValid())
        setGeoIDHeight(query.value(i).toDouble());
    if (query.value(++i).isValid())
        setSymbol(query.value(i).toString());
    if (query.value(++i).isValid())
        setFix(query.value(i).toString());
    if (query.value(++i).isValid())
        setSatelites(query.value(i).toInt());
    if (query.value(++i).isValid())
        setHorizontalDOP(query.value(i).toDouble());
    if (query.value(++i).isValid())
        setVerticalDOP(query.value(i).toDouble());
    if (query.value(++i).isValid())
        setPositionDOP(query.value(i).toDouble());
    if (query.value(++i).isValid())
        setAgeOfDGPSData(query.value(i).toDouble());
    if (query.value(++i).isValid())
        setDGPSID(query.value(i).toInt());
    if (query.value(++i).isValid())
        setLatitude(query.value(i).toDouble());
    if (query.value(++i).isValid())
        setLongitude(query.value(i).toDouble());
}

void Point::setTime(QString time)
{
    set(NULLMASK_POINT_TIME);
    _time = time;
}

QString Point::getTime()
{
    ensure(NULLMASK_POINT_TIME);
    return _time;
}

void Point::setSymbol(QString symbol)
{
    set(NULLMASK_POINT_SYMBOL);
    _symbol = symbol;
}

QString Point::getSymbol()
{
    ensure(NULLMASK_POINT_SYMBOL);
    return _symbol;
}

void Point::setFix(QString fix)
{
    set(NULLMASK_POINT_FIX);
    _fix = fix;
}

QString Point::getFix()
{
    ensure(NULLMASK_POINT_FIX);
    return _fix;
}

void Point::setElevation(float elevation)
{
    set(NULLMASK_POINT_ELEVATION);
    _elevation = elevation;
}

float Point::getElevation()
{
    ensure(NULLMASK_POINT_ELEVATION);
    return _elevation;
}

void Point::setMagneticVariation(float magnetic_variation)
{
    set(NULLMASK_POINT_MAGNETICVARIATION);
    _magnetic_variation = magnetic_variation;
}

float Point::getMagneticVariation()
{
    ensure(NULLMASK_POINT_MAGNETICVARIATION);
    return _magnetic_variation;
}

void Point::setGeoIDHeight(float geo_id_height)
{
    set(NULLMASK_POINT_GEOIDHEIGHT);
    _geo_id_height = geo_id_height;
}

float Point::getGeoIDHeight()
{
    ensure(NULLMASK_POINT_GEOIDHEIGHT);
    return _geo_id_height;
}

void Point::setLatitude(float latitude)
{
    set(NULLMASK_POINT_LATITUDE);
    _latitude = latitude;
}

float Point::getLatitude()
{
    ensure(NULLMASK_POINT_LATITUDE);
    return _latitude;
}

void Point::setLongitude(float longitude)
{
    set(NULLMASK_POINT_LONGITUDE);
    _longitude = longitude;
}

float Point::getLongitude()
{
    ensure(NULLMASK_POINT_LONGITUDE);
    return _longitude;
}

void Point::setHorizontalDOP(float horizontal_dop)
{
    set(NULLMASK_POINT_HORIZONTALDOP);
    _horizontal_dop = horizontal_dop;
}

float Point::getHorizontalDOP()
{
    ensure(NULLMASK_POINT_HORIZONTALDOP);
    return _horizontal_dop;
}

void Point::setVerticalDOP(float vertical_dop)
{
    set(NULLMASK_POINT_VERTICALDOP);
    _vertical_dop = vertical_dop;
}

float Point::getVerticalDOP()
{
    ensure(NULLMASK_POINT_VERTICALDOP);
    return _vertical_dop;
}

void Point::setPositionDOP(float position_dop)
{
    set(NULLMASK_POINT_POSITIONDOP);
    _position_dop = position_dop;
}

float Point::getPositionDOP()
{
    ensure(NULLMASK_POINT_POSITIONDOP);
    return _position_dop;
}

void Point::setAgeOfDGPSData(float age_of_dgps_data)
{
    set(NULLMASK_POINT_AGEOFDGPSDATA);
    _age_of_dgps_data = age_of_dgps_data;
}

float Point::getAgeOfDGPSData()
{
    ensure(NULLMASK_POINT_AGEOFDGPSDATA);
    return _age_of_dgps_data;
}

void Point::setSatelites(int satelites)
{
    set(NULLMASK_POINT_SATELITES);
    _satelites = satelites;
}

int Point::getSatelites()
{
    ensure(NULLMASK_POINT_SATELITES);
    return _satelites;
}

void Point::setDGPSID(int dgps_id)
{
    set(NULLMASK_POINT_DGPSID);
    _dgps_id = dgps_id;
}

int Point::getDGPSID()
{
    ensure(NULLMASK_POINT_DGPSID);
    return _dgps_id;
}

