#include "myapplication.h"
#include "exceptions.h"
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
    catch (QGeoViewException e) {
        std::cerr << "Caught " << e.name().toStdString() << ": " << e.error().toStdString() << std::endl;
        return false;
    }
    catch (char const *str) {
        std::cerr << "EXCEPTION: " << str << std::endl;
        return false;
    }
    catch (...) {
        std::cerr << "\t\t\tUnknown Exception!" << std::endl;
    }
    return true;
}

