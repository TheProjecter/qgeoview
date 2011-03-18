#include <iostream>
#include "readplugin.h"

ReadPlugin::ReadPlugin(QSqlDatabase *db) :
    _db(db)
{
}
