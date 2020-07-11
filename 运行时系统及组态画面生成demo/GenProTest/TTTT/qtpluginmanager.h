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
    //�������в��
    void loadAllPlugins();
    //ɨ��JSON�ļ��еĲ��Ԫ����
    void scan(const QString &filepath);
    //��������ĳ�����
    void loadPlugin(const QString &filepath);
    //ж�����в��
    void unloadAllPlugins();
    //ж��ĳ�����
    void unloadPlugin(const QString &filepath);
    //��ȡ���в��
    QList<QPluginLoader *> allPlugins();
    //��ȡĳ�����(by name)
    QPluginLoader* getPlugin(const QString &name);
    //��ȡĳ����(by type)
    QList<QPluginLoader *> getPluginsByType(const QVariant&);
    //��ʼ���Ͳ��ͨ�ŵ��źŲ�
    void initSignalAndSlot();

    //Ϊ���в����var
    void bindVarForAllPlugins(QMap<int, QVector<QString>>&);

public slots:
    //�������Ը��������Ϣ
    void recMsgfromPlugin(PluginMetaData);
private:
    QtPluginsManager()
    {
     d = new QtPluginsManagerPrivate;
    };
    QtPluginsManagerPrivate *d;
};

