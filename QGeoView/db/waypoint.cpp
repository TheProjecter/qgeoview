#include <QVariant>
#include <QStringList>
#include <iostream>
#include "waypoint.h"
#include "exceptions.h"

Waypoint::Waypoint(QSqlDatabase *db, int id) :
    DatabaseObject(db, id)
{
    if (id)
        load();
}

Waypoint::Waypoint(QSqlDatabase *db, QSqlQuery query) :
    DatabaseObject(db)
{
    loadValues(query, true);
}

QString Waypoint::summary()
{
    if (isSet(NULLMASK_WAYPOINT_DESCRIPTION)) {
        Description *d(getDescription());
        if (d->isSet(NULLMASK_DESCRIPTION_NAME))
            return d->getName();
    }
    return "Some Waypoint...";
}

QString Waypoint::table()
{
    return Waypoint::tableName();
}

QString Waypoint::tableName()
{
    return "Waypoint";
}

QStringList Waypoint::fields()
{
    return Waypoint::fieldNames();
}

QStringList Waypoint::fieldNames()
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

void Waypoint::loadValues(QSqlQuery query, bool loadID)
{
    int i=-1;
    if (loadID)
        setID(query.value(++i).toInt());
    if (query.value(++i).isValid())
        setPoint(query.value(i).toInt());
    if (query.value(++i).isValid())
        setDescription(query.value(i).toInt());
}

Point *Waypoint::getPoint()
{
    return new Point(_db, _fk_point);
}

Description *Waypoint::getDescription()
{
    if (!isSet(NULLMASK_WAYPOINT_DESCRIPTION)) {
        throw DBValueNotSetException(this, NULLMASK_WAYPOINT_DESCRIPTION, "fk_description");
    }
    return new Description(_db, _fk_description);
}

QList<Waypoint*> Waypoint::getAll(QSqlDatabase *db)
{
    QList<Waypoint*> waypoints;
    QSqlQuery query("SELECT id, " + Waypoint::fieldNames().join(", ") + " FROM " + Waypoint::tableName() + ";");
    if (!query.exec())
        throw query;
    while (query.next()) {
        waypoints.append(new Waypoint(db, query));
    }

    return waypoints;
}

void Waypoint::setPoint(int point)
{
    set(NULLMASK_WAYPOINT_POINT);
    _fk_point = point;
}

void Waypoint::setDescription(int description)
{
    set(NULLMASK_WAYPOINT_DESCRIPTION);
    _fk_description = description;
}

