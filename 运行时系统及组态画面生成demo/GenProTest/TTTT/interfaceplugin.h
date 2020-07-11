#pragma once

#include <QString>
#include <QtPlugin>
#include <QObject>
#include "pluginMetaData.h"
//定义接口
class InterfacePlugin
{

public:
    virtual ~InterfacePlugin() {}
    virtual void recMsgfromManager(PluginMetaData) = 0;
    virtual void sendMsg2Manager(PluginMetaData)   = 0;
    virtual void bindVar(QMap<int, QVector<QString>>&) = 0;
};


#define InterfacePlugin_iid "Test.Plugin.InterfacePlugin"

Q_DECLARE_INTERFACE(InterfacePlugin, InterfacePlugin_iid)

