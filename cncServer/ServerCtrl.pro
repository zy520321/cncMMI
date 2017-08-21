#-------------------------------------------------
#
# Project created by QtCreator 2017-04-12T11:29:42
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = ServerCtrl
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    serversocket.cpp \
    tcpclientsocket.cpp \
    serverthreadctrl.cpp \
    systemdatamanager.cpp \
    onlinecmdexcut.cpp \
    plcmainctrl.cpp \
    interpolation.cpp \
    ncprogpreprocess.cpp \
    tcpfilesocket.cpp \
    tcpcmdsocket.cpp \
    strbuf.cpp \
    interpsegdata.cpp \
    alarm.cpp \
    protocol/analyzeEncapsulate.cpp

HEADERS += \
    serversocket.h \
    tcpclientsocket.h \
    serverthreadctrl.h \
    systemdatamanager.h \
    onlinecmdexcut.h \
    plcmainctrl.h \
    interpolation.h \
    DefSysSignalAndData.h \
    ncprogpreprocess.h \
    tcpfilesocket.h \
    tcpcmdsocket.h \
    strbuf.h \
    interpsegdata.h \
    alarm.h \
    protocol/analyzeEncapsulate.h
