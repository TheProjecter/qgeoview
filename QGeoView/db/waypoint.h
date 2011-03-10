#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QObject>
#include "databaseobject.h"
#include "db/exceptions.h"
#include "description.h"
#include "point.h"

#define NULLMASK_WAYPOINT_POINT         0x1
#define NULLMASK_WAYPOINT_DESCRIPTION   0x2

class Waypoint : public DatabaseObject
{
    Q_OBJECT
public:
    Waypoint(Database *db);
    ~Waypoint();
    void addBindValues(QSqlQuery query);
    void setIntValue(int mask, int value);
    int getIntValue(int mask);
protected:
    QStringList fields();
private:
    QString table();
    int _point;
    int _description;
    Point *_point_object;
    Description *_description_object;
};

#endif
