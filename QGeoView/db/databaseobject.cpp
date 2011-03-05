#include <iostream>
#include <QSqlError>
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
        query_string = "INSERT INTO " + table() + " (" + field_names.join(", ") + ") VALUES (?" + QString(", ?").repeated(field_names.count() - 1) + ");";
        query.prepare(query_string);
    }
    addBindValues(query);
    if (!query.exec()) {
        QSqlError error = query.lastError();
        std::cerr << "Query Error: " << std::endl;
        std::cerr << "\t Query: " << query.lastQuery().toStdString() << std::endl;
        std::cerr << "\tdriverText: " << error.driverText().toStdString() << std::endl;
        std::cerr << "\tdatabaseText: " << error.databaseText().toStdString() << std::endl;
    }
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

void DatabaseObject::setQStringValue(int mask, QString value)
{
        throw InvalidMaskException();
}

void DatabaseObject::setFloatValue(int mask, float value)
{
        throw InvalidMaskException();
}

void DatabaseObject::setIntValue(int mask, int value)
{
        throw InvalidMaskException();
}

QString DatabaseObject::getQStringValue(int mask)
{
        throw InvalidMaskException();
}

float DatabaseObject::getFloatValue(int mask)
{
        throw InvalidMaskException();
}

int DatabaseObject::getIntValue(int mask)
{
        throw InvalidMaskException();
}


