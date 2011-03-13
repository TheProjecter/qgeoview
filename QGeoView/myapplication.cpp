#include "myapplication.h"
#include "exceptions.h"
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>


MyApplication::MyApplication(int argc, char *argv[]) :
    QApplication(argc, argv)
{
}

bool MyApplication::notify(QObject *rec, QEvent *ev)
{
    try {
        return QApplication::notify(rec, ev);
    }
    catch (QSqlQuery query) {
        QSqlError error = query.lastError();
        std::cerr << "Caught Query Error: " << std::endl;
        std::cerr << "\t Last Query:" << std::endl << "\t\t" << query.lastQuery().toStdString() << std::endl;
        std::cerr << "\t Executed Query:" << std::endl << "\t\t" << query.executedQuery().toStdString() << std::endl;
        std::cerr << "\tdriverText: " << error.driverText().toStdString() << std::endl;
        std::cerr << "\tdatabaseText: " << error.databaseText().toStdString() << std::endl;
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
        std::cerr << "Unknown Exception! FIX THIS!!!" << std::endl;
    }
    return true;
}

