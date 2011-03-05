#include "point.h"

Point::Point(Database *db) :
    DatabaseObject(db)
{
}

Point::~Point()
{
}

QString Point::table()
{
    return "Points";
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

void Point::setQStringValue(int mask, QString value)
{
    if (!((NULLMASK_POINT_TIME | NULLMASK_POINT_SYMBOL | NULLMASK_POINT_FIX) & mask))
        throw InvalidMaskException();
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
            throw MaskNotFoundException();
    }
    set(mask);
}

void Point::setFloatValue(int mask, float value)
{
    if (!((NULLMASK_POINT_ELEVATION | NULLMASK_POINT_MAGNETICVARIATION | NULLMASK_POINT_GEOIDHEIGHT | NULLMASK_POINT_LATITUDE | NULLMASK_POINT_LONGITUDE | NULLMASK_POINT_HORIZONTALDOP | NULLMASK_POINT_VERTICALDOP | NULLMASK_POINT_POSITIONDOP | NULLMASK_POINT_AGEOFDGPSDATA) & mask))
        throw InvalidMaskException();
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
            throw MaskNotFoundException();
    }
    set(mask);
}

void Point::setIntValue(int mask, int value)
{
    if (!((NULLMASK_POINT_SATELITES | NULLMASK_POINT_DGPSID) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_POINT_SATELITES:
            _satelites = value;
            break;
        case NULLMASK_POINT_DGPSID:
            _DGPSID = value;
            break;
        default:
            throw MaskNotFoundException();
    }
    set(mask);
}

QString Point::getQStringValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException();
    if (!((NULLMASK_POINT_TIME | NULLMASK_POINT_SYMBOL | NULLMASK_POINT_FIX) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_POINT_TIME:
            return _time;
        case NULLMASK_POINT_SYMBOL:
            return _symbol;
        case NULLMASK_POINT_FIX:
            return _fix;
        }
    throw MaskNotFoundException();
}

float Point::getFloatValue(int mask)
{
    if(!isSet(mask))
        throw DBValueNotSetException();
    if (!((NULLMASK_POINT_ELEVATION | NULLMASK_POINT_MAGNETICVARIATION | NULLMASK_POINT_GEOIDHEIGHT | NULLMASK_POINT_LATITUDE | NULLMASK_POINT_LONGITUDE | NULLMASK_POINT_HORIZONTALDOP | NULLMASK_POINT_VERTICALDOP | NULLMASK_POINT_POSITIONDOP | NULLMASK_POINT_AGEOFDGPSDATA) & mask))
        throw InvalidMaskException();
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
    throw MaskNotFoundException();
}

int Point::getIntValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException();
    if (!((NULLMASK_POINT_SATELITES | NULLMASK_POINT_DGPSID) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_POINT_SATELITES:
            return _satelites;
        case NULLMASK_POINT_DGPSID:
            return _DGPSID;
    }
    throw MaskNotFoundException();
}
