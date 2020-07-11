#ifndef PLUGINC_H
#define PLUGINC_H
#include <QtPlugin>
#include <QMap>
#include "D:/Qt5.9.0test/GenProTest/QtPluginDemo-master/TTTT/interfaceplugin.h"
#include "alarm.h"
#include "label.h"
#include "line.h"
class PluginC :public QWidget, public InterfacePlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID InterfacePlugin_iid FILE "programmer.json")
Q_INTERFACES(InterfacePlugin)
signals:
void sendMsg2Manager(PluginMetaData) Q_DECL_OVERRIDE;
public:
explicit PluginC(QWidget *parent = nullptr);
virtual  void recMsgfromManager(PluginMetaData)  Q_DECL_OVERRIDE;
virtual void bindVar(QMap<int, QVector<QString>>&)  Q_DECL_OVERRIDE;
private:
QMap<int, QVector<QString>*> var;
Alarm *alarm0;
Label *label0;
Line *line0;
};
#endif
