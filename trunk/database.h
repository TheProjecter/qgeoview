#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QDomDocument>
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
    explicit Database(QString location, QTreeView *list, QObject *parent = 0);
    void import_gpx(QFile *file);
    void export_gpx(QFile *file, int collection_id);
    void populate(int collection_id=-1);
    ~Database();
private:
    QVariant child_value(QDomNodeList list, int format);
    QSqlDatabase _db;
    QTreeView *_tree;

signals:

public slots:

};

#endif // DATABASE_H
