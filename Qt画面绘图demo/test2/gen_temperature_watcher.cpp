#include "gen_temperature_watcher.h"
gen_temperature_watcher* gen_temperature_watcher::instance_gt = NULL;
gen_temperature_watcher::GC gen_temperature_watcher::GC::gc_gt;

gen_temperature_watcher::gen_temperature_watcher(QObject *parent) : QObject(parent)
{

}

gen_temperature_watcher::~gen_temperature_watcher()
{

}

void gen_temperature_watcher::addWatchPath(QString path)
{
    qDebug() << QString("Add to watch: %1").arg(path);

    // 添加监控路径
    instance_gt->fileSystemWatcher_gt->addPath(path);

    // 如果添加路径是一个目录，保存当前内容列表
    QFileInfo file(path);
    if (file.isDir())
    {
        const QDir dirw(path);
        instance_gt->currentContentsMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

gen_temperature_watcher *gen_temperature_watcher::getInstance_gt()
{
    if (instance_gt == NULL)
    {
        instance_gt = new gen_temperature_watcher();
        instance_gt->fileSystemWatcher_gt = new QFileSystemWatcher(instance_gt);

        connect(instance_gt->fileSystemWatcher_gt, SIGNAL(fileChanged(QString)), instance_gt, SLOT(fileUpdated(QString)));
    }
    return instance_gt;
}


// 监听的文件必须已经存在,探测不到删除和新建文件，只有文件名或文件内容被修改时才会被触发
void gen_temperature_watcher::fileUpdated(const QString &file)
{
    QFileInfo fileInfo(file);
    QString strPath = fileInfo.absolutePath();
    QString strName = fileInfo.fileName();

    emit sigFileUpdated(strName,strPath);
     qDebug()<<"is send";
}
