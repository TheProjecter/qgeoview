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
