#include "log.h"

Log::Log(Database *db) :
    DatabaseObject(db),
    _cache_object(NULL)
{
}


Log::~Log()
{
    if (_cache_object)
        delete _cache_object;
}

QString Log::table()
{
    return "Log";
}

QStringList Log::fields()
{
    QStringList list;
    list << "log_guid" << "date" << "type" << "finder_id" << "finder_guid" << "finder_name" << "text" << "text_encoded" << "latitude" << "longitude";
    return list;
}

void Log::addBindValues(QSqlQuery query)
{
    query.addBindValue(isSet(NULLMASK_LOG_LOGGUID) ? _log_guid : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_DATE) ? _date : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_TYPE) ? _type : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_FINDERID) ? _finder_id : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_LOG_FINDERGUID) ? _finder_guid : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_FINDERNAME) ? _finder_name : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_TEXT) ? _text : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_TEXTENCODED) ? _text_encoded : QVariant(QVariant::Bool));
    query.addBindValue(isSet(NULLMASK_LOG_LATITUDE) ? _latitude : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_LOG_LONGITUDE) ? _longitude : QVariant(QVariant::Double)); }

void Log::setQStringValue(int mask, QString value)
{
    if (!((NULLMASK_LOG_DATE | NULLMASK_LOG_TYPE | NULLMASK_LOG_FINDERGUID | NULLMASK_LOG_FINDERNAME | NULLMASK_LOG_TEXT) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_LOG_DATE:
            _date = value;
            break;
        case NULLMASK_LOG_TYPE:
            _type = value;
            break;
        case NULLMASK_LOG_FINDERGUID:
            _finder_guid = value;
            break;
        case NULLMASK_LOG_FINDERNAME:
            _finder_name = value;
            break;
        case NULLMASK_LOG_TEXT:
            _text = value;
            break;
        default:
            throw MaskNotFoundException();
    }
    set(mask);
}

void Log::setFloatValue(int mask, float value)
{
    if (!((NULLMASK_LOG_LATITUDE | NULLMASK_LOG_LONGITUDE) & mask))
        throw InvalidMaskException();
    switch (mask) {
        case NULLMASK_LOG_LATITUDE:
            _latitude = value;
            break;
        case NULLMASK_LOG_LONGITUDE:
            _longitude = value;
            break;
        default:
            throw MaskNotFoundException();
    }
    set(mask);
}

void Log::setIntValue(int mask, int value)
{
    if (!!((NULLMASK_LOG_LOGGUID | NULLMASK_LOG_FINDERID | NULLMASK_LOG_CACHE) & mask ))
        throw InvalidMaskException();
    switch (mask) {
        case NULLMASK_LOG_LOGGUID:
            _log_guid = value;
            break;
        case NULLMASK_LOG_FINDERID:
            _finder_id = value;
            break;
        case NULLMASK_LOG_CACHE:
            _cache = value;
            break;
        default:
            throw MaskNotFoundException();
    }
    set(mask);
}

void Log::setBoolValue(int mask, bool value)
{
    if (!((NULLMASK_LOG_TEXTENCODED) & mask))
        throw InvalidMaskException();
    switch (mask) {
        case NULLMASK_LOG_TEXTENCODED:
            _text_encoded = value;
            break;
        default:
            throw MaskNotFoundException();
    }
    set(mask);
}

QString Log::getQStringValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException();
    if (!((NULLMASK_LOG_DATE | NULLMASK_LOG_TYPE | NULLMASK_LOG_FINDERGUID | NULLMASK_LOG_FINDERNAME | NULLMASK_LOG_TEXT) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_LOG_DATE:
            return _date;
        case NULLMASK_LOG_TYPE:
            return _type;
        case NULLMASK_LOG_FINDERGUID:
            return _finder_guid;
        case NULLMASK_LOG_FINDERNAME:
            return _finder_name;
        case NULLMASK_LOG_TEXT:
            return _text;
    }
    throw MaskNotFoundException();
}

float Log::getFloatValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException();
    if (!((NULLMASK_LOG_LATITUDE | NULLMASK_LOG_LONGITUDE) & mask))
        throw InvalidMaskException();
    switch (mask) {
        case NULLMASK_LOG_LATITUDE:
            return _latitude;
        case NULLMASK_LOG_LONGITUDE:
            return _longitude;
    }
    throw MaskNotFoundException();
}

int Log::getIntValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException();
    if (!!((NULLMASK_LOG_LOGGUID | NULLMASK_LOG_FINDERID | NULLMASK_LOG_CACHE) & mask ))
        throw InvalidMaskException();
    switch (mask) {
        case NULLMASK_LOG_LOGGUID:
            return _log_guid;
        case NULLMASK_LOG_FINDERID:
            return _finder_id;
        case NULLMASK_LOG_CACHE:
            return _cache;
    }
    throw MaskNotFoundException();
}

bool Log::getBoolValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException();
    if (!((NULLMASK_LOG_TEXTENCODED) & mask))
        throw InvalidMaskException();
    switch (mask) {
        case NULLMASK_LOG_TEXTENCODED:
            return _text_encoded;
    }
    throw MaskNotFoundException();
}
