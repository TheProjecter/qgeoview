#include <iostream>
#include "writeplugin.h"

WritePlugin::WritePlugin(QSqlDatabase *db) :
        _db(db)
{
}
