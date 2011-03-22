#include <iostream>
#include <QVariant>
#include <QStringList>
#include "description.h"
#include "exceptions.h"

Description::Description(QSqlDatabase *db, int id) :
    DatabaseObject(db, id)
{
    if (id)
        load();
}

Description::Description(QSqlDatabase *db, QSqlQuery query) :
    DatabaseObject(db)
{
    loadValues(query, true);
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

void Description::setName(QString name)
{
    set(NULLMASK_DESCRIPTION_NAME);
    _name = name;
}

QString Description::getName()
{
    ensure(NULLMASK_DESCRIPTION_NAME);
    return _name;
}

void Description::setLink(QString url, QString name)
{
    set(NULLMASK_DESCRIPTION_LINKURL);
    set(NULLMASK_DESCRIPTION_LINKNAME);
    _link_url = url;
    _link_name = name;
}

QString Description::getLinkURL()
{
    ensure(NULLMASK_DESCRIPTION_LINKURL);
    return _link_url;
}

QString Description::getLinkName()
{
    ensure(NULLMASK_DESCRIPTION_LINKNAME);
    return _link_name;
}

void Description::setComments(QString comments)
{
    set(NULLMASK_DESCRIPTION_COMMENTS);
    _comments = comments;
}

QString Description::getComments()
{
    ensure(NULLMASK_DESCRIPTION_COMMENTS);
    return _comments;
}

void Description::setSource(QString source)
{
    set(NULLMASK_DESCRIPTION_SOURCE);
    _source = source;
}

QString Description::getSource()
{
    ensure(NULLMASK_DESCRIPTION_SOURCE);
    return _source;
}

void Description::setType(QString type)
{
    set(NULLMASK_DESCRIPTION_TYPE);
    _type = type;
}

QString Description::getType()
{
    ensure(NULLMASK_DESCRIPTION_TYPE);
    return _type;
}

