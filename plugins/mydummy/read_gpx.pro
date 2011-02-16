QT             += xml \
                  sql
TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += . \
                  ../../QGeoView
HEADERS        += read_gpx.h
SOURCES        += read_gpx.cpp
TARGET          = $$qtLibraryTarget(readgpxpluginfactory)
DESTDIR         = ../bin
