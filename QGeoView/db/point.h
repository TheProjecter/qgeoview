#ifndef POINT_H
#define POINT_H

#include <QObject>
#include "databaseobject.h"

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
    Point(QSqlDatabase *db, int id=0);
    Point(QSqlDatabase *db, QSqlQuery query);
    void addBindValues(QSqlQuery query);
    void setQStringValue(int mask, QString value);
    void setFloatValue(int mask, float value);
    void setIntValue(int mask, int value);
    QString getQStringValue(int mask);
    float getFloatValue(int mask);
    int getIntValue(int mask);
    QString table();
    static QString tableName();
    QStringList fields();
    static QStringList fieldNames();
    void setTime(QString time);
    void setSymbol(QString symbol);
    void setFix(QString fix);
    void setElevation(float elevation);
    void setMagneticVariation(float magnetic_variation);
    void setGeoIDHeight(float geo_id_height);
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    void setHorizontalDOP(float horizontal_dop);
    void setVerticalDOP(float vertical_dop);
    void setPositionDOP(float position_dop);
    void setAgeOfDGPSData(float age_of_dgps_data);
    void setSatelites(int satelites);
    void setDGPSID(int dgps_id);
    QString getTime();
    QString getSymbol();
    QString getFix();
    float getElevation();
    float getMagneticVariation();
    float getGeoIDHeight();
    float getLatitude();
    float getLongitude();
    float getHorizontalDOP();
    float getVerticalDOP();
    float getPositionDOP();
    float getAgeOfDGPSData();
    int getSatelites();
    int getDGPSID();
protected:
    void loadValues(QSqlQuery query, bool loadID=false);
private:
    QString _time;
    QString _symbol;
    QString _fix;
    float _elevation;
    float _magnetic_variation;
    float _geo_id_height;
    float _latitude;
    float _longitude;
    float _horizontal_dop;
    float _vertical_dop;
    float _position_dop;
    float _age_of_dgps_data;
    int _satelites;
    int _dgps_id;
};
#endif // POINT_H
