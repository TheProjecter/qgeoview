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
        setName(query.value(i).toString());
    if (query.value(++i).isValid())
        setLinkURL(query.value(i).toString());
    if (query.value(++i).isValid())
        setLinkName(query.value(++i).toString());
    if (query.value(++i).isValid())
        setComments(query.value(i).toString());
    if (query.value(++i).isValid())
        setSource(query.value(i).toString());
    if (query.value(++i).isValid())
        setType(query.value(i).toString());
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

void Description::setLinkURL(QString url)
{
    set(NULLMASK_DESCRIPTION_LINKURL);
    _link_url = url;
}

void Description::setLinkName(QString name)
{
    set(NULLMASK_DESCRIPTION_LINKNAME);
    _link_name = name;
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

