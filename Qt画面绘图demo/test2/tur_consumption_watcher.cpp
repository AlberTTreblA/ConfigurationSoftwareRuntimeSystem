#include "tur_consumption_watcher.h"
tur_consumption_watcher* tur_consumption_watcher::instance_tc = NULL;
tur_consumption_watcher::GC tur_consumption_watcher::GC::gc_tc;

tur_consumption_watcher::tur_consumption_watcher(QObject *parent) : QObject(parent)
{

}

tur_consumption_watcher::~tur_consumption_watcher()
{

}

void tur_consumption_watcher::addWatchPath(QString path)
{
    qDebug() << QString("Add to watch: %1").arg(path);

    // 添加监控路径
    instance_tc->fileSystemWatcher_tc->addPath(path);

    // 如果添加路径是一个目录，保存当前内容列表
    QFileInfo file(path);
    if (file.isDir())
    {
        const QDir dirw(path);
        instance_tc->currentContentsMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

tur_consumption_watcher *tur_consumption_watcher::getInstance_tc()
{
    if (instance_tc == NULL)
    {
        instance_tc = new tur_consumption_watcher();
        instance_tc->fileSystemWatcher_tc = new QFileSystemWatcher(instance_tc);

        connect(instance_tc->fileSystemWatcher_tc, SIGNAL(fileChanged(QString)), instance_tc, SLOT(fileUpdated(QString)));
    }
    return instance_tc;
}


// 监听的文件必须已经存在,探测不到删除和新建文件，只有文件名或文件内容被修改时才会被触发
void tur_consumption_watcher::fileUpdated(const QString &file)
{
    QFileInfo fileInfo(file);
    QString strPath = fileInfo.absolutePath();
    QString strName = fileInfo.fileName();

    emit sigFileUpdated(strName,strPath);
     qDebug()<<"is send";
}
