#ifndef COLLECTION_H
#define COLLECTION_H

#include "databaseobject.h"

class Collection : public DatabaseObject
{
    Q_OBJECT
public:
    explicit Collection(QObject *parent = 0);

public slots:

};

#endif // COLLECTION_H