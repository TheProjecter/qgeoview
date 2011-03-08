#ifndef CACHE_H
#define CACHE_H

#include <QObject>
#include "databaseobject.h"
#include "db/exceptions.h"
#include "db/waypoint.h"

// NULLMASK_ID is set in db/databaseobject.h and is 0x1 DO NOT USE 0x1 HERE!!!
#define NULLMASK_CACHE_NAME                 0x2
#define NULLMASK_CACHE_PLACEDBY             0x4
#define NULLMASK_CACHE_OWNERID              0x8
#define NULLMASK_CACHE_OWNERGUID            0x10
#define NULLMASK_CACHE_OWNERNAME            0x20
#define NULLMASK_CACHE_TYPE                 0x40
#define NULLMASK_CACHE_CONTAINER            0x80
#define NULLMASK_CACHE_DIFFICULTY           0x100
#define NULLMASK_CACHE_TERRAIN              0x200
#define NULLMASK_CACHE_COUNTRY              0x400
#define NULLMASK_CACHE_STATE                0x800
#define NULLMASK_CACHE_SHORTDESCRIPTION     0x1000
#define NULLMASK_CACHE_SHORTDESCRIPTIONHTML 0x2000
#define NULLMASK_CACHE_LONGDESCRIPTION      0x4000
#define NULLMASK_CACHE_LONGDESCRIPTIONHTML  0x8000
#define NULLMASK_CACHE_ENCODEDHINTS         0x10000
#define NULLMASK_CACHE_WAYPOINT             0x20000


class Cache : public DatabaseObject
{
    Q_OBJECT
public:
    Cache(Database *db);
    ~Cache();
    void addBindValues(QSqlQuery query);
    void setIntValue(int mask, int value);
    void setFloatValue(int mask, float value);
    void setQStringValue(int mask, QString value);
    void setBoolValue(int mask, bool value);
    int getIntValue(int mask);
    float getFloatValue(int mask);
    QString getQStringValue(int mask);
    bool getBoolValue(int mask);
protected:
    QStringList fields();
private:
    QString table();
    QString _name;
    QString _placed_by;
    int _owner_id;
    QString _owner_guid;
    QString _owner_name;
    QString _type;
    QString _container;
    float _difficulty;
    float _terrain;
    QString _country;;
    QString _state;
    QString _short_description;
    bool _short_description_html;
    QString _long_description;
    bool _long_description_html;
    QString _encoded_hints;
    int _waypoint;
    Waypoint *_waypoint_object;

signals:

public slots:

};

#endif // CACHE_H
