#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H

#include <QObject>
#include <QSqlQuery>
#include "database.h"

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
protected:
    void setID(int id);
private:
    int _id;
    int _nullMask;
    virtual QStringList fields() = 0;
    virtual void addBindValues(QSqlQuery query) = 0;
    virtual QString table() = 0;
};

#endif // DATABASEOBJECT_H
