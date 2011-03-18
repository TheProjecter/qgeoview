#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <QObject>
#include "databaseobject.h"

#define NULLMASK_DESCRIPTION_NAME       0x1
#define NULLMASK_DESCRIPTION_LINKURL    0x2
#define NULLMASK_DESCRIPTION_LINKNAME   0x4
#define NULLMASK_DESCRIPTION_COMMENTS   0x8
#define NULLMASK_DESCRIPTION_SOURCE     0x10
#define NULLMASK_DESCRIPTION_TYPE       0x20

class Description : public DatabaseObject
{
    Q_OBJECT
public:
    Description(QSqlDatabase *db, int id=0);
    Description(QSqlDatabase *db, QSqlQuery query);
    Description(const Description &original);
    void addBindValues(QSqlQuery query);
    void setQStringValue(int mask, QString value);
    QString getQStringValue(int mask);
    QString table();
    QStringList fields();
    static QStringList fieldNames();
protected:
    void loadValues(QSqlQuery query, bool loadID=false);
private:
    QString _name;
    QString _link_url;
    QString _link_name;
    QString _comments;
    QString _source;
    QString _type;
};

#endif // DESCRIPTION_H
