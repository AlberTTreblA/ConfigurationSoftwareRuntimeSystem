TEMPLATE        = lib       #��ʾ���makefile��һ��lib��makefile��Ӧ�ó�����Ϊapp
CONFIG         += plugin    #Ӧ�ó�����һ�����
QT             += widgets
QT             += core gui
TARGET          = pluginD  #���ɲ��������
DESTDIR         = ../plugins/ #���ɲ����Ŀ¼


FORMS += \
    plugind.ui

HEADERS += \
    plugind.h

SOURCES += \
    plugind.cpp

DISTFILES += \
    programmer.json
