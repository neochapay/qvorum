QT += core network sql
QT -= gui

CONFIG += c++11

CONFIG   += console
CONFIG   -= app_bundle

TARGET = qvorum

include(src.pri)

TEMPLATE = app

INCLUDEPATH = ../qtwebserver

SOURCES += main.cpp \
    dbadapter.cpp \
    controllers/usercontroller.cpp \
    pages/notfoundpage.cpp \
    models/user.cpp

DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    dbadapter.h \
    controllers/usercontroller.h \
    pages/notfoundpage.h \
    models/user.h
