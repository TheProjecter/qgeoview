#ifndef POINT_H
#define POINT_H

#include <QObject>
#include "databaseobject.h"
#include "accuracy.h"

class Point : public DatabaseObject
{
    Q_OBJECT
public:
    explicit Point(QObject *parent = 0);

signals:

public slots:
private:
    QString _time;
    float _elevation;
    float _magneticVariation;
    float _geoIDHeight;
    QString _symbol;
    float _latitude;
    float _longitude;
    Accuracy *_accuracy;

};
#endif // POINT_H
