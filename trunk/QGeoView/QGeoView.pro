QT             += sql
TEMPLATE        = app
MOC_DIR         = tmp
OBJECTS_DIR     = obj
DESTDIR         = bin
TARGET          = 
DEPENDPATH     += . \
                  db
INCLUDEPATH    += . \
                  db
target.files = bin/*
unix:target.path = /usr/bin
win32:target.path = c:\Program\ Files\$$TARGET
INSTALLS       += target
HEADERS        += mainwindow.h \
                  treeitem.h \
                  treemodel.h \
                  db/collection.h \
                  db/database.h \
                  db/databaseobject.h \
                  db/description.h \
                  db/log.h \
                  db/point.h \
                  db/waypoint.h \
                  readplugin.h \
                  dummyplugin.h \
                  db/exceptions.h \
                  db/cache.h \
                  myapplication.h
FORMS          += mainwindow.ui
SOURCES        += main.cpp \
                  mainwindow.cpp \
                  treeitem.cpp \
                  treemodel.cpp \
                  db/collection.cpp \
                  db/database.cpp \
                  db/databaseobject.cpp \
                  db/description.cpp \
                  db/log.cpp \
                  db/point.cpp \
                  db/waypoint.cpp \
                  readplugin.cpp \
                  dummyplugin.cpp \
                  db/cache.cpp \
                  myapplication.cpp
RESOURCES      += QGeoView.qrc