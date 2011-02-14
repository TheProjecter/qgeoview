QT += xml \
    webkit \
    sql
TEMPLATE = app
MOC_DIR = tmp
OBJECTS_DIR = obj
DESTDIR = bin
TARGET = QGeoView
DEPENDPATH += .
INCLUDEPATH += .
target.files = bin/*
unix:target.path = /usr/bin
win32:target.path = c:\Program\ Files\$$TARGET
INSTALLS += target
HEADERS += mainwindow.h \
    treeitem.h \
    treemodel.h \
    database.h \
    point.h \
    accuracy.h \
    log.h \
    waypoint.h \
    description.h \
    databaseobject.h \
    collection.h
FORMS += mainwindow.ui
SOURCES += main.cpp \
    mainwindow.cpp \
    treeitem.cpp \
    treemodel.cpp \
    database.cpp \
    point.cpp \
    accuracy.cpp \
    log.cpp \
    waypoint.cpp \
    description.cpp \
    databaseobject.cpp \
    collection.cpp
RESOURCES += QGeoView.qrc
LIBS += -lmarblewidget
INCLUDEPATH += /usr/include/marble
