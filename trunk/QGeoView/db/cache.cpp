#include <iostream>
#include <QStringList>
#include <QVariant>
#include "cache.h"
#include "exceptions.h"

Cache::Cache(QSqlDatabase *db, int id) :
    DatabaseObject(db, id)
{
    if (id)
        load();
}

Cache::Cache(QSqlDatabase *db, QSqlQuery query) :
    DatabaseObject(db)
{
    loadValues(query, true);
}

QList<Cache*> Cache::getAll(QSqlDatabase *db)
{
    QList<Cache*> caches;
    QSqlQuery query("SELECT id, " + Cache::fieldNames().join(", ") + " FROM " + Cache::tableName() + ";");
    if (!query.exec())
        throw query;

    while (query.next()) {
        caches.append(new Cache(db, query));
    }

    return caches;
}

QString Cache::summary()
{
    try {
        return getQStringValue(NULLMASK_CACHE_NAME) + " (" + getWaypoint()->summary() + ")";
    }
    catch (DBValueNotSetException) {
        return "Cache " + QString::number(getID());
    }
}

QString Cache::table()
{
    return Cache::tableName();
}

QString Cache::tableName()
{
    return "Cache";
}

QStringList Cache::fields()
{
    return Cache::fieldNames();
}

QStringList Cache::fieldNames()
{
    QStringList list;
    list << "name" << "placed_by" << "owner_id" << "owner_guid" << "owner_name" << "type" << "container" << "difficulty" << "terrain" << "country" << "state" << "short_description" << "short_description_html" << "long_description" << "long_description_html" << "encoded_hints" << "fk_waypoint";
    return list;
}

void Cache::addBindValues(QSqlQuery query)
{
    query.addBindValue(isSet(NULLMASK_CACHE_NAME) ? _name : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_CACHE_PLACEDBY) ? _placed_by : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_CACHE_OWNERID) ? _owner_id : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_CACHE_OWNERGUID) ? _owner_guid : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_CACHE_OWNERNAME) ? _owner_name : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_CACHE_TYPE) ? _type : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_CACHE_CONTAINER) ? _container : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_CACHE_DIFFICULTY) ? _difficulty : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_CACHE_TERRAIN) ? _terrain : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_CACHE_COUNTRY) ? _country : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_CACHE_STATE) ? _state : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_CACHE_SHORTDESCRIPTION) ? _short_description : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_CACHE_SHORTDESCRIPTIONHTML) ? _short_description_html : QVariant(QVariant::Bool));
    query.addBindValue(isSet(NULLMASK_CACHE_LONGDESCRIPTION) ? _long_description : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_CACHE_LONGDESCRIPTIONHTML) ? _long_description_html : QVariant(QVariant::Bool));
    query.addBindValue(isSet(NULLMASK_CACHE_ENCODEDHINTS) ? _encoded_hints : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_CACHE_WAYPOINT) ? _fk_waypoint : QVariant(QVariant::Int));
}

void Cache::loadValues(QSqlQuery query, bool loadID)
{
    int i=-1;
    if (loadID)
        setID(query.value(++i).toInt());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_CACHE_NAME, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_CACHE_PLACEDBY, query.value(i).toString());
    if (query.value(++i).isValid())
        setIntValue(NULLMASK_CACHE_OWNERID, query.value(i).toInt());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_CACHE_OWNERGUID, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_CACHE_OWNERNAME, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_CACHE_TYPE, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_CACHE_CONTAINER, query.value(i).toString());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_CACHE_DIFFICULTY, query.value(i).toDouble());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_CACHE_TERRAIN, query.value(i).toDouble());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_CACHE_COUNTRY, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_CACHE_STATE, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_CACHE_SHORTDESCRIPTION, query.value(i).toString());
    if (query.value(++i).isValid())
        setBoolValue(NULLMASK_CACHE_SHORTDESCRIPTIONHTML, query.value(i).toBool());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_CACHE_LONGDESCRIPTION, query.value(i).toString());
    if (query.value(++i).isValid())
        setBoolValue(NULLMASK_CACHE_LONGDESCRIPTIONHTML, query.value(i).toBool());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_CACHE_ENCODEDHINTS, query.value(i).toString());
    if (query.value(++i).isValid())
        setIntValue(NULLMASK_CACHE_WAYPOINT, query.value(i).toInt());
}


