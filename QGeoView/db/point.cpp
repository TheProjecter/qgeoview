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
    query.addBindValue(isSet(NULLMASK_TIME) ? _time : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_ELEVATION) ? _elevation : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_MAGNETICVARIATION) ? _magneticVariation : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_GEOIDHEIGHT) ? _geoIDHeight : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_SYMBOL) ? _symbol : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_FIX) ? _fix : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_SATELITES) ? _satelites : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_HORIZONTALDOP) ? _horizontalDOP : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_VERTICALDOP) ? _verticalDOP : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_POSITIONDOP) ? _positionDOP : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_AGEOFDGPSDATA) ? _ageOfDGPSData : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_DGPSID) ? _DGPSID : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_LATITUDE) ? _latitude : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_LONGITUDE) ? _longitude : QVariant(QVariant::Double));
}

void Point::setQStringValue(int mask, QString value)
{
    if (!((NULLMASK_TIME | NULLMASK_SYMBOL | NULLMASK_FIX) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_TIME:
            _time = value;
            break;
        case NULLMASK_SYMBOL:
            _symbol = value;
            break;
        case NULLMASK_FIX:
            _fix = value;
            break;
        default:
            throw MaskNotFoundException();
    }
    set(mask);
}

void Point::setFloatValue(int mask, float value)
{
    if (!((NULLMASK_ELEVATION | NULLMASK_MAGNETICVARIATION | NULLMASK_GEOIDHEIGHT | NULLMASK_LATITUDE | NULLMASK_LONGITUDE | NULLMASK_HORIZONTALDOP | NULLMASK_VERTICALDOP | NULLMASK_POSITIONDOP | NULLMASK_AGEOFDGPSDATA) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_ELEVATION:
            _elevation = value;
            break;
        case NULLMASK_MAGNETICVARIATION:
            _magneticVariation = value;
            break;
        case NULLMASK_GEOIDHEIGHT:
            _geoIDHeight = value;
            break;
        case NULLMASK_LATITUDE:
            _latitude = value;
            break;
        case NULLMASK_LONGITUDE:
            _longitude = value;
            break;
        case NULLMASK_HORIZONTALDOP:
            _horizontalDOP = value;
            break;
        case NULLMASK_VERTICALDOP:
            _verticalDOP = value;
            break;
        case NULLMASK_POSITIONDOP:
            _positionDOP = value;
            break;
        case NULLMASK_AGEOFDGPSDATA:
            _ageOfDGPSData = value;
            break;
        default:
            throw MaskNotFoundException();
    }
    set(mask);
}

void Point::setIntValue(int mask, int value)
{
    if (!((NULLMASK_SATELITES | NULLMASK_DGPSID) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_SATELITES:
            _satelites = value;
            break;
        case NULLMASK_DGPSID:
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
    if (!((NULLMASK_TIME | NULLMASK_SYMBOL | NULLMASK_FIX) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_TIME:
            return _time;
        case NULLMASK_SYMBOL:
            return _symbol;
        case NULLMASK_FIX:
            return _fix;
        }
    throw MaskNotFoundException();
}

float Point::getFloatValue(int mask)
{
    if(!isSet(mask))
        throw DBValueNotSetException();
    if (!((NULLMASK_ELEVATION | NULLMASK_MAGNETICVARIATION | NULLMASK_GEOIDHEIGHT | NULLMASK_LATITUDE | NULLMASK_LONGITUDE | NULLMASK_HORIZONTALDOP | NULLMASK_VERTICALDOP | NULLMASK_POSITIONDOP | NULLMASK_AGEOFDGPSDATA) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_ELEVATION:
            return _elevation;
        case NULLMASK_MAGNETICVARIATION:
            return _magneticVariation;
        case NULLMASK_GEOIDHEIGHT:
            return _geoIDHeight;
        case NULLMASK_LATITUDE:
            return _latitude;
        case NULLMASK_LONGITUDE:
            return _longitude;
        case NULLMASK_HORIZONTALDOP:
            return _horizontalDOP;
        case NULLMASK_VERTICALDOP:
            return _verticalDOP;
        case NULLMASK_POSITIONDOP:
            return _positionDOP;
        case NULLMASK_AGEOFDGPSDATA:
            return _ageOfDGPSData;
    }
    throw MaskNotFoundException();
}

int Point::getIntValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException();
    if (!((NULLMASK_SATELITES | NULLMASK_DGPSID) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_SATELITES:
            return _satelites;
        case NULLMASK_DGPSID:
            return _DGPSID;
    }
    throw MaskNotFoundException();
}
