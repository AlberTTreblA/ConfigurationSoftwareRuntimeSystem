#ifndef QTPLUGINSMANAGERPRIVATE_H
#define QTPLUGINSMANAGERPRIVATE_H
#include <QString>
#include <QVariant>
#include <QDebug>
#include <QPluginLoader>
class QtPluginsManagerPrivate
{
public:
    //插件依赖检测
    bool check(const QString &filepath);
    QMap<QString, QVariant> m_names; //插件路径--插件名称
    QMap<QString, QVariant> m_versions; //插件路径--插件版本
    QMap<QString, QVariant> m_types; //插件路径--插件画面类型
    QMap<QString, QVariantList>m_dependencies; //插件路径--插件额外依赖的其他插件
    QMap<QString, QPluginLoader *>m_loaders; //插件路径--QPluginLoader实例
};

#endif
