#include <QVariant>

#include "collection.h"
#include "exceptions.h"

Collection::Collection(QSqlDatabase *db, int id) :
    DatabaseObject(db, id)
{
    if (id)
        load();
}

Collection::Collection(QSqlDatabase *db, QSqlQuery query) :
    DatabaseObject(db)
{
    loadValues(query, true);
}

QString Collection::table()
{
    return tableName();
}

QString Collection::tableName()
{
    return "Collection";
}

QString Collection::summary()
{
    return _name + " (" + _description + ")";
}

QStringList Collection::fields()
{
    return Collection::fieldNames();
}

QStringList Collection::fieldNames()
{
    QStringList list;
    list << "name" << "description";
    return list;
}

void Collection::addBindValues(QSqlQuery query)
{
    query.addBindValue(isSet(NULLMASK_COLLECTION_NAME) ? _name : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_COLLECTION_DESCRIPTION) ? _description : QVariant(QVariant::String));
}

void Collection::loadValues(QSqlQuery query, bool loadID)
{
    int i=-1;
    if (loadID)
        setID(query.value(++i).toInt());
    if (query.value(++i).isValid())
        setName(query.value(i).toString());
    if (query.value(++i).isValid())
        setDescription(query.value(i).toString());
}

void Collection::addCache(int id)
{
    _db->transaction();
    QSqlQuery query("INSERT INTO Cache2Collection (fk_collection, fk_cache) VALUES (?, ?)");
    query.addBindValue(_id);
    query.addBindValue(id);
    if (!query.exec())
        throw query;
    _db->commit();
}

void Collection::addWaypoint(int id)
{
    _db->transaction();
    QSqlQuery query("INSERT INTO Waypoint2Collection (fk_collection, fk_waypoint) VALUES (?, ?)");
    query.addBindValue(_id);
    query.addBindValue(id);
    if (!query.exec())
        throw query;
    _db->commit();
}

void Collection::removeCache(int id)
{
    _db->transaction();
    QSqlQuery query("DELETE FROM Cache2Collection WHERE fk_collection=? AND fk_cache=?");
    query.addBindValue(_id);
    query.addBindValue(id);
    if (!query.exec())
        throw query;
    _db->commit();
}

void Collection::removeWaypoint(int id)
{
    _db->transaction();
    QSqlQuery query("DELETE FROM Waypoint2Collection WHERE fk_collection=? AND fk_waypoint=?;");
    query.addBindValue(_id);
    query.addBindValue(id);
    if (!query.exec())
        throw query;
    _db->commit();
}

void Collection::cleanup()
{
    if (!_id)
        return;

    _db->transaction();

    QSqlQuery query("DELETE FROM Cache2Collection WHERE fk_collection=?;");
    query.addBindValue(_id);
    if (!query.exec())
        throw query;

    query.clear();
    query.prepare("DELETE FROM Waypoint2Collection WHERE fk_collection=?;");
    query.addBindValue(_id);
    if (!query.exec())
        throw query;

    query.clear();
    query.prepare("DELETE FROM Point2Collection WHERE fk_collection=?;");
    query.addBindValue(_id);
    if (!query.exec())
        throw query;

    query.clear();
    query.prepare("DELETE FROM Track2Collection WHERE fk_collection=?;");
    query.addBindValue(_id);
    if (!query.exec())
        throw query;

    query.clear();
    query.prepare("DELETE FROM Route2Collection WHERE fk_collection=?;");
    query.addBindValue(_id);
    if (!query.exec())
        throw query;

    query.clear();
    query.prepare("DELETE FROM TravelBug2Collection WHERE fk_collection=?;");
    query.addBindValue(_id);
    if (!query.exec())
        throw query;

    _db->commit();
}

QList<Collection*> Collection::getAll(QSqlDatabase *db)
{
    QList<Collection*> collections;
    QSqlQuery query("SELECT id, " + Collection::fieldNames().join(", ") + " FROM " + Collection::tableName() + ";");
    if (!query.exec())
        throw query;

    while (query.next())
        collections.append(new Collection(db, query));

    return collections;
}

QList<Cache*> Collection::caches()
{
    if (!_id)
        throw IDNotSetException(this);
    QList<Cache*> caches;
    QSqlQuery query("SELECT id, " + Cache::fieldNames().join(", ") + " FROM " + Cache::tableName() + " WHERE id IN (SELECT fk_cache FROM Cache2Collection WHERE fk_collection=?);");
    query.addBindValue(_id);

    if (!query.exec())
        throw query;

    while (query.next()) {
        caches.append(new Cache(_db, query));
    }

    return caches;
}

QList<Waypoint*> Collection::waypoints()
{
    if (!_id)
        throw IDNotSetException(this);
    QList<Waypoint*> waypoints;
    QSqlQuery query("SELECT id, " + Waypoint::fieldNames().join(", ") + " FROM " + Waypoint::tableName() + " WHERE id IN (SELECT fk_waypoint FROM Waypoint2Collection WHERE fk_collection=?);");
    query.addBindValue(_id);

    if (!query.exec())
        throw query;

    while (query.next()) {
        waypoints.append(new Waypoint(_db, query));
    }

    return waypoints;
}

void Collection::setName(QString name)
{
    set(NULLMASK_COLLECTION_NAME);
    _name = name;
}

QString Collection::getName()
{
    ensure(NULLMASK_COLLECTION_NAME);
    return _name;
}

void Collection::setDescription(QString description)
{
    set(NULLMASK_COLLECTION_DESCRIPTION);
    _description = description;
}

QString Collection::getDescription()
{
    ensure(NULLMASK_COLLECTION_DESCRIPTION);
    return _description;
}
