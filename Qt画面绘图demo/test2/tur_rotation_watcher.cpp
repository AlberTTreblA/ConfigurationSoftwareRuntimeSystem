#include "tur_rotation_watcher.h"
tur_rotation_watcher* tur_rotation_watcher::instance_tr = NULL;
tur_rotation_watcher::GC tur_rotation_watcher::GC::gc_tr;

tur_rotation_watcher::tur_rotation_watcher(QObject *parent) : QObject(parent)
{

}

tur_rotation_watcher::~tur_rotation_watcher()
{

}

void tur_rotation_watcher::addWatchPath(QString path)
{
    qDebug() << QString("Add to watch: %1").arg(path);

    // 添加监控路径
    instance_tr->fileSystemWatcher_tr->addPath(path);

    // 如果添加路径是一个目录，保存当前内容列表
    QFileInfo file(path);
    if (file.isDir())
    {
        const QDir dirw(path);
        instance_tr->currentContentsMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

tur_rotation_watcher *tur_rotation_watcher::getInstance_tr()
{
    if (instance_tr == NULL)
    {
        instance_tr = new tur_rotation_watcher();
        instance_tr->fileSystemWatcher_tr = new QFileSystemWatcher(instance_tr);

        connect(instance_tr->fileSystemWatcher_tr, SIGNAL(fileChanged(QString)), instance_tr, SLOT(fileUpdated(QString)));
    }
    return instance_tr;
}


// 监听的文件必须已经存在,探测不到删除和新建文件，只有文件名或文件内容被修改时才会被触发
void tur_rotation_watcher::fileUpdated(const QString &file)
{
    QFileInfo fileInfo(file);
    QString strPath = fileInfo.absolutePath();
    QString strName = fileInfo.fileName();

    emit sigFileUpdated(strName,strPath);
     qDebug()<<"is send";
}
