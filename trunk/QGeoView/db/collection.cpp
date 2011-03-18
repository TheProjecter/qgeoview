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
        setQStringValue(NULLMASK_COLLECTION_NAME, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_COLLECTION_DESCRIPTION, query.value(i).toString());
}

void Collection::setQStringValue(int mask, QString value)
{
    switch (mask) {
        case NULLMASK_COLLECTION_NAME:
            _name = value;
            break;
        case NULLMASK_COLLECTION_DESCRIPTION:
            _description = value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "QString");
    }
    set(mask);
}

QString Collection::getQStringValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "QString");
    switch(mask) {
        case NULLMASK_COLLECTION_NAME:
            return _name;
        case NULLMASK_COLLECTION_DESCRIPTION:
            return _description;
    }
    throw MaskNotFoundException(this, mask, "QString");
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

QList<Collection> Collection::getAllCollections(QSqlDatabase *db)
{
    QList<Collection> collections;
    QSqlQuery query("SELECT id, " + Collection::fieldNames().join(", ") + " FROM " + Collection::tableName() + ";");
    if (!query.exec())
        throw query;

    while (query.next())
        collections.append(Collection(db, query));

    return collections;
}

QList<Cache> Collection::caches()
{
    QList<Cache> caches;
    QSqlQuery query("SELECT id, " + Cache::fieldNames().join(", ") + " FROM " + Cache::tableName() + ";");

    if (!query.exec())
        throw query;

    while (query.next()) {
        caches.append(Cache(_db, query));
    }

    return caches;
}

QList<Waypoint> Collection::waypoints()
{
    QList<Waypoint> waypoints;
    QSqlQuery query("SELECT id, " + Waypoint::fieldNames().join(", ") + " FROM " + Waypoint::tableName() + ";");

    if (!query.exec())
        throw query;

    while (query.next()) {
        waypoints.append(Waypoint(_db, query));
    }

    return waypoints;
}
