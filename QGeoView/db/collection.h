#ifndef COLLECTION_H
#define COLLECTION_H

#include <QSqlQuery>
#include <QObject>
#include <QStringList>
#include "databaseobject.h"
#include "db/cache.h"


#define NULLMASK_COLLECTION_NAME        0x1
#define NULLMASK_COLLECTION_DESCRIPTION 0x2

class Collection : public DatabaseObject
{
    Q_OBJECT
public:
    Collection(QSqlDatabase *db, int id=0);
    Collection(QSqlDatabase *db, QSqlQuery query);
    void addBindValues(QSqlQuery query);
    void setQStringValue(int mask, QString value);
    QString getQStringValue(int mask);
    QString summary();
    QString table();
    static QString tableName();
    QStringList fields();
    static QStringList fieldNames();
    void addCache(int id);
    void removeCache(int id);
    void addWaypoint(int id);
    void removeWaypoint(int id);
    void cleanup();
    static QList<Collection*> getAll(QSqlDatabase *db);
    QList<Cache*> caches();
    QList<Waypoint*> waypoints();
    void setName(QString name);
    void setDescription(QString description);
    QString getName();
    QString getDescription();
protected:
    void loadValues(QSqlQuery query, bool loadID=false);
private:
    QString _name;
    QString _description;
};

#endif // COLLECTION_H
