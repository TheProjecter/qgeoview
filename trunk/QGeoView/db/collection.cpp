#include "collection.h"

Collection::Collection(Database *db, int id) :
    DatabaseObject(db, id)
{
    if (id)
        load();
}

Collection::Collection(const Collection &original) :
    DatabaseObject(original),
    _name(original._name),
    _description(original._description)
{
}

QString Collection::table()
{
    return "Collection";
}

QStringList Collection::fields()
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

void Collection::loadValues(QSqlQuery query)
{
    int i=-1;
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
