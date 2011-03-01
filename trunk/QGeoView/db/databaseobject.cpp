#include <iostream>
#include "databaseobject.h"
#include "db/exceptions.h"

DatabaseObject::DatabaseObject(Database *db) :
    _db(db)
{

}


bool DatabaseObject::isSet(int mask)
{
    return _nullMask & mask;
}

void DatabaseObject::set(int mask)
{
    _nullMask |= mask;
}


void DatabaseObject::save()
{
    if (_db == NULL)
        throw NoDatabaseFoundException();
    std::cout << "save() called" << std::endl;
    QSqlQuery query;
    std::cout << "starting transaction" << std::endl;
    _db->transaction();
    std::cout << "\ttransaction started" << std::endl;
    QString query_string;
    QStringList field_names = fields();
    std::cout << "Performing save()" << std::endl;

    if (isSet(NULLMASK_ID)) {   // update
        std::cout << "\tupdating" << std::endl;
        query_string = "UPDATE " + table() + " SET " + field_names.join("=?, ") + "=? WHERE id=" + _id + ";";
        query.prepare(query_string);
        query.addBindValue(_id);
    } else {                    // insert
        std::cout << "\tinserting" << std::endl;
        query_string = "INSERT INTO " + table() + " (id, " + field_names.join(", ") + ") VALUES (?" + QString(", ?").repeated(field_names.count()) + ");";
        query.prepare(query_string);
    }
    addBindValues(query);
    _db->commit();
    std::cout << "\tdone" << std::endl;
}

void DatabaseObject::remove()
{
    if(isSet(NULLMASK_ID)) {
        QSqlQuery query;
        _db->transaction();
        query.prepare("REMOVE FROM " + table() + " WHERE id=" + _id);
    }
}
