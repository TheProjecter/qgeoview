TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ../../QGeoView
HEADERS        += ../../QGeoView/database.h
SOURCES        += ../../QGeoView/database.cpp
TARGET          = $$qtLibraryTarget(marblemapplugin)
DESTDIR         = ../bin
