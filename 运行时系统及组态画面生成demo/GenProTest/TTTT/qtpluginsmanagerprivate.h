#ifndef QTPLUGINSMANAGERPRIVATE_H
#define QTPLUGINSMANAGERPRIVATE_H
#include <QString>
#include <QVariant>
#include <QDebug>
#include <QPluginLoader>
class QtPluginsManagerPrivate
{
public:
    //����������
    bool check(const QString &filepath);
    QMap<QString, QVariant> m_names; //���·��--�������
    QMap<QString, QVariant> m_versions; //���·��--����汾
    QMap<QString, QVariant> m_types; //���·��--�����������
    QMap<QString, QVariantList>m_dependencies; //���·��--��������������������
    QMap<QString, QPluginLoader *>m_loaders; //���·��--QPluginLoaderʵ��
};

#endif
