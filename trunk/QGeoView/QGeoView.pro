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
HEADERS        += interfaces.h \
                  mainwindow.h \
                  treeitem.h \
                  treemodel.h \
                  db/accuracy.h \
                  db/collection.h \
                  db/database.h \
                  db/databaseobject.h \
                  db/description.h \
                  db/log.h \
                  db/point.h \
                  db/waypoint.h
FORMS          += mainwindow.ui
SOURCES        += main.cpp \
                  mainwindow.cpp \
                  treeitem.cpp \
                  treemodel.cpp \
                  db/accuracy.cpp \
                  db/collection.cpp \
                  db/database.cpp \
                  db/databaseobject.cpp \
                  db/description.cpp \
                  db/log.cpp \
                  db/point.cpp \
                  db/waypoint.cpp
RESOURCES      += QGeoView.qrc
