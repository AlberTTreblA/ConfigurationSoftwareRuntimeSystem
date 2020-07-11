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
    w_heighth_thread.cpp \
    water_subwidget.cpp \
    waterpump_painter.cpp

HEADERS  += widget.h   \
    mytcpclient.h \
    global.h \
    addmastersdialog.h \
    w_heighth_thread.h \
    water_subwidget.h \
    waterpump_painter.h

FORMS    += widget.ui \
    addmastersdialog.ui
CONFIG +=c++11

RESOURCES += \
    images.qrc

DISTFILES +=
