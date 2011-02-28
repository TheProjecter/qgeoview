#include "databaseobject.h"

DatabaseObject::DatabaseObject(QObject *parent) :
    QObject(parent)
{
}

DatabaseObject::DatabaseObject(Database *db) :
    _db(db)
{

}


bool DatabaseObject::isSet(int value)
{
    return _nullMask & value;
}


void DatabaseObject::save()
{
    QSqlQuery query;
    _db->transaction();
    QString query_string;
    QStringList field_names = fields();

    if (isSet(NULLMASK_ID)) {   // update
        query_string = "UPDATE Points SET " + field_names.join("=?, ") + "=? WHERE id=" + _id + ";";
        query.prepare(query_string);
        query.addBindValue(_id);
    } else {                    // insert
        query_string = "INSERT INTO Points (id, " + field_names.join(", ") + ") VALUES (?" + QString(", ?").repeated(field_names.count()) + ");";
        query.prepare(query_string);
    }
    addBindValues(query);
    _db->commit();
}
