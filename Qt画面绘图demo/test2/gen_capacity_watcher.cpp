#include "gen_capacity_watcher.h"
gen_capacity_watcher* gen_capacity_watcher::instance_gc = NULL;
gen_capacity_watcher::GC gen_capacity_watcher::GC::gc_gc;

gen_capacity_watcher::gen_capacity_watcher(QObject *parent) : QObject(parent)
{

}

gen_capacity_watcher::~gen_capacity_watcher()
{

}
void gen_capacity_watcher::addWatchPath(QString path)
{
    qDebug() << QString("Add to watch: %1").arg(path);

    // 添加监控路径
    instance_gc->fileSystemWatcher_gc->addPath(path);

    // 如果添加路径是一个目录，保存当前内容列表
    QFileInfo file(path);
    if (file.isDir())
    {
        const QDir dirw(path);
        instance_gc->currentContentsMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

gen_capacity_watcher *gen_capacity_watcher::getInstance_gc()
{
    if (instance_gc == NULL)
    {
        instance_gc = new gen_capacity_watcher();
        instance_gc->fileSystemWatcher_gc = new QFileSystemWatcher(instance_gc);

        connect(instance_gc->fileSystemWatcher_gc, SIGNAL(fileChanged(QString)), instance_gc, SLOT(fileUpdated(QString)));
    }
    return instance_gc;
}


// 监听的文件必须已经存在,探测不到删除和新建文件，只有文件名或文件内容被修改时才会被触发
void gen_capacity_watcher::fileUpdated(const QString &file)
{
    QFileInfo fileInfo(file);
    QString strPath = fileInfo.absolutePath();
    QString strName = fileInfo.fileName();

    emit sigFileUpdated(strName,strPath);
     qDebug()<<"is send";
}

