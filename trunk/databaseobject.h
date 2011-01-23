#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H

#include <QObject>
#include "database.h"

class DatabaseObject : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseObject(QObject *parent = 0);
    DatabaseObject(Database *db);

signals:
    void saved();
    void changed();
    void removed();
public slots:
    virtual void save() = 0;
    virtual void remove() = 0;
private:
    int _id;
    Database *_db;
};

#endif // DATABASEOBJECT_H
