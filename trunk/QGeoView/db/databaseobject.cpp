#include <iostream>
#include <QSqlError>
#include "databaseobject.h"
#include "exceptions.h"

DatabaseObject::DatabaseObject(Database *db, int id) :
    _db(db),
    _id(id)
{
}

DatabaseObject::DatabaseObject(const DatabaseObject &original) :
    _db(original._db),
    _id(original._id),
    _nullMask(original._nullMask)
{

}

void DatabaseObject::load()
{
    if (!_id)
        throw IDNotSetException(this);
    QSqlQuery query;
    QString query_string = "SELECT " + fields().join(",") + " FROM " + table() + " WHERE id=?;";
    query.prepare(query_string);
    query.addBindValue(getID());
    if (query.exec() && query.first())
        loadValues(query);
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
    QSqlQuery query;
    _db->transaction();
    QString query_string;
    QStringList field_names = fields();
    if (_id) {   // update
        query_string = "UPDATE " + table() + " SET " + field_names.join("=?, ") + "=? WHERE id=" + _id + ";";
        query.prepare(query_string);
        query.addBindValue(_id);
    } else {                    // insert
        query_string = "INSERT INTO " + table() + " (" + field_names.join(", ") + ") VALUES (?" + QString(", ?").repeated(field_names.count() - 1) + ");";
        query.prepare(query_string);
    }
    addBindValues(query);
    if (!query.exec()) {
        QSqlError error = query.lastError();
        std::cerr << "Query Error: " << std::endl;
        std::cerr << "\t Last Query:" << std::endl << "\t\t" << query.lastQuery().toStdString() << std::endl;
        std::cerr << "\t Executed Query:" << std::endl << "\t\t" << query.executedQuery().toStdString() << std::endl;
        std::cerr << "\tdriverText: " << error.driverText().toStdString() << std::endl;
        std::cerr << "\tdatabaseText: " << error.databaseText().toStdString() << std::endl;
    }
    _db->commit();
    if (!_id) {
        setID(query.lastInsertId().toInt());
    }
}

void DatabaseObject::remove()
{
    if (!_id)
        throw NotInDatabaseException(this);
    QSqlQuery query;
    _db->transaction();
    query.prepare("REMOVE FROM " + table() + " WHERE id=" + _id);
}

void DatabaseObject::setID(int value)
{
    if (_id) {
        throw IDAlreadySetException(this, value);
    }
    _id = value;
}

void DatabaseObject::setQStringValue(int mask, QString value)
{
    Q_UNUSED(mask)
    Q_UNUSED(value)
    throw MaskNotFoundException(this, mask, "QString");
}

void DatabaseObject::setFloatValue(int mask, float value)
{
    Q_UNUSED(mask)
    Q_UNUSED(value)
    throw MaskNotFoundException(this, mask, "Float");
}

void DatabaseObject::setIntValue(int mask, int value)
{
    Q_UNUSED(mask)
    Q_UNUSED(value)
    throw MaskNotFoundException(this, mask, "Int");
}

void DatabaseObject::setBoolValue(int mask, bool value)
{
    Q_UNUSED(mask)
    Q_UNUSED(value)
    throw MaskNotFoundException(this, mask, "Bool");
}

int DatabaseObject::getID()
{
    if (!_id)
        throw IDNotSetException(this);
    return _id;
}

QString DatabaseObject::getQStringValue(int mask)
{
    Q_UNUSED(mask)
    throw MaskNotFoundException(this, mask, "QString");
}

float DatabaseObject::getFloatValue(int mask)
{
    Q_UNUSED(mask)
    throw MaskNotFoundException(this, mask, "Float");
}

int DatabaseObject::getIntValue(int mask)
{
    Q_UNUSED(mask)
    throw MaskNotFoundException(this, mask, "Int");
}

bool DatabaseObject::getBoolValue(int mask)
{
    Q_UNUSED(mask)
    throw MaskNotFoundException(this, mask, "Bool");
}

