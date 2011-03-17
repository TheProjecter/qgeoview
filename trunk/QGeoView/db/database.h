#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QObject>
#include <QFile>
#include <QTreeView>

#define INFO_TYPE_NONE      1
#define INFO_TYPE_CACHE     2
#define INFO_TYPE_WAYPOINT  3
#define INFO_TYPE_ROUTE     4
#define INFO_TYPE_TRACK     5

#define DATABASE_DATATYPE_STRING	0
#define DATABASE_DATATYPE_INT		1
#define DATABASE_DATATYPE_DOUBLE	2

class Database : public QObject
{
Q_OBJECT
public:
    explicit Database(QString location, QObject *parent=NULL);
    void transaction();
    void commit();
    ~Database();
private:
    QSqlDatabase _db;

signals:

public slots:

};

#endif // DATABASE_H
