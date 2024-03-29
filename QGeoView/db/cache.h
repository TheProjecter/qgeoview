#ifndef CACHE_H
#define CACHE_H

#include <QObject>
#include <QList>
#include "databaseobject.h"
#include "db/waypoint.h"

#define NULLMASK_CACHE_NAME                 0x1
#define NULLMASK_CACHE_PLACEDBY             0x2
#define NULLMASK_CACHE_OWNERID              0x4
#define NULLMASK_CACHE_OWNERGUID            0x8
#define NULLMASK_CACHE_OWNERNAME            0x10
#define NULLMASK_CACHE_TYPE                 0x20
#define NULLMASK_CACHE_CONTAINER            0x40
#define NULLMASK_CACHE_DIFFICULTY           0x80
#define NULLMASK_CACHE_TERRAIN              0x100
#define NULLMASK_CACHE_COUNTRY              0x200
#define NULLMASK_CACHE_STATE                0x400
#define NULLMASK_CACHE_SHORTDESCRIPTION     0x800
#define NULLMASK_CACHE_SHORTDESCRIPTIONHTML 0x1000
#define NULLMASK_CACHE_LONGDESCRIPTION      0x2000
#define NULLMASK_CACHE_LONGDESCRIPTIONHTML  0x4000
#define NULLMASK_CACHE_ENCODEDHINTS         0x8000
#define NULLMASK_CACHE_WAYPOINT             0x10000


class Cache : public DatabaseObject
{
    Q_OBJECT
public:
    Cache(QSqlDatabase *db, int id=0);
    Cache(QSqlDatabase *db, QSqlQuery query);
    QString table();
    static QString tableName();
    static QList<Cache*> getAll(QSqlDatabase *);
    void addBindValues(QSqlQuery query);
    Waypoint *getWaypoint();
    QList<int> getLogIDs();
    QString summary();
    QStringList fields();
    static QStringList fieldNames();
    void setName(QString name);
    void setPlacedBy(QString placed_by);
    void setOwnerGUID(QString owner_guid);
    void setOwnerName(QString owner_name);
    void setType(QString type);
    void setContainer(QString container);
    void setCountry(QString country);
    void setState(QString state);
    void setShortDescription(QString description, bool html=false);
    void setLongDescription(QString description, bool html=false);
    void setEncodedHints(QString encoded_hints);
    void setDifficulty(float difficulty);
    void setTerrain(float terrain);
    void setOwnerID(int owner_id);
    void setWaypoint(int waypoint);
    QString getName();
    QString getPlacedBy();
    QString getOwnerGUID();
    QString getOwnerName();
    QString getType();
    QString getContainer();
    QString getCountry();
    QString getState();
    QString getShortDescription();
    bool getShortDescriptionHTML();
    QString getLongDescription();
    bool getLongDescriptionHTML();
    QString getEncodedHints();
    float getDifficulty();
    float getTerrain();
    int getOwnerID();
protected:
    void loadValues(QSqlQuery query, bool loadID=false);
private:
    QString _name;
    QString _placed_by;
    QString _owner_guid;
    QString _owner_name;
    QString _type;
    QString _container;
    QString _country;
    QString _state;
    QString _short_description;
    QString _long_description;
    QString _encoded_hints;
    float _difficulty;
    float _terrain;
    int _owner_id;
    int _fk_waypoint;
    bool _long_description_html;
    bool _short_description_html;

signals:

public slots:

};

#endif // CACHE_H
