TEMPLATE        = lib       #��ʾ���makefile��һ��lib��makefile��Ӧ�ó�����Ϊapp
CONFIG         += plugin    #Ӧ�ó�����һ�����
QT             += widgets
TARGET          = pluginB  #���ɲ��������
DESTDIR         = ../plugins/ #���ɲ����Ŀ¼

HEADERS += \
    pluginB.h

SOURCES += \
    pluginB.cpp

DISTFILES += \
    programmer.json
