#pragma once

#include "ui_pluginA.h"
#include <QtPlugin>
#include "../TTTT/interfaceplugin.h"
namespace Ui {
class PluginA;
}

class PluginA :public QWidget, public InterfacePlugin
{
    // programmer.json �������Ϣ������
    Q_OBJECT
    Q_PLUGIN_METADATA(IID InterfacePlugin_iid FILE "programmer.json")
    Q_INTERFACES(InterfacePlugin)
public:
    explicit PluginA(QWidget *parent = nullptr);
    virtual  void recMsgfromManager(PluginMetaData)  Q_DECL_OVERRIDE;
    virtual void bindVar(QMap<int, QVector<QString>>&)  Q_DECL_OVERRIDE;

public slots:
    void clickOpenImg();
    void click2Animation();
signals:
    // �źŷ����� moc �����
    void sendMsg2Manager(PluginMetaData) Q_DECL_OVERRIDE;
private:
    Ui::PluginA *ui;
};

