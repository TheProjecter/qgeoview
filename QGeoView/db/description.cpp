#include "description.h"

Description::Description(Database *db) :
    DatabaseObject(db)
{
}

Description::~Description()
{
}

QString Description::table()
{
    return "Description";
}

QStringList Description::fields()
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

void Description::setQStringValue(int mask, QString value)
{
    if (!((NULLMASK_DESCRIPTION_NAME | NULLMASK_DESCRIPTION_LINKURL | NULLMASK_DESCRIPTION_LINKNAME | NULLMASK_DESCRIPTION_COMMENTS | NULLMASK_DESCRIPTION_SOURCE | NULLMASK_DESCRIPTION_TYPE) & mask))
        throw InvalidMaskException();
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
            throw MaskNotFoundException();
    }
    set(mask);
}

QString Description::getQStringValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException();
    if (!((NULLMASK_DESCRIPTION_NAME | NULLMASK_DESCRIPTION_LINKURL | NULLMASK_DESCRIPTION_LINKNAME | NULLMASK_DESCRIPTION_COMMENTS | NULLMASK_DESCRIPTION_SOURCE | NULLMASK_DESCRIPTION_TYPE) & mask))
        throw InvalidMaskException();
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
    throw MaskNotFoundException();
}
