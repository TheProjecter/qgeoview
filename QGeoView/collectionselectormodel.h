#ifndef COLLECTIONSELECTORMODEL_H
#define COLLECTIONSELECTORMODEL_H
#include <QStandardItemModel>
#include <QComboBox>
#include <QMimeData>

#include "db/database.h"
#include "db/collection.h"
#include "db/cache.h"
#include "db/waypoint.h"
#include "exceptions.h"

class CollectionSelectorModel : public QStandardItemModel
{
    Q_OBJECT
public:
    CollectionSelectorModel(Database *db, bool all=false);
    ~CollectionSelectorModel();
    Collection *collection();
signals:
    void collectionSelected(Collection collection);
    void allSelected();
    void noneSelected();
    void refreshed();
public slots:
    void indexChanged(int index);
    void refresh();
private:
    Database *_db;
    Collection *_collection;
    QStandardItem *_root;
    bool _all;
    QList<int> _ids;
};

#endif // COLLECTIONSELECTORMODEL_H
