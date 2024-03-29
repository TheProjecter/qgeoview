#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QSqlQuery>
#include <QObject>
#include "databaseobject.h"
#include "description.h"
#include "point.h"

#define NULLMASK_WAYPOINT_POINT         0x1
#define NULLMASK_WAYPOINT_DESCRIPTION   0x2

class Waypoint : public DatabaseObject
{
    Q_OBJECT
public:
    Waypoint(QSqlDatabase *db, int id=0);
    Waypoint(QSqlDatabase *db, QSqlQuery query);
    void addBindValues(QSqlQuery query);
    QString table();
    static QString tableName();
    Point *getPoint();
    Description *getDescription();
    QString summary();
    QStringList fields();
    static QStringList fieldNames();
    static QList<Waypoint*> getAll(QSqlDatabase *db);
    void setPoint(int point);
    void setDescription(int description);
protected:
    void loadValues(QSqlQuery query, bool loadID=false);
private:
    int _fk_point;
    int _fk_description;
};

#endif
