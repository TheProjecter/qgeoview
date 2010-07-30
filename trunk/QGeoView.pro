include(QMapControl/QMapControl.pri)
include(src/src.pro)
MOC_DIR = tmp
OBJECTS_DIR = obj
DESTDIR = bin
TARGET = QGeoView
DEPENDPATH += src \
    QMapControl/src
INCLUDEPATH += src \
    QMapControl/src
target.files = bin/*
unix {
    target.path = /usr/bin
}
win32 {
    target.path = c:\Program Files\$$TARGET
}
INSTALLS += target
