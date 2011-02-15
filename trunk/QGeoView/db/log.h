#ifndef LOG_H
#define LOG_H

#include <QObject>
#include "databaseobject.h"

class Log : public DatabaseObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = 0);

signals:

public slots:
private:
    long _log_guid;
    QString date;
    QString type;
    long _finder_id;
    QString _finder_guid;
    QString _finder_name;
    QString _text;
    bool _text_encoded;
    float _latitude;
    float _longitude;
};

#endif // LOG_H
