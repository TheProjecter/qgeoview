#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QObject>
#include <QFile>
#include <QTreeView>

#define DATABASE_DATATYPE_STRING	0
#define DATABASE_DATATYPE_INT		1
#define DATABASE_DATATYPE_DOUBLE	2

class Database : public QObject
{
Q_OBJECT
public:
    explicit Database(QString location, QTreeView *list, QObject *parent=NULL);
    void transaction();
    void commit();
    ~Database();
private:
    QSqlDatabase _db;
    QTreeView *_tree;

signals:

public slots:

};

#endif // DATABASE_H
