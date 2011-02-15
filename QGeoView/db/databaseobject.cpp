#include "databaseobject.h"

DatabaseObject::DatabaseObject(QObject *parent) :
    QObject(parent)
{
}

DatabaseObject::DatabaseObject(Database *db) :
    _db(db)
{

}
