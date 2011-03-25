QT             += xml \
                  sql
TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += . \
                  ../../QGeoView \
                  ../../QGeoView/db
HEADERS        += read_groundspeakgpx.h \
                  ../../QGeoView/readplugin.h \
                  ../../QGeoView/db/point.h \
                  ../../QGeoView/db/cache.h \
                  ../../QGeoView/db/collection.h \
                  ../../QGeoView/db/description.h \
                  ../../QGeoView/exceptions.h \
                  ../../QGeoView/db/log.h \
                  ../../QGeoView/db/waypoint.h \
                  ../../QGeoView/db/databaseobject.h
SOURCES        += read_groundspeakgpx.cpp \
                  ../../QGeoView/readplugin.cpp \
                  ../../QGeoView/db/point.cpp \
                  ../../QGeoView/db/cache.cpp \
                  ../../QGeoView/db/collection.cpp \
                  ../../QGeoView/db/description.cpp \
                  ../../QGeoView/db/log.cpp \
                  ../../QGeoView/db/waypoint.cpp \
                  ../../QGeoView/db/databaseobject.cpp
TARGET          = $$qtLibraryTarget(readgroundspeakgpxpluginfactory)
DESTDIR         = ../bin
