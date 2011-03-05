#include "collection.h"

Collection::Collection(Database *db) :
    DatabaseObject(db)
{
}

Collection::~Collection()
{
}

QString Collection::table()
{
    return "Collections";
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

void Collection::setQStringValue(int mask, QString value)
{
    if (!((NULLMASK_COLLECTION_NAME | NULLMASK_COLLECTION_DESCRIPTION) & mask))
        throw InvalidMaskException();
    switch (mask) {
        case NULLMASK_COLLECTION_NAME:
            _name = value;
            break;
        case NULLMASK_COLLECTION_DESCRIPTION:
            _description = value;
            break;
        default:
            throw MaskNotFoundException();
    }
    set(mask);
}

QString Collection::getQStringValue(int mask)
{
    if (!isSet(mask))
        throw DBValueNotSetException();
    if (!((NULLMASK_COLLECTION_NAME | NULLMASK_COLLECTION_DESCRIPTION) & mask))
        throw InvalidMaskException();
    switch(mask) {
        case NULLMASK_COLLECTION_NAME:
            return _name;
        case NULLMASK_COLLECTION_DESCRIPTION:
            return _description;
    }
    throw MaskNotFoundException();
}
