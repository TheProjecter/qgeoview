#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "db/databaseobject.h"

class DBException {};

class NoDatabaseFoundException : public DBException {
public:
    NoDatabaseFoundException(QString location);
    QString location() {return _location;}
protected:
    QString _location;
};

class WrongDatatypeForMaskException : public DBException {
public:
    WrongDatatypeForMaskException(DatabaseObject *o, int mask, QString datatype) : _o(o), _mask(mask), _datatype(datatype) {}
    DatabaseObject *object() {return _o;}
    int mask() {return _mask;}
    QString datatype() {return _datatype;}
protected:
    DatabaseObject *_o;
    int _mask;
    QString _datatype;
};

class MaskNotFoundException : public DBException {
public:
    MaskNotFoundException(DatabaseObject *o, int mask, QString datatype) : _o(o), _mask(mask), _datatype(datatype) {}
    DatabaseObject *object() {return _o;}
    int mask() {return _mask;}
    QString datatype() {return _datatype;}
protected:
    DatabaseObject *_o;
    int _mask;
    QString _datatype;
};

class DBValueNotSetException : public DBException {
public:
    DBValueNotSetException(DatabaseObject *o, int mask, QString datatype) : _o(o), _mask(mask), _datatype(datatype) {}
    DatabaseObject *object() {return _o;}
    int mask() {return _mask;}
    QString datatype() {return _datatype;}
protected:
    DatabaseObject *_o;
    int _mask;
    QString _datatype;
};

class IDNotSetException : public DBException {
public:
    IDNotSetException(DatabaseObject *o) : _o(o) {}
    DatabaseObject *object() {return _o;}
protected:
    DatabaseObject *_o;
};

class IDAlreadySetException : public DBException {
public:
    IDAlreadySetException(DatabaseObject *o, int id) : _o(o), _id(id) {}
    DatabaseObject *object() {return _o;}
    int id() {return _id;}
protected:
    DatabaseObject *_o;
    int _id;
};

class NotInDatabaseException : public DBException {
public:
    NotInDatabaseException(DatabaseObject *o) : _o(o) {}
    DatabaseObject *object() {return _o;}
protected:
    DatabaseObject *_o;
};


#endif // EXCEPTIONS_H
