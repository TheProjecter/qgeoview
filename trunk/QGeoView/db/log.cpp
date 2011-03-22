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
        setCache(query.value(i).toInt());
    if (query.value(++i).isValid())
        setLogID(query.value(i).toInt());
    if (query.value(++i).isValid())
        setLogGUID(query.value(i).toString());
    if (query.value(++i).isValid())
        setDate(query.value(i).toString());
    if (query.value(++i).isValid())
        setType(query.value(i).toString());
    if (query.value(++i).isValid())
        setFinderID(query.value(i).toInt());
    if (query.value(++i).isValid())
        setFinderGUID(query.value(i).toString());
    if (query.value(++i).isValid())
        setFinderName(query.value(i).toString());
    if (query.value(++i).isValid()) {
        if (query.value(++i).isValid())
            setText(query.value(i-1).toString(), query.value(i).toBool());
        else
            setText(query.value(i-1).toString(), false);
    } else
        ++i;
    if (query.value(++i).isValid())
        setLatitude(query.value(i).toDouble());
    if (query.value(++i).isValid())
        setLongitude(query.value(i).toDouble());
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

