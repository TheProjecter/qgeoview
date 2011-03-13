#ifndef TREEITEMIDENTIFIER_H
#define TREEITEMIDENTIFIER_H

#include <QObject>
#include "db/database.h"
#include "db/cache.h"
#include "db/waypoint.h"

#define TREE_TYPE_CATEGORY  1
#define TREE_TYPE_CACHE     2
#define TREE_TYPE_WAYPOINT  3

#define TREE_CATEGORY_CACHES    1
#define TREE_CATEGORY_WAYPOINTS 2

typedef struct {
    int type;
    int id;
} tstruct;

class TreeItemIdentifier
{
public:
    TreeItemIdentifier();
    TreeItemIdentifier(const TreeItemIdentifier &original);
    TreeItemIdentifier(Database *db, tstruct ts);
    TreeItemIdentifier(Database *db, int type, int id);
    ~TreeItemIdentifier();
    int type();
    QString categoryName();
    Cache cache();
    Waypoint waypoint();
private:
    Database *_db;
    int _type;
    int _id;
};

Q_DECLARE_METATYPE(TreeItemIdentifier);

#endif // TREEITEMIDENTIFIER_H
