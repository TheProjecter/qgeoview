#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H

#include <QObject>
#include <QSqlQuery>
#include "database.h"

class DatabaseObject : public QObject
{
    Q_OBJECT
public:
    DatabaseObject(Database *db, int id=0);
    DatabaseObject(const DatabaseObject &original);
    bool isSet(int mask);
    void set(int mask);
    virtual QStringList fields();
signals:
    void saved();
    void changed();
    void removed();
public slots:
    void setQStringValue(int mask, QString value);
    void setFloatValue(int mask, float value);
    void setIntValue(int mask, int value);
    void setBoolValue(int mask, bool value);
    int getID();
    QString getQStringValue(int mask);
    float getFloatValue(int mask);
    int getIntValue(int mask);
    bool getBoolValue(int mask);
    virtual void save();
    virtual void remove();
    virtual QString table() = 0;
protected:
    void setID(int id);
    virtual void addBindValues(QSqlQuery query) = 0;
    virtual void loadValues(QSqlQuery query, bool loadID=false) = 0;
    void load();
    Database *_db;
    int _id;
    int _nullMask;
};

#endif // DATABASEOBJECT_H
