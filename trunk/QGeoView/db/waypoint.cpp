#include "waypoint.h"

Waypoint::Waypoint(Database *db) :
    DatabaseObject(db),
    _point_object(NULL),
    _description_object(NULL)
{
}

Waypoint::~Waypoint()
{
    if (_point_object)
        delete _point_object;
    if (_description_object)
        delete _description_object;
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
    if (!((NULLMASK_WAYPOINT_POINT | NULLMASK_WAYPOINT_DESCRIPTION) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_WAYPOINT_POINT:
            if (_point)
                delete _point_object;
            _point = value;
            break;
        case NULLMASK_WAYPOINT_DESCRIPTION:
            if (_description_object)
                delete _description_object;
            _description = value;
            break;
        default:
            throw MaskNotFoundException();
    }
    set(mask);
}

int Waypoint::getIntValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException();
    if (!((NULLMASK_WAYPOINT_POINT | NULLMASK_WAYPOINT_DESCRIPTION) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_WAYPOINT_POINT:
            return _point;
        case NULLMASK_WAYPOINT_DESCRIPTION:
            return _description;
    }
    throw MaskNotFoundException();
}
