#include <QSqlError>
#include <QSqlDatabase>
#include <QStringList>
#include <QVariant>
#include "databaseobject.h"
#include "exceptions.h"

DatabaseObject::DatabaseObject(QSqlDatabase *db, int id) :
    _db(db),
    _id(id),
    _nullMask(0x0)
{}

void DatabaseObject::load()
{
    if (!_id)
        throw IDNotSetException(this);
    QSqlQuery query;
    QString query_string = "SELECT " + fields().join(",") + " FROM " + table() + " WHERE id=?;";
    query.prepare(query_string);
    query.addBindValue(QVariant::fromValue<int>(_id));
    if (!query.exec())
        throw query;
    if (!query.first())
        throw query;
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
    QStringList field_names = fields();
    if (_id) {  // perform update
        query.prepare("UPDATE " + table() + " SET " + field_names.join("=?, ") + "=? WHERE id=" + _id + ";");
        query.addBindValue(_id);
    } else {    // perform insert
        query.prepare("INSERT INTO " + table() + " (" + field_names.join(", ") + ") VALUES (?" + QString(", ?").repeated(field_names.count() - 1) + ");");
    }
    addBindValues(query);
    if (!query.exec()) {
        throw query;
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
    cleanup();
    QSqlQuery query;
    _db->transaction();
    query.prepare("DELETE FROM " + table() + " WHERE id=?;");
    query.addBindValue(_id);
    if (!query.exec())
        throw query;
    _db->commit();
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

// Defined in case a class does not require cleanup when being removed.
void DatabaseObject::cleanup()
{}

// The following only need to be implemented if the item handles the respective type.

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
