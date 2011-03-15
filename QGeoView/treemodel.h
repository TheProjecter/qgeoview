#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QStandardItemModel>
#include <QMimeData>

#include "db/database.h"
#include "db/collection.h"
#include "db/cache.h"
#include "db/waypoint.h"
#include "exceptions.h"

#define INFO_TYPE_NONE      1
#define INFO_TYPE_CACHE     2
#define INFO_TYPE_WAYPOINT  3
#define INFO_TYPE_ROUTE     4
#define INFO_TYPE_TRACK     5

class TreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    TreeModel(Database *db, QObject *parent = 0);
    ~TreeModel();
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    QStringList mimeTypes() const;
    Qt::DropActions supportedDropActions() const;
    int collectionID();
    Collection *collection();
signals:
    void cacheSelected(Cache cache);
    void waypointSelected(Waypoint waypoint);
    void cacheDragged(int id);
    void cacheDropped(int id);
    void waypointDragged(int id);
    void waypointDropped(int id);
public slots:
    void item_selected(QModelIndex index);
    void refresh(Collection *collection=NULL);
private:
    Database *_db;
    Collection *_collection;
    QStandardItem _caches;
    QStandardItem _waypoints;
};

#endif // TREEMODEL_H
