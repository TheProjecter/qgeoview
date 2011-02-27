QT             += xml \
                  sql
TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += . \
                  ../../QGeoView
HEADERS        += read_gpx.h \
                  ../../QGeoView/db/database.h \
                  ../../QGeoView/readplugin.h
SOURCES        += read_gpx.cpp \
                  ../../QGeoView/db/database.cpp \
                  ../../QGeoView/readplugin.cpp
TARGET          = $$qtLibraryTarget(readgpxpluginfactory)
DESTDIR         = ../bin
