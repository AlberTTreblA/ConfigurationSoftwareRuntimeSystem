TEMPLATE        = lib       #表示这个makefile是一个lib的makefile，应用程序则为app
CONFIG         += plugin    #应用程序是一个插件
QT             += widgets
QT             += core gui
TARGET          = pluginD  #生成插件的名称
DESTDIR         = ../plugins/ #生成插件的目录


FORMS += \
    plugind.ui

HEADERS += \
    plugind.h

SOURCES += \
    plugind.cpp

DISTFILES += \
    programmer.json
