#pragma once

#include <QObject>
#include <QPluginLoader>
#include <QVariant>
#include "qtpluginsmanagerprivate.h"
#include "pluginMetaData.h"
#include <QDir>

class  QtPluginsManager : public QObject
{
    Q_OBJECT

public:
    static QtPluginsManager &getInstance()
    {
        static QtPluginsManager m_instance;
        return m_instance;
    }
public:
    QDir getPluginPath();
    //加载所有插件
    void loadAllPlugins();
    //扫描JSON文件中的插件元数据
    void scan(const QString &filepath);
    //加载其中某个插件
    void loadPlugin(const QString &filepath);
    //卸载所有插件
    void unloadAllPlugins();
    //卸载某个插件
    void unloadPlugin(const QString &filepath);
    //获取所有插件
    QList<QPluginLoader *> allPlugins();
    //获取某个插件(by name)
    QPluginLoader* getPlugin(const QString &name);
    //获取某组插件(by type)
    QList<QPluginLoader *> getPluginsByType(const QVariant&);
    //初始化和插件通信的信号槽
    void initSignalAndSlot();

    //为所有插件绑定var
    void bindVarForAllPlugins(QMap<int, QVector<QString>>&);

public slots:
    //接受来自各插件的消息
    void recMsgfromPlugin(PluginMetaData);
private:
    QtPluginsManager()
    {
     d = new QtPluginsManagerPrivate;
    };
    QtPluginsManagerPrivate *d;
};

