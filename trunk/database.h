#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QDomDocument>
#include <QObject>
#include <QFile>

#define DATABASE_DATATYPE_STRING	0
#define DATABASE_DATATYPE_INT		1
#define DATABASE_DATATYPE_DOUBLE	2

typedef struct point_ {
    int id;
    QString time;
    float elevation;
    float magneticVariation;
    float geoIDHeight;
    QString symbol;
    QString fix;
    int satelites;
    float horizontalDOP;
    float verticalDOP;
    float positionDOP;
    float ageOfDGPSData;
    int DGPSID;
    float latitude;
    float longitude;
} Point;

typedef struct log_ {
    int id;
    long log_id;
    QString log_guid;
    QString date;
    QString type;
    long finder_id;
    QString finder_guid;
    QString finder_name;
    QString text;
    bool text_encoded;
    float latitude;
    float longitude;
    int cache;
} Log;

typedef struct cache_ {
    int id;
    QString name;
    QString placed_by;
    long owner_id;
    QString owner_guid;
    QString owner_name;
    QString type;
    QString container;
    float difficulty;
    float terrain;
    QString country;
    QString state;
    QString short_description;
    bool short_description_encoded;
    QString long_description;
    bool long_description_encoded;
    QString encoded_hints;
    int waypoint;
} Cache;

typedef struct waypoint_ {
    int id;
    int description;
    int point;
} Waypoint;

typedef struct description_ {
    int id;
    QString name;
    QString link_url;
    QString link_name;
    QString comments;
    QString source;
    QString type;
} Description;

class Database : public QObject
{
Q_OBJECT
public:
    explicit Database(QString location, QObject *parent = 0);
    void import_gpx(QFile *file);
    void export_gpx(QFile *file, int collection_id);
    ~Database();
private:
    QVariant child_value(QDomNodeList list, int format);
    QSqlDatabase _db;

signals:

public slots:

};

#endif // DATABASE_H
