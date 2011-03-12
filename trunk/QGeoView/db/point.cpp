#include "point.h"

Point::Point(Database *db, int id) :
    DatabaseObject(db, id)
{
    if (id)
        load();
}

Point::Point(const Point &original) :
    DatabaseObject(original),
    _time(original._time),
    _symbol(original._symbol),
    _fix(original._fix),
    _elevation(original._elevation),
    _magneticVariation(original._elevation),
    _geoIDHeight(original._geoIDHeight),
    _latitude(original._latitude),
    _longitude(original._longitude),
    _horizontalDOP(original._horizontalDOP),
    _verticalDOP(original._verticalDOP),
    _positionDOP(original._positionDOP),
    _ageOfDGPSData(original._ageOfDGPSData),
    _satelites(original._satelites),
    _DGPSID(original._DGPSID)
{
}

QString Point::table()
{
    return "Point";
}

QStringList Point::fields()
{
    QStringList list;
    list << "time" << "elevation" << "magneticVariation" << "geoIDHeight" << "symbol" << "fix" << "satelites" << "horizontalDOP" << "verticalDOP" << "positionDOP" << "ageofDGPSData" << "DGPSID" << "latitude" << "longitude";
    return list;
}

void Point::addBindValues(QSqlQuery query)
{
    query.addBindValue(isSet(NULLMASK_POINT_TIME) ? _time : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_POINT_ELEVATION) ? _elevation : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_MAGNETICVARIATION) ? _magneticVariation : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_GEOIDHEIGHT) ? _geoIDHeight : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_SYMBOL) ? _symbol : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_POINT_FIX) ? _fix : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_POINT_SATELITES) ? _satelites : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_POINT_HORIZONTALDOP) ? _horizontalDOP : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_VERTICALDOP) ? _verticalDOP : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_POSITIONDOP) ? _positionDOP : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_AGEOFDGPSDATA) ? _ageOfDGPSData : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_DGPSID) ? _DGPSID : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_POINT_LATITUDE) ? _latitude : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POINT_LONGITUDE) ? _longitude : QVariant(QVariant::Double));
}

void Point::loadValues(QSqlQuery query)
{
    int i=0;
    _time = query.value(i++).toString();
    _elevation = query.value(i++).toDouble();
    _magneticVariation = query.value(i++).toDouble();
    _geoIDHeight = query.value(i++).toDouble();
    _symbol = query.value(i++).toString();
    _fix = query.value(i++).toString();
    _satelites = query.value(i++).toInt();
    _horizontalDOP = query.value(i++).toDouble();
    _verticalDOP = query.value(i++).toDouble();
    _positionDOP = query.value(i++).toDouble();
    _ageOfDGPSData = query.value(i++).toDouble();
    _DGPSID = query.value(i++).toInt();
    _latitude = query.value(i++).toDouble();
    _longitude = query.value(i++).toDouble();
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
            _magneticVariation = value;
            break;
        case NULLMASK_POINT_GEOIDHEIGHT:
            _geoIDHeight = value;
            break;
        case NULLMASK_POINT_LATITUDE:
            _latitude = value;
            break;
        case NULLMASK_POINT_LONGITUDE:
            _longitude = value;
            break;
        case NULLMASK_POINT_HORIZONTALDOP:
            _horizontalDOP = value;
            break;
        case NULLMASK_POINT_VERTICALDOP:
            _verticalDOP = value;
            break;
        case NULLMASK_POINT_POSITIONDOP:
            _positionDOP = value;
            break;
        case NULLMASK_POINT_AGEOFDGPSDATA:
            _ageOfDGPSData = value;
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
            _DGPSID = value;
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
            return _magneticVariation;
        case NULLMASK_POINT_GEOIDHEIGHT:
            return _geoIDHeight;
        case NULLMASK_POINT_LATITUDE:
            return _latitude;
        case NULLMASK_POINT_LONGITUDE:
            return _longitude;
        case NULLMASK_POINT_HORIZONTALDOP:
            return _horizontalDOP;
        case NULLMASK_POINT_VERTICALDOP:
            return _verticalDOP;
        case NULLMASK_POINT_POSITIONDOP:
            return _positionDOP;
        case NULLMASK_POINT_AGEOFDGPSDATA:
            return _ageOfDGPSData;
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
            return _DGPSID;
    }
    throw MaskNotFoundException(this, mask, "Int");
}
