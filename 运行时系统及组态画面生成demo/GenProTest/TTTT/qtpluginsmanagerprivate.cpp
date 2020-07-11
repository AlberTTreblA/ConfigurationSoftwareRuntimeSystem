#include "qtpluginsmanagerprivate.h"

// 检测插件依赖
bool QtPluginsManagerPrivate::check(const QString& path)
{
    bool status = true;

    foreach (QVariant item, m_dependencies.value(path)) {
        QVariantMap map = item.toMap();
        // 依赖的插件名称、版本、路径
        QVariant name = map.value("name");
        QVariant version = map.value("version");
        QString path = m_names.key(name);

        /********** 检测插件是否依赖于其他插件 **********/
        // 先检测插件名称
        if (!m_names.values().contains(name)) {
            qDebug() << Q_FUNC_INFO << "  Missing dependency:" << name.toString() << "for plugin" << path;
            status = false;
            continue;
        }

        // 再检测插件版本
        if (m_versions.value(path) != version) {
            qDebug() << Q_FUNC_INFO << "    Version mismatch:" << name.toString() << "version"
                     << m_versions.value(m_names.key(name)).toString() << "but" << version.toString() << "required for plugin" << path;
            status = false;
            continue;
        }

        // 然后，检测被依赖的插件是否还依赖于另外的插件
        if (!check(path)) {
            qDebug() << Q_FUNC_INFO << "Corrupted dependency:" << name.toString() << "for plugin" << path;
            status = false;
            continue;
        }
    }

    return status;
}

