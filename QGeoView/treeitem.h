#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

class TreeItem
{
public:
    TreeItem(TreeItem* parent = 0);
    ~TreeItem();

    void appendChild(TreeItem* child);

    TreeItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem* parent();
    TreeItem operator<<(QVariant data);
private:
    QList<TreeItem*> _childItems;
    QList<QVariant> _itemData;
    TreeItem* _parentItem;
};

#endif // TREEITEM_H