void Cache::setQStringValue(int mask, QString value)
{
    switch (mask) {
        case NULLMASK_CACHE_NAME:
            _name = value;
            break;
        case NULLMASK_CACHE_PLACEDBY:
            _placed_by = value;
            break;
        case NULLMASK_CACHE_OWNERGUID:
            _owner_name = value;
            break;
        case NULLMASK_CACHE_OWNERNAME:
            _type = value;
            break;
        case NULLMASK_CACHE_TYPE:
            _type = value;
            break;
        case NULLMASK_CACHE_CONTAINER:
            _container = value;
            break;
        case NULLMASK_CACHE_COUNTRY:
            _country = value;
            break;
        case NULLMASK_CACHE_STATE:
            _state = value;
            break;
        case NULLMASK_CACHE_SHORTDESCRIPTION:
            _short_description = value;
            break;
        case NULLMASK_CACHE_LONGDESCRIPTION:
            _long_description = value;
            break;
        case NULLMASK_CACHE_ENCODEDHINTS:
            _encoded_hints = value;
            break;
        default:
        throw MaskNotFoundException(this, mask, "QString");
    }
    set(mask);
}

void Cache::setFloatValue(int mask, float value)
{
    switch(mask) {
        case NULLMASK_CACHE_DIFFICULTY:
            _difficulty = value;
            break;
        case NULLMASK_CACHE_TERRAIN:
            _terrain = value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "Float");
    }
    set(mask);
}


void Cache::setIntValue(int mask, int value)
{
    switch (mask) {
        case NULLMASK_CACHE_OWNERID:
            _owner_id = value;
            break;
        case NULLMASK_CACHE_WAYPOINT:
            _fk_waypoint = value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "Int");
    }
    set(mask);
}

void Cache::setBoolValue(int mask, bool value)
{
    switch(mask) {
        case NULLMASK_CACHE_SHORTDESCRIPTIONHTML:
            _short_description_html = value;
            break;
        case NULLMASK_CACHE_LONGDESCRIPTIONHTML:
            _long_description_html = value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "Bool");
    }
    set(mask);
}

QString Cache::getQStringValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "QString");
    switch (mask) {
        case NULLMASK_CACHE_NAME:
            return _name;
        case NULLMASK_CACHE_PLACEDBY:
            return _placed_by;
        case NULLMASK_CACHE_OWNERGUID:
            return _owner_name;
        case NULLMASK_CACHE_OWNERNAME:
            return _type;
        case NULLMASK_CACHE_TYPE:
            return _type;
        case NULLMASK_CACHE_CONTAINER:
            return _container;
        case NULLMASK_CACHE_COUNTRY:
            return _country;
        case NULLMASK_CACHE_STATE:
            return _state;
        case NULLMASK_CACHE_SHORTDESCRIPTION:
            return _short_description;
        case NULLMASK_CACHE_LONGDESCRIPTION:
            return _long_description;
        case NULLMASK_CACHE_ENCODEDHINTS:
            return _encoded_hints;
    }
    throw MaskNotFoundException(this, mask, "QString");
}

float Cache::getFloatValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "Float");
    switch(mask) {
        case NULLMASK_CACHE_DIFFICULTY:
            return _difficulty;
        case NULLMASK_CACHE_TERRAIN:
            return _terrain;
    }
    throw MaskNotFoundException(this, mask, "Float");
}

int Cache::getIntValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "Int");
    switch(mask) {
        case NULLMASK_CACHE_SHORTDESCRIPTIONHTML:
            return _short_description_html;
        case NULLMASK_CACHE_LONGDESCRIPTIONHTML:
            return _long_description_html;
    }
    throw MaskNotFoundException(this, mask, "Int");
}

bool Cache::getBoolValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "Bool");
    switch(mask) {
        case NULLMASK_CACHE_SHORTDESCRIPTIONHTML:
            return _short_description_html;
        case NULLMASK_CACHE_LONGDESCRIPTIONHTML:
            return _long_description_html;
    }
    throw MaskNotFoundException(this, mask, "Bool");
}

Waypoint *Cache::getWaypoint()
{
    return new Waypoint(_db, _fk_waypoint);
}

QList<int> Cache::getLogIDs()
{
    QList<int> ids;
    QSqlQuery query;
    _db->transaction();
    query.prepare("SELECT id FROM Log where fk_cache=?");
    query.addBindValue(getID());
    query.exec();
    while (query.next()) {
        ids.append(query.value(0).toInt());
    }
    return ids;
}

