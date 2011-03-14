#ifndef COLLECTION_H
#define COLLECTION_H

#include <QSqlQuery>
#include <QObject>
#include "databaseobject.h"


#define NULLMASK_COLLECTION_NAME        0x1
#define NULLMASK_COLLECTION_DESCRIPTION 0x2

class Collection : public DatabaseObject
{
    Q_OBJECT
public:
    Collection(Database *db, int id=0);
    Collection(Database *db, QSqlQuery query);
    Collection(const Collection &original);
    void addBindValues(QSqlQuery query);
    void setQStringValue(int mask, QString value);
    QString getQStringValue(int mask);
    QString summary();
    QString table();
    QStringList fields();
    static QStringList fieldNames();
protected:
    void loadValues(QSqlQuery query, bool loadID=false);
private:
    QString _name;
    QString _description;
};

#endif // COLLECTION_H
