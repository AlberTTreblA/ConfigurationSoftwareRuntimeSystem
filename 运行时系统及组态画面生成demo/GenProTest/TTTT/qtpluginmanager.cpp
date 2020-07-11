#include "qtpluginmanager.h"
#include <QFileInfo>
#include <QApplication>
#include <QJsonObject>
#include <QJsonArray>
#include"interfaceplugin.h"

// 加载所有插件
QDir QtPluginsManager::getPluginPath()
{
    // 进入插件目录
    QDir path = QDir(qApp->applicationDirPath());
    path.cd("../plugins");
    return path;
}

void QtPluginsManager::loadAllPlugins()
{
    // 进入插件目录
    QDir path = getPluginPath();

    // 初始化插件中的元数据
    foreach (QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
            scan(info.absoluteFilePath());
    }
    // 加载插件
    foreach (QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
            loadPlugin(info.absoluteFilePath());
    }
}


// 扫描 JSON 文件中的插件元数据
void QtPluginsManager::scan(const QString& path)
{
    /*****
     *  判断是否是库（后缀有效性）
     * Windows：.dll、.DLL
     * Unix/Linux：.so
   *****/

    if (!QLibrary::isLibrary(path))
        return;

    // 获取元数据（名称、版本、依赖）
    QPluginLoader *loader = new QPluginLoader(path);
    QJsonObject json = loader->metaData().value("MetaData").toObject();

    d->m_names.insert(path, json.value("name").toVariant());
    d->m_versions.insert(path, json.value("version").toVariant());
    d->m_types.insert(path, json.value("type").toVariant());
    d->m_dependencies.insert(path, json.value("dependencies").toArray().toVariantList());

    delete loader;
    loader = Q_NULLPTR;
}

// 加载插件
void QtPluginsManager::loadPlugin(const QString& path)
{
    // 判断是否是库
    if (!QLibrary::isLibrary(path))
        return;

    // 检测插件依赖
    if (!d->check(path))
        return;

    // 加载插件
    QPluginLoader *loader = new QPluginLoader(path);
    if (loader->load()) {
        // 如果继承自 Plugin，则认为是自己的插件（防止外部插件注入）。
        InterfacePlugin *plugin = qobject_cast<InterfacePlugin *>(loader->instance());
        if (plugin)
        {
            d->m_loaders.insert(path, loader);
        }
        else
        {
            delete loader;
            loader = Q_NULLPTR;
        }
    }
}


// 卸载所有插件
void QtPluginsManager::unloadAllPlugins()
{
    foreach (const QString &path, d->m_loaders.keys())
        unloadPlugin(path);
}

// 卸载插件
void QtPluginsManager::unloadPlugin(const QString& path)
{
    QPluginLoader *loader = d->m_loaders.value(path);

    // 卸载插件，并从内部数据结构中移除
    if (loader->unload())
    {
        d->m_loaders.remove(path);
        delete loader;
        loader = Q_NULLPTR;
    }
}

QList<QPluginLoader *> QtPluginsManager::allPlugins()
{
    return d->m_loaders.values();
}

QPluginLoader* QtPluginsManager::getPlugin(const QString &name)
{
    QPluginLoader *loader = d->m_loaders.value(d->m_names.key(name));
    return  loader;
}

QList<QPluginLoader *> QtPluginsManager::getPluginsByType(const QVariant& type)
{
    QList<QPluginLoader *> plugins;
    QMap<QString, QVariant>::iterator i;
    for(i = d->m_types.begin(); i!=d->m_types.end(); ++i)
    {
        if( i.value()==type )
            plugins.append(d->m_loaders.value(i.key()));
    }
    return plugins;
}


void QtPluginsManager::initSignalAndSlot()
{
    auto plugins = allPlugins();
    foreach (auto loader, plugins)
    {
    // 每个插件发送消息到manager，然后由manager 根据 dest 字段转发
    connect(loader->instance(),SIGNAL(sendMsg2Manager(PluginMetaData)),this,SLOT(recMsgfromPlugin(PluginMetaData)));
    }
}

void QtPluginsManager::recMsgfromPlugin(PluginMetaData metadata)
{
    auto loader = getPlugin(metadata.dest);
    if(loader)
    {
        auto interface = qobject_cast<InterfacePlugin*>(loader->instance());;
        if(interface)
        {
            interface->recMsgfromManager(metadata);
        }
    }
}

void QtPluginsManager::bindVarForAllPlugins(QMap<int, QVector<QString> > & map)
{
    auto plugins = allPlugins();
    foreach (auto loader, plugins)
    {
        if(loader)
        {
            auto interface = qobject_cast<InterfacePlugin*>(loader->instance());;
            if(interface)
            {
                interface->bindVar(map);
            }
        }
    }

}
