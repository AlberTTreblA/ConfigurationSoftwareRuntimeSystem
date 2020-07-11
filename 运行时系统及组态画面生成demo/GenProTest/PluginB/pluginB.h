#pragma once

#include <QObject>
#include <QWidget>
#include <QtPlugin>
#include "../TTTT/interfaceplugin.h"

class PluginB : public QObject, public InterfacePlugin
{
    // programmer.json 插件的信息描述类
    Q_OBJECT
    Q_PLUGIN_METADATA(IID InterfacePlugin_iid FILE "programmer.json")
    Q_INTERFACES(InterfacePlugin)
public:
    explicit PluginB(QObject *parent = 0);
    virtual  void recMsgfromManager(PluginMetaData)  Q_DECL_OVERRIDE;
    virtual void bindVar(QMap<int, QVector<QString>>&)  Q_DECL_OVERRIDE;

signals:
    void sendMsg2Manager(PluginMetaData) Q_DECL_OVERRIDE;
public slots:
     void animation(QWidget*);
};

