#-------------------------------------------------
#
# Project created by QtCreator 2017-08-01T14:55:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

INCLUDEPATH += "/usr/local/mysql/include"
LIBS += "/usr/local/mysql/lib/libmysqlclient.a"

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
