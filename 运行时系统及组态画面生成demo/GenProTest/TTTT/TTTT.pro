#-------------------------------------------------
#
# Project created by QtCreator 2019-05-23T16:06:07
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app

INCLUDEPATH += $$PWD/..

debug:DESTDIR = ../debug/
release:DESTDIR = ../release/

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11   # foreach 循环，lambda等，指定�console 在运行时会导致插件无法创建GUI

SOURCES += \
    main.cpp \
    widget.cpp \
    qtpluginmanager.cpp \
    qtpluginsmanagerprivate.cpp \
    global.cpp \
    mytcpclient.cpp \
    datacommunication.cpp \
    datasave.cpp \
    simulator.cpp

HEADERS += \
    widget.h \
    interfaceplugin.h \
    qtpluginmanager.h \
    qtpluginsmanagerprivate.h \
    pluginMetaData.h \
    global.h \
    mytcpclient.h \
    datacommunication.h \
    datasave.h \
    simulator.h

FORMS += \
        widget.ui

LIBS += -LD:/pinusdb_1.3.1/CSDK -lpdb_csdk

INCLUDEPATH += D:/pinusdb_1.3.1/CSDK

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    dataSave.json
