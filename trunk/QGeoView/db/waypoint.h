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
    Waypoint(Database *db, int id=0);
    Waypoint(Database *db, QSqlQuery query);
    Waypoint(const Waypoint &original);
    void addBindValues(QSqlQuery query);
    void setIntValue(int mask, int value);
    int getIntValue(int mask);
    QString table();
    Point getPoint();
    Description getDescription();
    QString summary();
    QStringList fields();
    static QStringList fieldNames();
protected:
    void loadValues(QSqlQuery query, bool loadID=false);
private:
    int _fk_point;
    int _fk_description;
};

#endif