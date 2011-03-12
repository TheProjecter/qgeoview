#include "waypoint.h"

Waypoint::Waypoint(Database *db, int id) :
    DatabaseObject(db, id)
{
    if (id)
        load();
}

Waypoint::Waypoint(const Waypoint &original) :
    DatabaseObject(original),
    _point(original._point),
    _description(original._description)
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
    query.addBindValue(isSet(NULLMASK_WAYPOINT_POINT) ? _point : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_WAYPOINT_DESCRIPTION) ? _description : QVariant(QVariant::Int));
}

void Waypoint::setIntValue(int mask, int value)
{
    switch(mask) {
        case NULLMASK_WAYPOINT_POINT:
            _point = value;
            break;
        case NULLMASK_WAYPOINT_DESCRIPTION:
            _description = value;
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
            return _point;
        case NULLMASK_WAYPOINT_DESCRIPTION:
            return _description;
    }
    throw MaskNotFoundException(this, mask, "Int");
}

Point Waypoint::getPoint()
{
    return Point(_db, _point);
}

Description Waypoint::getDescription()
{
    return Description(_db, _description);
}
