#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H

#include <QObject>
#include <QSqlQuery>

#define INFO_TYPE_NONE      1
#define INFO_TYPE_CACHE     2
#define INFO_TYPE_WAYPOINT  3
#define INFO_TYPE_ROUTE     4
#define INFO_TYPE_TRACK     5

class DatabaseObject : public QObject
{
    Q_OBJECT
public:
    DatabaseObject(QSqlDatabase *db, int id=0);
    bool isSet(int mask);
    void set(int mask);
    virtual QStringList fields() = 0;
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
    virtual void cleanup();
    virtual void save();
    virtual void remove();
    virtual QString table() = 0;
    void ensure(int mask);
protected:
    void setID(int id);
    virtual void addBindValues(QSqlQuery query) = 0;
    virtual void loadValues(QSqlQuery query, bool loadID=false) = 0;
    void load();
    QSqlDatabase *_db;
    int _id;
    int _nullMask;
};

#endif // DATABASEOBJECT_H
