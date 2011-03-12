#ifndef LOG_H
#define LOG_H

#include <QObject>
#include "databaseobject.h"
#include "db/cache.h"

#define NULLMASK_LOG_LOGID          0x1
#define NULLMASK_LOG_LOGGUID        0x2
#define NULLMASK_LOG_DATE           0x3
#define NULLMASK_LOG_TYPE           0x4
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
    Log(Database *db, int id=0);
    Log(const Log &original);
    void addBindValues(QSqlQuery query);
    void setQStringValue(int mask, QString value);
    void setFloatValue(int mask, float value);
    void setIntValue(int mask, int value);
    void setBoolValue(int mask, bool value);
    QString getQStringValue(int mask);
    float getFloatValue(int mask);
    int getIntValue(int mask);
    bool getBoolValue(int mask);
    QString table();
protected:
    QStringList fields();
private:
    QString _log_guid;
    QString _date;
    QString _type;
    QString _finder_guid;
    QString _finder_name;
    QString _text;
    float _latitude;
    float _longitude;
    int _log_id;
    int _finder_id;
    int _cache;
    bool _text_encoded;
};

#endif // LOG_H
