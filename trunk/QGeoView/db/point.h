#ifndef POINT_H
#define POINT_H

#include <QObject>
#include "databaseobject.h"
#include "accuracy.h"
#include "db/exceptions.h"

// NULLMASK_ID is set in db/databaseobject.h ans is 0x1 DO NOT USE 0x1 HERE!!!
#define NULLMASK_TIME               0x2
#define NULLMASK_ELEVATION          0x4
#define NULLMASK_MAGNETICVARIATION  0x8
#define NULLMASK_GEOIDHEIGHT        0x10
#define NULLMASK_SYMBOL             0x20
#define NULLMASK_LATITUDE           0x40
#define NULLMASK_LONGITUDE          0x80
#define NULLMASK_ACCURACY           0x100
#define NULLMASK_FIX                0x200
#define NULLMASK_SATELITES          0x400
#define NULLMASK_HORIZONTALDOP      0x800
#define NULLMASK_VERTICALDOP        0x1000
#define NULLMASK_POSITIONDOP         0x2000
#define NULLMASK_AGEOFDGPSDATA      0x4000
#define NULLMASK_DGPSID             0x8000

class Point : public DatabaseObject
{
    Q_OBJECT
public:
    Point(QObject *parent = 0);
    ~Point();
    void addBindValues(QSqlQuery query);

signals:

public slots:
protected:
    QStringList fields();
private:
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

    Accuracy *_accuracy;

};
#endif // POINT_H
