#include "cache.h"

Cache::Cache(Database *db) :
    DatabaseObject(db),
    _waypoint_object(NULL)
{
}

Cache::~Cache()
{
    if (_waypoint_object)
        delete _waypoint_object;
}

QString Cache::table()
{
    return "Cache";
}

QStringList Cache::fields()
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
    query.addBindValue(isSet(NULLMASK_CACHE_WAYPOINT) ? _waypoint : QVariant(QVariant::Int));
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
            _waypoint = value;
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
