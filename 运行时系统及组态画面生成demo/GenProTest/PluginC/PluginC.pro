TEMPLATE=lib
CONFIG+= plugin
QT+= widgets
QT+= core gui qml
TARGET=pluginC
DESTDIR=../plugins
HEADERS+=pluginc.h
SOURCES+=pluginc.cpp
DISTFILES+=programmer.json
INCLUDEPATH+="D:/QtPrimitiveLib/"
LIBS+="D:/QtPrimitiveLib/Alarm.lib"\
"D:/QtPrimitiveLib/Label.lib"\
"D:/QtPrimitiveLib/Line.lib"\
