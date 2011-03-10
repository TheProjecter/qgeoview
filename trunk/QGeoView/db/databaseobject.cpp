#include <iostream>
#include <QSqlError>
#include "databaseobject.h"
#include "db/exceptions.h"

DatabaseObject::DatabaseObject(Database *db) :
    _db(db),
    _id(0)
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

    if (_id) {   // update
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
    if (!_id) {
        setID(query.lastInsertId().toInt());
    }
    std::cout << "\tdone" << std::endl;
}

void DatabaseObject::remove()
{
    if (!_id)
        throw NotInDatabaseException();
    QSqlQuery query;
    _db->transaction();
    query.prepare("REMOVE FROM " + table() + " WHERE id=" + _id);
}

void DatabaseObject::setID(int value)
{
    if (_id) {
        throw IDAlreadySetException();
    }
    _id = value;
}

void DatabaseObject::setQStringValue(int mask, QString value)
{
    Q_UNUSED(mask)
    Q_UNUSED(value)
    throw InvalidMaskException();
}

void DatabaseObject::setFloatValue(int mask, float value)
{
    Q_UNUSED(mask)
    Q_UNUSED(value)
    throw InvalidMaskException();
}

void DatabaseObject::setIntValue(int mask, int value)
{
    Q_UNUSED(mask)
    Q_UNUSED(value)
    throw InvalidMaskException();
}

void DatabaseObject::setBoolValue(int mask, bool value)
{
    Q_UNUSED(mask)
    Q_UNUSED(value)
    throw InvalidMaskException();
}

int DatabaseObject::getID()
{
    if (!_id)
        throw IDNotSetException();
    return _id;
}

QString DatabaseObject::getQStringValue(int mask)
{
    Q_UNUSED(mask)
    throw InvalidMaskException();
}

float DatabaseObject::getFloatValue(int mask)
{
    Q_UNUSED(mask)
    throw InvalidMaskException();
}

int DatabaseObject::getIntValue(int mask)
{
    Q_UNUSED(mask)
    throw InvalidMaskException();
}

bool DatabaseObject::getBoolValue(int mask)
{
    Q_UNUSED(mask)
    throw InvalidMaskException();
}

