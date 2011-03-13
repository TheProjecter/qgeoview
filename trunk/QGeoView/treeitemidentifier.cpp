#include "treeitemidentifier.h"
#include "exceptions.h"

TreeItemIdentifier::TreeItemIdentifier() :
    _db(NULL),
    _type(0),
    _id(0)
{
}

TreeItemIdentifier::TreeItemIdentifier(Database *db, tstruct ts) :
    _db(db),
    _type(ts.type),
    _id(ts.id)
{}

TreeItemIdentifier::TreeItemIdentifier(const TreeItemIdentifier &original) :
    _db(original._db),
    _type(original._type),
    _id(original._id)
{
}

TreeItemIdentifier::TreeItemIdentifier(Database *db, int type, int id) :
    _db(db),
    _type(type),
    _id(id)
{
}

TreeItemIdentifier::~TreeItemIdentifier() {}

int TreeItemIdentifier::type()
{
    return _type;
}

QString TreeItemIdentifier::categoryName()
{
    if (_type != TREE_TYPE_CATEGORY)
        throw InvalidTreeItemIdentifierException(_type, TREE_TYPE_CATEGORY);
    switch(_id) {
        case TREE_CATEGORY_CACHES:
            return "Caches";
        case TREE_CATEGORY_WAYPOINTS:
            return "Waypoints";
    }
    throw InvalidTreeItemCategoryException(_id);
}

Cache TreeItemIdentifier::cache()
{
    if (_type != TREE_TYPE_CACHE)
        throw InvalidTreeItemIdentifierException(_type, TREE_TYPE_CACHE);
    return Cache(_db, _id);
}

Waypoint TreeItemIdentifier::waypoint()
{
    if (_type != TREE_TYPE_WAYPOINT)
        throw InvalidTreeItemIdentifierException(_type, TREE_TYPE_WAYPOINT);
    return Waypoint(_db, _id);
}
