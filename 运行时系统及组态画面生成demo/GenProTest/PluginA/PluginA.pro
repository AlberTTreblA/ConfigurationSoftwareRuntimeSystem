TEMPLATE        = lib       #��ʾ���makefile��һ��lib��makefile��Ӧ�ó�����Ϊapp
CONFIG         += plugin    #Ӧ�ó�����һ�����
QT             += widgets
QT             += core gui
TARGET          = pluginA  #���ɲ��������
DESTDIR         = ../plugins/ #���ɲ����Ŀ¼

HEADERS += \
    pluginA.h

SOURCES += \
    pluginA.cpp

FORMS += \
    pluginA.ui

DISTFILES += \
    programmer.json

