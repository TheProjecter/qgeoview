#ifndef LOG_H
#define LOG_H

#include <QObject>
#include "databaseobject.h"
#include "db/cache.h"

//  NULLMASK_ID is set in db/databaseobject.h and is 0x1 DO NOT USE 0x1 HERE!!!
#define NULLMASK_LOG_LOGGUID        0x2
#define NULLMASK_LOG_DATE           0x4
#define NULLMASK_LOG_TYPE           0x8
#define NULLMASK_LOG_FINDERID       0x10
#define NULLMASK_LOG_FINDERGUID     0x20
#define NULLMASK_LOG_FINDERNAME     0x40
#define NULLMASK_LOG_TEXT           0x80
#define NULLMASK_LOG_TEXTENCODED    0x100
#define NULLMASK_LOG_LATITUDE       0x200
#define NULLMASK_LOG_LONGITUDE      0x400
#define NULLMASK_LOG_CACHE          0x800

class Log : public DatabaseObject
{
    Q_OBJECT
public:
    Log(Database *db);
    ~Log();
    void addBindValues(QSqlQuery query);
    void setQStringValue(int mask, QString value);
    void setFloatValue(int mask, float value);
    void setIntValue(int mask, int value);
    void setBoolValue(int mask, bool value);
    QString getQStringValue(int mask);
    float getFloatValue(int mask);
    int getIntValue(int mask);
    bool getBoolValue(int mask);
protected:
    QStringList fields();
private:
    QString table();
    int _log_guid;
    QString _date;
    QString _type;
    int _finder_id;
    QString _finder_guid;
    QString _finder_name;
    QString _text;
    bool _text_encoded;
    float _latitude;
    float _longitude;
    int _cache;
    Cache *_cache_object;
};

#endif // LOG_H
