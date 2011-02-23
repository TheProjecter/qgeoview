QT             += xml \
                  sql
TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += . \
                  ../../QGeoView
HEADERS        += mydummy.h \
               += ../../QGeoView/test_class.h
               += ../../QGeoView/dummyplugin.h
SOURCES        += mydummy.cpp \
                  ../../QGeoView/test_class.cpp \
                  ../../QGeoView/dummyplugin.cpp
TARGET          = $$qtLibraryTarget(mydummypluginfactory)
DESTDIR         = ../bin
