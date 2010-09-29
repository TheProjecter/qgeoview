#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QObject>

class Database : public QObject
{
Q_OBJECT
public:
    explicit Database(QString location, QObject *parent = 0);
    ~Database();
private:
    QSqlDatabase _db;

signals:

public slots:

};

#endif // DATABASE_H
