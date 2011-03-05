#ifndef COLLECTION_H
#define COLLECTION_H

#include <QObject>
#include "databaseobject.h"
#include "db/exceptions.h"


// NULLMASK_ID is set in db/databaseobject.h and is 0x1 DO NOT USE 0x1 HERE!!!
#define NULLMASK_COLLECTION_NAME        0x2
#define NULLMASK_COLLECTION_DESCRIPTION 0x4

class Collection : public DatabaseObject
{
    Q_OBJECT
public:
    Collection(Database *db);
    ~Collection();
    void addBindValues(QSqlQuery query);
    void setQStringValue(int mask, QString value);
    QString getQStringValue(int mask);
protected:
    QStringList fields();
private:
    QString table();
    QString _name;
    QString _description;
};

#endif // COLLECTION_H
