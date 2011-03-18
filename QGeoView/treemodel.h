#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QStandardItemModel>
#include <QMimeData>

#include "db/collection.h"
#include "db/cache.h"
#include "db/waypoint.h"
#include "exceptions.h"

class TreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    TreeModel(QSqlDatabase *db, QObject *parent = 0);
    ~TreeModel();
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    QStringList mimeTypes() const;
    Qt::DropActions supportedDropActions() const;
signals:
    void cacheSelected(Cache cache);
    void waypointSelected(Waypoint waypoint);
    void cacheDragged(int id);
    void cacheDropped(int id);
    void waypointDragged(int id);
    void waypointDropped(int id);
public slots:
    void showAll();
    void showNone();
    void showCollection(Collection collection);
    void itemSelected(QModelIndex index);
    void refresh();
protected:
    void setup();
private:
    QSqlDatabase *_db;
    Collection *_collection;
    bool _all;
    QStandardItem _caches;
    QStandardItem _waypoints;
};

#endif // TREEMODEL_H
