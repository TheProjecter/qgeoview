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
    DatabaseObject(Database *db);
    bool isSet(int mask);
    void set(int mask);
protected:
    Database *_db;
signals:
    void saved();
    void changed();
    void removed();
public slots:
    virtual void save();
    virtual void remove();
private:
    int _id;
    int _nullMask;
    virtual QStringList fields() = 0;
    virtual void addBindValues(QSqlQuery query) = 0;
    virtual QString table() = 0;
};

#endif // DATABASEOBJECT_H
