#-------------------------------------------------
#
# Project created by QtCreator 2017-08-01T14:48:54
#
#-------------------------------------------------

QT       -= gui

TARGET = mySqlPlugin
TEMPLATE = lib

DEFINES += MYSQLPLUGIN_LIBRARY

SOURCES += mySqlPlugin.cpp

HEADERS += mySqlPlugin.h\
        mysqlplugin_global.h \
    mySqlInterface.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
