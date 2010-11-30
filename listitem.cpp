#include "listitem.h"

ListItem::ListItem(int type, int id, QString name) :
    QListWidgetItem(name),
    _type(type),
    _id(id),
    _name(name)
{
}

ListItem::ListItem(int type, int id, QString name, QIcon icon) :
    QListWidgetItem(icon, name),
    _type(type),
    _id(id),
    _name(name)
{
}

