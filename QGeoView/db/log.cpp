#include <QVariant>
#include <QStringList>
#include "log.h"
#include "exceptions.h"

Log::Log(QSqlDatabase *db, int id) :
    DatabaseObject(db, id)
{
    if (id)
        load();
}

Log::Log(QSqlDatabase *db, QSqlQuery query) :
    DatabaseObject(db)
{
    loadValues(query, true);
}

QString Log::table()
{
    return Log::tableName();
}

QString Log::tableName()
{
    return "Log";
}

QString Log::summary()
{
    return "Log " + QString::number(getID());
}

QStringList Log::fields()
{
    return Log::fieldNames();
}

QStringList Log::fieldNames()
{
    QStringList list;
    list << "fk_cache" << "log_id" << "log_guid" << "date" << "type" << "finder_id" << "finder_guid" << "finder_name" << "text" << "text_encoded" << "latitude" << "longitude";
    return list;
}

void Log::addBindValues(QSqlQuery query)
{
    query.addBindValue(isSet(NULLMASK_LOG_CACHE) ? _fk_cache : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_LOG_LOGID) ? _log_id : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_LOG_LOGGUID) ? _log_guid : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_DATE) ? _date : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_TYPE) ? _type : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_FINDERID) ? _finder_id : QVariant(QVariant::Int));
    query.addBindValue(isSet(NULLMASK_LOG_FINDERGUID) ? _finder_guid : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_FINDERNAME) ? _finder_name : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_TEXT) ? _text : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_LOG_TEXTENCODED) ? _text_encoded : QVariant(QVariant::Bool));
    query.addBindValue(isSet(NULLMASK_LOG_LATITUDE) ? _latitude : QVariant(QVariant::Double));
    query.addBindValue(isSet(NULLMASK_LOG_LONGITUDE) ? _longitude : QVariant(QVariant::Double));
}

void Log::loadValues(QSqlQuery query, bool loadID)
{
    int i=-1;
    if (loadID)
        setID(query.value(++i).toInt());
    if (query.value(++i).isValid())
        setIntValue(NULLMASK_LOG_CACHE, query.value(i).toInt());
    if (query.value(++i).isValid())
        setIntValue(NULLMASK_LOG_LOGID, query.value(i).toInt());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_LOG_LOGGUID, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_LOG_DATE, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_LOG_TYPE, query.value(i).toString());
    if (query.value(++i).isValid())
        setIntValue(NULLMASK_LOG_FINDERID, query.value(i).toInt());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_LOG_FINDERGUID, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_LOG_FINDERNAME, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_LOG_TEXT, query.value(i).toString());
    if (query.value(++i).isValid())
        setBoolValue(NULLMASK_LOG_TEXTENCODED, query.value(i).toBool());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_LOG_LATITUDE, query.value(i).toDouble());
    if (query.value(++i).isValid())
        setFloatValue(NULLMASK_LOG_LONGITUDE, query.value(i).toDouble());
}

void Log::setQStringValue(int mask, QString value)
{
    switch(mask) {
        case NULLMASK_LOG_LOGGUID:
            _finder_guid = value;
            break;
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
            throw MaskNotFoundException(this, mask, "QString");
    }
    set(mask);
}

void Log::setFloatValue(int mask, float value)
{
    switch (mask) {
        case NULLMASK_LOG_LATITUDE:
            _latitude = value;
            break;
        case NULLMASK_LOG_LONGITUDE:
            _longitude = value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "Float");
    }
    set(mask);
}

void Log::setIntValue(int mask, int value)
{
    switch (mask) {
        case NULLMASK_LOG_LOGID:
            _log_id = value;
            break;
        case NULLMASK_LOG_FINDERID:
            _finder_id = value;
            break;
        case NULLMASK_LOG_CACHE:
            _fk_cache = value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "Int");
    }
    set(mask);
}

void Log::setBoolValue(int mask, bool value)
{
    switch (mask) {
        case NULLMASK_LOG_TEXTENCODED:
            _text_encoded = value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "Bool");
    }
    set(mask);
}

