#include "myapplication.h"
#include "db/exceptions.h"
#include <iostream>


MyApplication::MyApplication(int argc, char *argv[]) :
    QApplication(argc, argv)
{
}

bool MyApplication::notify(QObject *rec, QEvent *ev)
{
    try {
        return QApplication::notify(rec, ev);
    }
    catch (char const *str) {
        std::cerr << "EXCEPTION: " << str << std::endl;
        return false;
    }
    catch (NoDatabaseFoundException e) {
        std::cerr << "Exception: No Database found at " << e.location().toStdString() << std::endl;
        return false;
    }
    catch (MaskNotFoundException e) {
        std::cerr << "Exception: " << e.object()->table().toStdString() << "::" << e.mask() << " Not found for type " << e.datatype().toStdString() << std::endl;
        return false;
    }
    catch (DBValueNotSetException e) {
        std::cerr << "Exception: " << e.object()->table().toStdString() << ".id(" << e.object()->getID() << ") " << e.datatype().toStdString() << "(" << e.mask() << ") is NULL" << std::endl;
        return false;
    }
    catch (IDNotSetException e) {
        std::cerr << "Exception: ID for " << e.object()->table().toStdString() << " has no ID" << std::endl;
        return false;
    }
    catch (IDAlreadySetException e) {
        std::cerr << "Exception: Tried to set " << e.object()->table().toStdString() << ".id(" << e.object()->getID() << ") to " << e.id() << std::endl;
        return false;
    }
    catch (NotInDatabaseException e) {
        std::cerr << "Exception: Tried deleting " << e.object()->table().toStdString() << ", but it isn't in the database!" << std::endl;
        return false;
    }
    catch (DBException e) {
        std::cerr << "unknown DBException " << std::endl;
        return false;
    }
    catch (...) {
        std::cerr << "\t\t\tUnknown Exception!" << std::endl;
    }
    return true;
}

