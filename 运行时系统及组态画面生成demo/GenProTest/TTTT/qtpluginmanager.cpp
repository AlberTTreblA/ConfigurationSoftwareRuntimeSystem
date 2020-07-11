#include "qtpluginmanager.h"
#include <QFileInfo>
#include <QApplication>
#include <QJsonObject>
#include <QJsonArray>
#include"interfaceplugin.h"

// �������в��
QDir QtPluginsManager::getPluginPath()
{
    // ������Ŀ¼
    QDir path = QDir(qApp->applicationDirPath());
    path.cd("../plugins");
    return path;
}

void QtPluginsManager::loadAllPlugins()
{
    // ������Ŀ¼
    QDir path = getPluginPath();

    // ��ʼ������е�Ԫ����
    foreach (QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
            scan(info.absoluteFilePath());
    }
    // ���ز��
    foreach (QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
            loadPlugin(info.absoluteFilePath());
    }
}


// ɨ�� JSON �ļ��еĲ��Ԫ����
void QtPluginsManager::scan(const QString& path)
{
    /*****
     *  �ж��Ƿ��ǿ⣨��׺��Ч�ԣ�
     * Windows��.dll��.DLL
     * Unix/Linux��.so
   *****/

    if (!QLibrary::isLibrary(path))
        return;

    // ��ȡԪ���ݣ����ơ��汾��������
    QPluginLoader *loader = new QPluginLoader(path);
    QJsonObject json = loader->metaData().value("MetaData").toObject();

    d->m_names.insert(path, json.value("name").toVariant());
    d->m_versions.insert(path, json.value("version").toVariant());
    d->m_types.insert(path, json.value("type").toVariant());
    d->m_dependencies.insert(path, json.value("dependencies").toArray().toVariantList());

    delete loader;
    loader = Q_NULLPTR;
}

// ���ز��
void QtPluginsManager::loadPlugin(const QString& path)
{
    // �ж��Ƿ��ǿ�
    if (!QLibrary::isLibrary(path))
        return;

    // ���������
    if (!d->check(path))
        return;

    // ���ز��
    QPluginLoader *loader = new QPluginLoader(path);
    if (loader->load()) {
        // ����̳��� Plugin������Ϊ���Լ��Ĳ������ֹ�ⲿ���ע�룩��
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


// ж�����в��
void QtPluginsManager::unloadAllPlugins()
{
    foreach (const QString &path, d->m_loaders.keys())
        unloadPlugin(path);
}

// ж�ز��
void QtPluginsManager::unloadPlugin(const QString& path)
{
    QPluginLoader *loader = d->m_loaders.value(path);

    // ж�ز���������ڲ����ݽṹ���Ƴ�
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
    // ÿ�����������Ϣ��manager��Ȼ����manager ���� dest �ֶ�ת��
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
