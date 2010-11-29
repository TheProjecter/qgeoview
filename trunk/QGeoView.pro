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
    itemstreewidget.h \
    treeitem.h \
    treemodel.h \
    database.h \
    newitemdialog.h
FORMS += mainwindow.ui \
    newitemdialog.ui \
    ItemDescription.ui \
    ItemLocation.ui \
    PointAccuracy.ui
SOURCES += main.cpp \
    mainwindow.cpp \
    itemstreewidget.cpp \
    treeitem.cpp \
    treemodel.cpp \
    database.cpp \
    newitemdialog.cpp
RESOURCES += QGeoView.qrc
LIBS += -lmarblewidget
INCLUDEPATH += /usr/include/marble
