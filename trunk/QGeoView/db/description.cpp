#include <iostream>
#include "description.h"
#include "exceptions.h"

Description::Description(Database *db, int id) :
    DatabaseObject(db, id)
{
    if (id)
        load();
}

Description::Description(Database *db, QSqlQuery query) :
    DatabaseObject(db)
{
    loadValues(query, true);
}

Description::Description(const Description &original) :
    DatabaseObject(original),
    _name(original._name),
    _link_url(original._link_url),
    _link_name(original._link_name),
    _comments(original._comments),
    _source(original._source),
    _type(original._type)
{

}

QString Description::table()
{
    return "Description";
}

QStringList Description::fields()
{
    return Description::fieldNames();
}

QStringList Description::fieldNames()
{
    QStringList list; list << "name" << "link_url" << "link_name" << "comments" << "source" << "type";
    return list;
}

void Description::addBindValues(QSqlQuery query)
{
    query.addBindValue(isSet(NULLMASK_DESCRIPTION_NAME) ? _name : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_DESCRIPTION_LINKURL) ? _link_url : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_DESCRIPTION_LINKNAME) ? _link_name : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_DESCRIPTION_COMMENTS) ? _comments : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_DESCRIPTION_SOURCE) ? _source : QVariant(QVariant::String));
    query.addBindValue(isSet(NULLMASK_DESCRIPTION_TYPE) ? _type : QVariant(QVariant::String));
}

void Description::loadValues(QSqlQuery query, bool loadID)
{
    int i=-1;
    if (loadID)
        setID(query.value(++i).toInt());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_DESCRIPTION_NAME, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_DESCRIPTION_LINKURL, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_DESCRIPTION_LINKNAME, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_DESCRIPTION_COMMENTS, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_DESCRIPTION_SOURCE, query.value(i).toString());
    if (query.value(++i).isValid())
        setQStringValue(NULLMASK_DESCRIPTION_TYPE, query.value(i).toString());
}

void Description::setQStringValue(int mask, QString value)
{
    switch(mask) {
        case NULLMASK_DESCRIPTION_NAME:
            _name = value;
            break;
        case NULLMASK_DESCRIPTION_LINKURL:
            _link_url = value;
            break;
        case NULLMASK_DESCRIPTION_LINKNAME:
            _link_name = value;
            break;
        case NULLMASK_DESCRIPTION_COMMENTS:
            _comments = value;
            break;
        case NULLMASK_DESCRIPTION_SOURCE:
            _source = value;
            break;
        case NULLMASK_DESCRIPTION_TYPE:
            _type = value;
            break;
        default:
            throw MaskNotFoundException(this, mask, "QString");
    }
    set(mask);
}

QString Description::getQStringValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException(this, mask, "QString");
    switch(mask) {
        case NULLMASK_DESCRIPTION_NAME:
            return _name;
        case NULLMASK_DESCRIPTION_LINKURL:
            return _link_url;
        case NULLMASK_DESCRIPTION_LINKNAME:
            return _link_name;
        case NULLMASK_DESCRIPTION_COMMENTS:
            return _comments;
        case NULLMASK_DESCRIPTION_SOURCE:
            return _source;
        case NULLMASK_DESCRIPTION_TYPE:
            return _type;
    }
    throw MaskNotFoundException(this, mask, "QString");
}
