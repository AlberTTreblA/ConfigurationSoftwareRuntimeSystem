#ifndef PLUGIND_H
#define PLUGIND_H

#include "ui_plugind.h"
#include <QtPlugin>
#include "../TTTT/interfaceplugin.h"

namespace Ui {
class pluginD;
}

class pluginD :public QWidget, public InterfacePlugin
{
    // programmer.json �������Ϣ������
    Q_OBJECT
    Q_PLUGIN_METADATA(IID InterfacePlugin_iid FILE "programmer.json")
    Q_INTERFACES(InterfacePlugin)
public:
    explicit pluginD(QWidget *parent = nullptr);
    ~pluginD();
    virtual  void recMsgfromManager(PluginMetaData)  Q_DECL_OVERRIDE;
    virtual void bindVar(QMap<int, QVector<QString>>&)  Q_DECL_OVERRIDE;

public slots:
    void updateValueForRotation();
    void updateValueForPower();

signals:
    // �źŷ����� moc �����
    void sendMsg2Manager(PluginMetaData) Q_DECL_OVERRIDE;
private:
    Ui::pluginD *ui;
    QMap<int, QVector<QString>*> var;
    QTimer* rTimer;
    QTimer* pTimer;
};

#endif // PLUGIND_H
