#ifndef COLLECTION_H
#define COLLECTION_H

#include <QObject>
#include "databaseobject.h"
#include "db/exceptions.h"


#define NULLMASK_COLLECTION_NAME        0x1
#define NULLMASK_COLLECTION_DESCRIPTION 0x2

class Collection : public DatabaseObject
{
    Q_OBJECT
public:
    Collection(Database *db, int id=0);
    Collection(const Collection &original);
    void addBindValues(QSqlQuery query);
    void setQStringValue(int mask, QString value);
    QString getQStringValue(int mask);
    QString table();
protected:
    QStringList fields();
    void loadValues(QSqlQuery query);
private:
    QString _name;
    QString _description;
};

#endif // COLLECTION_H
