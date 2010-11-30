#ifndef LISTITEM_H
#define LISTITEM_H

#include <QListWidgetItem>

#define LISTITEM_TYPE_NONE      0
#define LISTITEM_TYPE_CACHE     1
#define LISTITEM_TYPE_WAYPOINT  2
#define LISTITEM_TYPE_TRACK     3
#define LISTITEM_TYPE_ROUTE     4

class ListItem : public QListWidgetItem
{
public:
    ListItem(int type, int id, QString name);
    ListItem(int type, int id, QString name, QIcon icon);
private:
    int _type;
    int _id;
    QString _name;
};

#endif // LISTITEM_H
