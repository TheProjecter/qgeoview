#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H

#include <QObject>
#include <QSqlQuery>
#include "database.h"

#define NULLMASK_ID                 0x1

class DatabaseObject : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseObject(QObject *parent = 0);
    DatabaseObject(Database *db);
    bool isSet(int value);

signals:
    void saved();
    void changed();
    void removed();
public slots:
    virtual void save() = 0;
    virtual void remove() = 0;
private:
    int _id;
    int _nullMask;
    virtual QStringList fields() = 0;
    virtual void addBindValues(QSqlQuery query) = 0;
    Database *_db;
};

#endif // DATABASEOBJECT_H