QString Log::getQStringValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "QString");
    switch(mask) {
        case NULLMASK_LOG_DATE:
            return _date;
        case NULLMASK_LOG_TYPE:
            return _type;
        case NULLMASK_LOG_LOGGUID:
            return _log_guid;
        case NULLMASK_LOG_FINDERGUID:
            return _finder_guid;
        case NULLMASK_LOG_FINDERNAME:
            return _finder_name;
        case NULLMASK_LOG_TEXT:
            return _text;
    }
    throw MaskNotFoundException(this, mask, "QString");
}

float Log::getFloatValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "Float");
    switch (mask) {
        case NULLMASK_LOG_LATITUDE:
            return _latitude;
        case NULLMASK_LOG_LONGITUDE:
            return _longitude;
    }
    throw MaskNotFoundException(this, mask, "Float");
}

int Log::getIntValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "Int");
    switch (mask) {
        case NULLMASK_LOG_LOGID:
            return _log_id;
        case NULLMASK_LOG_FINDERID:
            return _finder_id;
        case NULLMASK_LOG_CACHE:
            return _fk_cache;
    }
    throw MaskNotFoundException(this, mask, "Int");
}

bool Log::getBoolValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "Bool");
    switch (mask) {
        case NULLMASK_LOG_TEXTENCODED:
            return _text_encoded;
    }
    throw MaskNotFoundException(this, mask, "Bool");
}

void Log::setLogGUID(QString log_guid)
{
    set(NULLMASK_LOG_LOGGUID);
    _log_guid = log_guid;
}

QString Log::getLogGUID()
{
    ensure(NULLMASK_LOG_LOGGUID);
    return _log_guid;
}

void Log::setDate(QString date)
{
    set(NULLMASK_LOG_DATE);
    _date = date;
}

QString Log::getDate()
{
    ensure(NULLMASK_LOG_DATE);
    return _date;
}

void Log::setType(QString type)
{
    set(NULLMASK_LOG_TYPE);
    _type = type;
}

QString Log::getType()
{
    ensure(NULLMASK_LOG_TYPE);
    return _type;
}

void Log::setFinderGUID(QString finder_guid)
{
    set(NULLMASK_LOG_FINDERGUID);
    _finder_guid = finder_guid;
}

QString Log::getFinderGUID()
{
    ensure(NULLMASK_LOG_FINDERGUID);
    return _finder_guid;
}

void Log::setFinderName(QString finder_name)
{
    set(NULLMASK_LOG_FINDERNAME);
    _finder_name = finder_name;
}

QString Log::getFinderName()
{
    ensure(NULLMASK_LOG_FINDERNAME);
    return _finder_name;
}

void Log::setText(QString text, bool encoded)
{
    set(NULLMASK_LOG_TEXT);
    set(NULLMASK_LOG_TEXTENCODED);
    _text = text;
    _text_encoded = encoded;
}

QString Log::getText()
{
    ensure(NULLMASK_LOG_TEXT);
    return _text;
}

bool Log::getTextEncoded()
{
    ensure(NULLMASK_LOG_TEXTENCODED);
    return _text_encoded;
}

void Log::setLatitude(float latitude)
{
    set(NULLMASK_LOG_LATITUDE);
    _latitude = latitude;
}

float Log::getLatitude()
{
    ensure(NULLMASK_LOG_LATITUDE);
    return _latitude;
}

void Log::setLongitude(float longitude)
{
    set(NULLMASK_LOG_LONGITUDE);
    _longitude = longitude;
}

float Log::getLongitude()
{
    ensure(NULLMASK_LOG_LONGITUDE);
    return _longitude;
}

void Log::setLogID(int log_id)
{
    set(NULLMASK_LOG_LOGID);
    _log_id = log_id;
}

int Log::getLogID()
{
    ensure(NULLMASK_LOG_LOGID);
    return _log_id;
}

void Log::setFinderID(int finder_id)
{
    set(NULLMASK_LOG_FINDERID);
    _finder_id = finder_id;
}

int Log::getFinderID()
{
    ensure(NULLMASK_LOG_FINDERID);
    return _finder_id;
}

void Log::setCache(int cache)
{
    set(NULLMASK_LOG_CACHE);
    _fk_cache = cache;
}

int Log::getCache()
{
    ensure(NULLMASK_LOG_CACHE);
    return _fk_cache;
}

