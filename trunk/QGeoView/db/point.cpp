#include "point.h"

Point::Point(QObject *parent) :
    DatabaseObject(parent)
{
}

Point::~Point()
{
    delete _accuracy;
}

QStringList Point::fields()
{
    QStringList list;
    list.append("time");
    list.append("elevation");
    list.append("magneticVariation");
    list.append("geoIDHeight");
    list.append("symbol");
    list.append("fix");
    list.append("satelites");
    list.append("horizontalDOP");
    list.append("verticalDOP");
    list.append("positionDOP");
    list.append("ageofDGPSData");
    list.append("DGPSID");
    list.append("latitude");
    list.append("longitude");
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
