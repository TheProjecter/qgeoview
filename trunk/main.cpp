#include <QtGui/QApplication>
#include <QObject>
#include "mainwindow.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.connect(&w, SIGNAL(quit()), &a, SLOT(quit()));
    return a.exec();
}
