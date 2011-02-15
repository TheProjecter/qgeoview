#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QObject>
#include "databaseobject.h"
#include "description.h"
#include "point.h"

class Waypoint : public DatabaseObject
{
    Q_OBJECT
public:
    explicit Waypoint(QObject *parent = 0);

signals:

public slots:
private:
    Description *_description;
    Point *_point;
};

#endif // WAYPOINT_H
