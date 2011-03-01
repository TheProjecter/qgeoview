#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class DBException {};

class InvalidMaskException : public DBException {};
class NoDatabaseFoundException : public DBException {};
class WrongDatatypeForMakeException : public DBException {};
class MaskNotFoundException : public DBException {};
class DBValueNotSetException : public DBException {};

#endif // EXCEPTIONS_H
