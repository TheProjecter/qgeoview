#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <QObject>
#include "databaseobject.h"
#include "db/exceptions.h"

// NULLMASK_ID is set in db/databaseobject.h and is 0x1 DO NOT USE 0x1 HERE!!
#define NULLMASK_DESCRIPTION_NAME       0x2
#define NULLMASK_DESCRIPTION_LINKURL    0x4
#define NULLMASK_DESCRIPTION_LINKNAME   0x8
#define NULLMASK_DESCRIPTION_COMMENTS   0x10
#define NULLMASK_DESCRIPTION_SOURCE     0x20
#define NULLMASK_DESCRIPTION_TYPE       0x40

class Description : public DatabaseObject
{
    Q_OBJECT
public:
    Description(Database *db);
    ~Description();
    void addBindValues(QSqlQuery query);
    void setQStringValue(int mask, QString value);
    QString getQStringValue(int mask);

protected:
    QStringList fields();
private:
    QString table();
    QString _name;
    QString _link_url;
    QString _link_name;
    QString _comments;
    QString _source;
    QString _type;
};

#endif // DESCRIPTION_H
