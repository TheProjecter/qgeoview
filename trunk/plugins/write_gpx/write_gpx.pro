QT             += xml \
                  sql
TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += . \
                  ../../QGeoView \
                  ../../QGeoView/db
HEADERS        += write_gpx.h \
                  ../../QGeoView/writeplugin.h \
                  ../../QGeoView/db/point.h \
                  ../../QGeoView/db/cache.h \
                  ../../QGeoView/db/collection.h \
                  ../../QGeoView/db/description.h \
                  ../../QGeoView/exceptions.h \
                  ../../QGeoView/db/log.h \
                  ../../QGeoView/db/waypoint.h \
                  ../../QGeoView/db/databaseobject.h \
                  ../../QGeoView/db/database.h
SOURCES        += write_gpx.cpp \
                  ../../QGeoView/writeplugin.cpp \
                  ../../QGeoView/db/point.cpp \
                  ../../QGeoView/db/cache.cpp \
                  ../../QGeoView/db/collection.cpp \
                  ../../QGeoView/db/description.cpp \
                  ../../QGeoView/db/log.cpp \
                  ../../QGeoView/db/waypoint.cpp \
                  ../../QGeoView/db/databaseobject.cpp \
                  ../../QGeoView/db/database.cpp
TARGET          = $$qtLibraryTarget(writegpxpluginfactory)
DESTDIR         = ../bin
