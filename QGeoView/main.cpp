/******************************************************************************
** Copyright 2010 Doug Penner
**
** This file is part of QGeoView.
**
** QGeoView is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QGeoView is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QGeoView.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


#include <QtGui/QApplication>
#include <QObject>
#include "mainwindow.h"
#include <QMessageBox>
#include "myapplication.h"

#include <iostream>

/*
 Initializes the application.
*/
int main(int argc, char *argv[])
{
    MyApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.connect(&w, SIGNAL(quit()), &a, SLOT(quit()));
    std::cout << "test" << std::endl;
    return a.exec();
}
