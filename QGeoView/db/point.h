#ifndef POINT_H
#define POINT_H

#include <QObject>
#include "databaseobject.h"
#include "db/exceptions.h"

#define NULLMASK_POINT_TIME               0x1
#define NULLMASK_POINT_ELEVATION          0x2
#define NULLMASK_POINT_MAGNETICVARIATION  0x4
#define NULLMASK_POINT_GEOIDHEIGHT        0x8
#define NULLMASK_POINT_SYMBOL             0x10
#define NULLMASK_POINT_LATITUDE           0x20
#define NULLMASK_POINT_LONGITUDE          0x40
#define NULLMASK_POINT_ACCURACY           0x800
#define NULLMASK_POINT_FIX                0x100
#define NULLMASK_POINT_SATELITES          0x200
#define NULLMASK_POINT_HORIZONTALDOP      0x400
#define NULLMASK_POINT_VERTICALDOP        0x8000
#define NULLMASK_POINT_POSITIONDOP        0x1000
#define NULLMASK_POINT_AGEOFDGPSDATA      0x2000
#define NULLMASK_POINT_DGPSID             0x4000

class Point : public DatabaseObject
{
    Q_OBJECT
public:
    Point(Database *db);
    ~Point();
    void addBindValues(QSqlQuery query);
    void setQStringValue(int mask, QString value);
    void setFloatValue(int mask, float value);
    void setIntValue(int mask, int value);
    QString getQStringValue(int mask);
    float getFloatValue(int mask);
    int getIntValue(int mask);

protected:
    QStringList fields();
private:
    QString table();
    QString _time;
    float _elevation;
    float _magneticVariation;
    float _geoIDHeight;
    QString _symbol;
    float _latitude;
    float _longitude;
    QString _fix;
    int _satelites;
    float _horizontalDOP;
    float _verticalDOP;
    float _positionDOP;
    float _ageOfDGPSData;
    int _DGPSID;

};
#endif // POINT_H
