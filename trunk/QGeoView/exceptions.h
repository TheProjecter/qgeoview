#ifndef DB_EXCEPTIONS_H
#define DB_EXCEPTIONS_H

#include "db/databaseobject.h"

class QGeoViewException {
public:
    QString name() {return "QGeoViewException";}
    QString error() {return "unkown";}
};

class DBException : public QGeoViewException {
public:
    QString name() {return "DBException";}
    QString error() {return "unkown";}
};

class NoDatabaseFoundException : public DBException {
public:
    NoDatabaseFoundException(QString location) : _location(location) {}
    QString name() {return "NoDatabaseFoundException";}
    QString error() {return "No database found at: " + _location;}
private:
    QString _location;
};

class WrongDatatypeForMaskException : public DBException {
public:
    WrongDatatypeForMaskException(DatabaseObject *o, int mask, QString datatype) : _o(o), _mask(mask), _datatype(datatype) {}
    QString name() {return "WrongDatatypeForMaskException";}
    QString error() {return _o->table() + "::NULLMASK " + _mask + " is not of type " + _datatype;}
protected:
    DatabaseObject *_o;
    int _mask;
    QString _datatype;
};

class MaskNotFoundException : public DBException {
public:
    MaskNotFoundException(DatabaseObject *o, int mask, QString datatype) : _o(o), _mask(mask), _datatype(datatype) {}
    QString name() {return "MaskNotFoundException";}
    QString error() {return _o->table() + "::" + _mask + " Not found for type " + _datatype;}
protected:
    DatabaseObject *_o;
    int _mask;
    QString _datatype;
};

class DBValueNotSetException : public DBException {
public:
    DBValueNotSetException(DatabaseObject *o, int mask, QString datatype) : _o(o), _mask(mask), _datatype(datatype) {}
    QString name() {return "DBValueNotSetException";}
    QString error() {return _o->table() + ".id(" + _o->getID() + ") " + _datatype + "(" + _mask + ") is NULL";}
protected:
    DatabaseObject *_o;
    int _mask;
    QString _datatype;
};

class IDNotSetException : public DBException {
public:
    IDNotSetException(DatabaseObject *o) : _o(o) {}
    QString name() {return "IDNotSetException";}
    QString error() {return "Exception: ID for " + _o->table() + " has no ID";}
protected:
    DatabaseObject *_o;
};

class IDAlreadySetException : public DBException {
public:
    IDAlreadySetException(DatabaseObject *o, int id) : _o(o), _id(id) {}
    QString name() {return "IDAlreadySetException";}
    QString error() {return "Tried to set " + _o->table() + ".id(" + _o->getID() + ") to " + _id;}
protected:
    DatabaseObject *_o;
    int _id;
};

class NotInDatabaseException : public DBException {
public:
    NotInDatabaseException(DatabaseObject *o) : _o(o) {}
    QString name() {return "NotInDatabaseException";}
    QString error() {return "Tried deleting " + _o->table() + ", but it isn't in the database!";}
protected:
    DatabaseObject *_o;
};

class InvalidTreeItemCategoryException : QGeoViewException {
public:
    InvalidTreeItemCategoryException(int id) : _id(id) {}
    QString name() {return "InvalidTreeItemCategoryException";}
    QString error() {return QString(_id) + "is not a valid TreeCategory";}
private:
    int _id;
};

#endif // DB_EXCEPTIONS_H
