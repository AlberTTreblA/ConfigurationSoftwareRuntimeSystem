#-------------------------------------------------
#
# Project created by QtCreator 2019-08-4T10:04:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test2
TEMPLATE = app


SOURCES += main.cpp    widget.cpp   \
    global.cpp\
    myserver.cpp \
    mytcpsocket.cpp

HEADERS  += widget.h   \
    myserver.h \
    mytcpsocket.h \
    global.h

FORMS    += widget.ui
CONFIG +=c++11

RESOURCES += \
    images.qrc

DISTFILES +=
