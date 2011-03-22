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
        setQStringValue(NULLMASK_POINT_TIME, query.value(i).toString());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_POINT_ELEVATION, query.value(i).toDouble());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_POINT_MAGNETICVARIATION, query.value(i).toDouble());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_POINT_GEOIDHEIGHT, query.value(i).toDouble());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_POINT_SYMBOL, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_POINT_FIX, query.value(i).toString());
    if (query.value(++i).isValid())
        setIntValue(NULLMASK_POINT_SATELITES, query.value(i).toInt());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_POINT_HORIZONTALDOP, query.value(i).toDouble());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_POINT_VERTICALDOP, query.value(i).toDouble());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_POINT_POSITIONDOP, query.value(i).toDouble());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_POINT_AGEOFDGPSDATA, query.value(i).toDouble());
    if (query.value(++i).isValid())
        setIntValue(NULLMASK_POINT_DGPSID, query.value(i).toInt());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_POINT_LATITUDE, query.value(i).toDouble());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_POINT_LONGITUDE, query.value(i).toDouble());
}

void Point::setQStringValue(int mask, QString value)
{
    switch(mask) {
        case NULLMASK_POINT_TIME:
            _time = value;
            break;
        case NULLMASK_POINT_SYMBOL:
            _symbol = value;
            break;
        case NULLMASK_POINT_FIX:
            _fix = value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "QString");
    }
    set(mask);
}

void Point::setFloatValue(int mask, float value)
{
    switch(mask) {
        case NULLMASK_POINT_ELEVATION:
            _elevation = value;
            break;
        case NULLMASK_POINT_MAGNETICVARIATION:
            _magnetic_variation = value;
            break;
        case NULLMASK_POINT_GEOIDHEIGHT:
            _geo_id_height = value;
            break;
        case NULLMASK_POINT_LATITUDE:
            _latitude = value;
            break;
        case NULLMASK_POINT_LONGITUDE:
            _longitude = value;
            break;
        case NULLMASK_POINT_HORIZONTALDOP:
            _horizontal_dop = value;
            break;
        case NULLMASK_POINT_VERTICALDOP:
            _vertical_dop= value;
            break;
        case NULLMASK_POINT_POSITIONDOP:
            _position_dop= value;
            break;
        case NULLMASK_POINT_AGEOFDGPSDATA:
            _age_of_dgps_data= value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "Float");
    }
    set(mask);
}

void Point::setIntValue(int mask, int value)
{
    switch(mask) {
        case NULLMASK_POINT_SATELITES:
            _satelites = value;
            break;
        case NULLMASK_POINT_DGPSID:
            _dgps_id= value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "Int");
    }
    set(mask);
}

QString Point::getQStringValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "QString");
    switch(mask) {
        case NULLMASK_POINT_TIME:
            return _time;
        case NULLMASK_POINT_SYMBOL:
            return _symbol;
        case NULLMASK_POINT_FIX:
            return _fix;
        }
    throw MaskNotFoundException(this, mask, "QString");
}

float Point::getFloatValue(int mask)
{
    if(!isSet(mask))
        throw DBValueNotSetException(this, mask, "Float");
    switch(mask) {
        case NULLMASK_POINT_ELEVATION:
            return _elevation;
        case NULLMASK_POINT_MAGNETICVARIATION:
            return _magnetic_variation;
        case NULLMASK_POINT_GEOIDHEIGHT:
            return _geo_id_height;
        case NULLMASK_POINT_LATITUDE:
            return _latitude;
        case NULLMASK_POINT_LONGITUDE:
            return _longitude;
        case NULLMASK_POINT_HORIZONTALDOP:
            return _horizontal_dop;
        case NULLMASK_POINT_VERTICALDOP:
            return _vertical_dop;
        case NULLMASK_POINT_POSITIONDOP:
            return _position_dop;
        case NULLMASK_POINT_AGEOFDGPSDATA:
            return _age_of_dgps_data;
    }
    throw MaskNotFoundException(this, mask, "Float");
}

int Point::getIntValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "Int");
    switch(mask) {
        case NULLMASK_POINT_SATELITES:
            return _satelites;
        case NULLMASK_POINT_DGPSID:
            return _dgps_id;
    }
    throw MaskNotFoundException(this, mask, "Int");
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

