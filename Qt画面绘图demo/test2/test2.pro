#-------------------------------------------------
#
# Project created by QtCreator 2019-05-25T10:04:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test2
TEMPLATE = app


SOURCES += main.cpp    widget.cpp    waterpump_painter.cpp\
    global.cpp\
    conderser_painter.cpp\
    gen_painter.cpp\
    w_heighth_thread.cpp\
    w_consumption_thread.cpp\
    water_subwidget.cpp\
    w_height_watcher.cpp\
    w_consumption_watcher.cpp\
    gen_capacity_thread.cpp\
    gen_temperature_thread.cpp\
    gen_subwidget.cpp\
    tur_consumption_thread.cpp\
    tur_rotation_thread.cpp\
    turbine_subwidget.cpp\
    tur_painter.cpp\
    tur_consumption_watcher.cpp\
    tur_rotation_watcher.cpp\
    gen_capacity_watcher.cpp\
    gen_temperature_watcher.cpp \
    curvechart.cpp \
    roundplot.cpp \
    lednumber.cpp \
    barruler.cpp \
    myserver.cpp \
    mytcpsocket.cpp \
    hled.cpp \
    addcontrollersdialog.cpp \
    mytcpclient.cpp

HEADERS  += widget.h    waterpump_painter.h\
    global.h\
    conderser_painter.h\
    gen_painter.h\
    w_heighth_thread.h\
    w_consumption_thread.h\
    water_subwidget.h\
    w_height_watcher.h\
    w_consumption_watcher.h\
    gen_capacity_thread.h\
    gen_temperature_thread.h\
    gen_subwidget.h\
    tur_consumption_thread.h\
    tur_rotation_thread.h\
    turbine_subwidget.h\
    tur_painter.h\
    tur_consumption_watcher.h\
    tur_rotation_watcher.h\
    gen_capacity_watcher.h\
    gen_temperature_watcher.h \
    curvechart.h \
    curvechart.h \
    roundplot.h \
    lednumber.h \
    barruler.h \
    myserver.h \
    mytcpsocket.h \
    hled.h \
    addcontrollersdialog.h \
    mytcpclient.h

FORMS    += widget.ui \
    addcontrollersdialog.ui
CONFIG +=c++11

RESOURCES += \
    images.qrc

DISTFILES +=
