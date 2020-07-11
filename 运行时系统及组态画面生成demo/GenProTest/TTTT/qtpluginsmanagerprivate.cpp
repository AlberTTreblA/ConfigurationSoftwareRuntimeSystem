#include "qtpluginsmanagerprivate.h"

// ���������
bool QtPluginsManagerPrivate::check(const QString& path)
{
    bool status = true;

    foreach (QVariant item, m_dependencies.value(path)) {
        QVariantMap map = item.toMap();
        // �����Ĳ�����ơ��汾��·��
        QVariant name = map.value("name");
        QVariant version = map.value("version");
        QString path = m_names.key(name);

        /********** ������Ƿ�������������� **********/
        // �ȼ��������
        if (!m_names.values().contains(name)) {
            qDebug() << Q_FUNC_INFO << "  Missing dependency:" << name.toString() << "for plugin" << path;
            status = false;
            continue;
        }

        // �ټ�����汾
        if (m_versions.value(path) != version) {
            qDebug() << Q_FUNC_INFO << "    Version mismatch:" << name.toString() << "version"
                     << m_versions.value(m_names.key(name)).toString() << "but" << version.toString() << "required for plugin" << path;
            status = false;
            continue;
        }

        // Ȼ�󣬼�ⱻ�����Ĳ���Ƿ�����������Ĳ��
        if (!check(path)) {
            qDebug() << Q_FUNC_INFO << "Corrupted dependency:" << name.toString() << "for plugin" << path;
            status = false;
            continue;
        }
    }

    return status;
}

