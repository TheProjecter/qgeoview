QT             += sql
TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += . \
                  ../../QGeoView \
                  ../../QGeoView/db
HEADERS        += details_tab.h \
                  ../../QGeoView/tabplugin.h \
                  ../../QGeoView/exceptions.h \
                  ../../QGeoView/mainwindow.h \
                  ../../QGeoView/db/point.h \
                  ../../QGeoView/db/cache.h \
                  ../../QGeoView/db/collection.h \
                  ../../QGeoView/db/description.h \
                  ../../QGeoView/db/log.h \
                  ../../QGeoView/db/waypoint.h \
                  ../../QGeoView/db/databaseobject.h
SOURCES        += details_tab.cpp \
                  ../../QGeoView/tabplugin.cpp \
                  ../../QGeoView/mainwindow.cpp \
                  ../../QGeoView/db/point.cpp \
                  ../../QGeoView/db/cache.cpp \
                  ../../QGeoView/db/collection.cpp \
                  ../../QGeoView/db/description.cpp \
                  ../../QGeoView/db/log.cpp \
                  ../../QGeoView/db/waypoint.cpp \
                  ../../QGeoView/db/databaseobject.cpp
FORMS           += \
                  mainwidget.ui
TARGET          = $$qtLibraryTarget(detailstabpluginfactor)
DESTDIR         = ../bin
