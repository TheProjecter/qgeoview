QT             += xml \
                  sql
TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += . \
                  ../../QGeoView
HEADERS        += mydummy.h
SOURCES        += mydummy.cpp
TARGET          = $$qtLibraryTarget(mydummypluginfactory)
DESTDIR         = ../bin
