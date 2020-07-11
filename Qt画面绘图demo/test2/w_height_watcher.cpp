#include "w_height_watcher.h"
w_height_watcher* w_height_watcher::instance_wh = NULL;
w_height_watcher::GC w_height_watcher::GC::gc_wh;

w_height_watcher::w_height_watcher(QObject *parent) : QObject(parent)
{

}

w_height_watcher::~w_height_watcher()
{

}

void w_height_watcher::addWatchPath(QString path)
{
    qDebug() << QString("Add to watch: %1").arg(path);

    // 添加监控路径
    instance_wh->fileSystemWatcher_wh->addPath(path);

    // 如果添加路径是一个目录，保存当前内容列表
    QFileInfo file(path);
    if (file.isDir())
    {
        const QDir dirw(path);
        instance_wh->currentContentsMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

w_height_watcher *w_height_watcher::getInstance_wh()
{
    if (instance_wh == NULL)
    {
        instance_wh = new w_height_watcher();
        instance_wh->fileSystemWatcher_wh = new QFileSystemWatcher(instance_wh);

        connect(instance_wh->fileSystemWatcher_wh, SIGNAL(fileChanged(QString)), instance_wh, SLOT(fileUpdated(QString)));
    }
    return instance_wh;
}


// 监听的文件必须已经存在,探测不到删除和新建文件，只有文件名或文件内容被修改时才会被触发
void w_height_watcher::fileUpdated(const QString &file)
{
    QFileInfo fileInfo(file);
    QString strPath = fileInfo.absolutePath();
    QString strName = fileInfo.fileName();

    emit sigFileUpdated(strName,strPath);
     qDebug()<<"is send";
}
