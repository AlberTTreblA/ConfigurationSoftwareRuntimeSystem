#pragma once

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QString>
/**
 * �������Ϣ��װ��
 **/
struct PluginMetaData
{
    QString from;
    QString dest;
    int type;
    QMap<QString,QVariant> map;
    QObject *object = nullptr;
};
Q_DECLARE_METATYPE(PluginMetaData);

