#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <QObject>
#include "databaseobject.h"
class Description : public DatabaseObject
{
    Q_OBJECT
public:
    explicit Description(QObject *parent = 0);

signals:

public slots:
private:
    QString _name;
    QString _link_url;
    QString _link_name;
    QString _comments;
    QString _source;
    QString _type;
};

#endif // DESCRIPTION_H