void Cache::setName(QString name)
{
    set(NULLMASK_CACHE_NAME);
    _name = name;
}

QString Cache::getName()
{
    ensure(NULLMASK_CACHE_NAME);
    return _name;
}

void Cache::setPlacedBy(QString placed_by)
{
    set(NULLMASK_CACHE_PLACEDBY);
    _placed_by = placed_by;
}

QString Cache::getPlacedBy()
{
    ensure(NULLMASK_CACHE_PLACEDBY);
    return _placed_by;
}

void Cache::setOwnerGUID(QString owner_guid)
{
    set(NULLMASK_CACHE_OWNERGUID);
    _owner_guid = owner_guid;
}

QString Cache::getOwnerGUID()
{
    ensure(NULLMASK_CACHE_OWNERGUID);
    return _owner_guid;
}

void Cache::setOwnerName(QString owner_name)
{
    set(NULLMASK_CACHE_OWNERNAME);
    _owner_name = owner_name;
}

QString Cache::getOwnerName()
{
    ensure(NULLMASK_CACHE_OWNERNAME);
    return _owner_name;
}

void Cache::setType(QString type)
{
    set(NULLMASK_CACHE_TYPE);
    _type = type;
}

QString Cache::getType()
{
    ensure(NULLMASK_CACHE_TYPE);
    return _type;
}

void Cache::setContainer(QString container)
{
    set(NULLMASK_CACHE_CONTAINER);
    _container = container;
}

QString Cache::getContainer()
{
    ensure(NULLMASK_CACHE_CONTAINER);
    return _container;
}

void Cache::setCountry(QString country)
{
    set(NULLMASK_CACHE_COUNTRY);
    _country = country;
}

QString Cache::getCountry()
{
    ensure(NULLMASK_CACHE_COUNTRY);
    return _country;
}

void Cache::setState(QString state)
{
    set(NULLMASK_CACHE_STATE);
    _state = state;
}

QString Cache::getState()
{
    ensure(NULLMASK_CACHE_STATE);
    return _state;
}

void Cache::setShortDescription(QString description, bool html)
{
    set(NULLMASK_CACHE_SHORTDESCRIPTION);
    set(NULLMASK_CACHE_SHORTDESCRIPTIONHTML);
    _short_description = description;
    _short_description_html = html;
}

QString Cache::getShortDescription()
{
    ensure(NULLMASK_CACHE_SHORTDESCRIPTION);
    return _short_description;
}

bool Cache::getShortDescriptionHTML()
{
    ensure(NULLMASK_CACHE_SHORTDESCRIPTION);
    return _short_description_html;
}

void Cache::setLongDescription(QString description, bool html)
{
    set(NULLMASK_CACHE_LONGDESCRIPTION);
    set(NULLMASK_CACHE_LONGDESCRIPTIONHTML);
    _long_description = description;
    _long_description_html = html;
}

QString Cache::getLongDescription()
{
    ensure(NULLMASK_CACHE_LONGDESCRIPTION);
    return _long_description;
}

bool Cache::getLongDescriptionHTML()
{
    ensure(NULLMASK_CACHE_LONGDESCRIPTIONHTML);
    return _long_description_html;
}

void Cache::setEncodedHints(QString encoded_hints)
{
    set(NULLMASK_CACHE_ENCODEDHINTS);
    _encoded_hints = encoded_hints;
}

QString Cache::getEncodedHints()
{
    ensure(NULLMASK_CACHE_ENCODEDHINTS);
    return _encoded_hints;
}

void Cache::setDifficulty(float difficulty)
{
    set(NULLMASK_CACHE_DIFFICULTY);
    _difficulty = difficulty;
}

float Cache::getDifficulty()
{
    ensure(NULLMASK_CACHE_DIFFICULTY);
    return _difficulty;
}

void Cache::setTerrain(float terrain)
{
    set(NULLMASK_CACHE_TERRAIN);
    _terrain = terrain;
}

float Cache::getTerrain()
{
    ensure(NULLMASK_CACHE_TERRAIN);
    return _terrain;
}

void Cache::setOwnerID(int owner_id)
{
    set(NULLMASK_CACHE_OWNERID);
    _owner_id = owner_id;
}

int Cache::getOwnerID()
{
    ensure(NULLMASK_CACHE_OWNERID);
    return _owner_id;
}

void Cache::setWaypoint(int waypoint)
{
    set(NULLMASK_CACHE_WAYPOINT);
    _fk_waypoint = waypoint;
}

