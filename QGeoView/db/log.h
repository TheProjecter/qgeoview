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
    Log(QSqlDatabase *db, int id=0);
    Log(QSqlDatabase *db, QSqlQuery query);
    void addBindValues(QSqlQuery query);
    QString table();
    static QString tableName();
    QStringList fields();
    static QStringList fieldNames();
    QString summary();
    void setLogGUID(QString log_guid);
    void setDate(QString date);
    void setType(QString type);
    void setFinderGUID(QString finder_guid);
    void setFinderName(QString finder_name);
    void setText(QString text, bool encoded=false);
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    void setLogID(int log_id);
    void setFinderID(int finder_id);
    void setCache(int cache);
    QString getLogGUID();
    QString getDate();
    QString getType();
    QString getFinderGUID();
    QString getFinderName();
    QString getText();
    bool getTextEncoded();
    float getLatitude();
    float getLongitude();
    int getLogID();
    int getFinderID();
    int getCache();
protected:
    void loadValues(QSqlQuery query, bool loadID=false);
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
    int _fk_cache;
    bool _text_encoded;
};

#endif // LOG_H
