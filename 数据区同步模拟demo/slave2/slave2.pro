#-------------------------------------------------
#
# Project created by QtCreator 2019-05-25T10:04:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test2
TEMPLATE = app


SOURCES += main.cpp    widget.cpp   \
    global.cpp\
    mytcpclient.cpp \
    addmastersdialog.cpp \
    tur_rotation_thread.cpp

HEADERS  += widget.h   \
    mytcpclient.h \
    global.h \
    addmastersdialog.h \
    tur_rotation_thread.h

FORMS    += widget.ui \
    addmastersdialog.ui
CONFIG +=c++11

RESOURCES += \
    images.qrc

DISTFILES +=
