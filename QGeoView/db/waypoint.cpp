#include "waypoint.h"

Waypoint::Waypoint(Database *db, int id) :
    DatabaseObject(db, id)
{
    if (id)
        load();
}

Waypoint::Waypoint(const Waypoint &original) :
    DatabaseObject(original),
    _fk_point(original._fk_point),
    _fk_description(original._fk_description)
{
}

QString Waypoint::table()
{
    return "Waypoint";
}

QStringList Waypoint::fields()
{
    QStringList list;
    list << "fk_point" << "fk_description";
    return list;
}

void Waypoint::addBindValues(QSqlQuery query)
{
    query.addBindValue(isSet(NULLMASK_WAYPOINT_POINT) ? _fk_point : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_WAYPOINT_DESCRIPTION) ? _fk_description : QVariant(QVariant::Int));
}

void Waypoint::loadValues(QSqlQuery query)
{
    int i=0;
    _fk_point = query.value(i++).toInt();
    _fk_description = query.value(i++).toInt();
}

void Waypoint::setIntValue(int mask, int value)
{
    switch(mask) {
        case NULLMASK_WAYPOINT_POINT:
            _fk_point = value;
            break;
        case NULLMASK_WAYPOINT_DESCRIPTION:
            _fk_description = value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "Int");
    }
    set(mask);
}

int Waypoint::getIntValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "Int");
    switch(mask) {
        case NULLMASK_WAYPOINT_POINT:
            return _fk_point;
        case NULLMASK_WAYPOINT_DESCRIPTION:
            return _fk_description;
    }
    throw MaskNotFoundException(this, mask, "Int");
}

Point Waypoint::getPoint()
{
    return Point(_db, _fk_point);
}

Description Waypoint::getDescription()
{
    return Description(_db, _fk_description);
}
