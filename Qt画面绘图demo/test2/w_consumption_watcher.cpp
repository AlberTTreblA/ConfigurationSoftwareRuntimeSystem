#include "w_consumption_watcher.h"
w_consumption_watcher* w_consumption_watcher::instance_wc = NULL;
w_consumption_watcher::GC w_consumption_watcher::GC::gc_wc;
w_consumption_watcher::w_consumption_watcher(QObject *parent) : QObject(parent)
{

}

w_consumption_watcher::~w_consumption_watcher()
{

}

//myfilesyswatcer2* myfilesyswatcer2::instance2 = NULL;
//myfilesyswatcer2::GC myfilesyswatcer2::GC::gc2;

void w_consumption_watcher::addWatchPath(QString path)
{
    qDebug() << QString("Add to watch: %1").arg(path);

    // 添加监控路径
    instance_wc->fileSystemWatcher_wc->addPath(path);

    // 如果添加路径是一个目录，保存当前内容列表
    QFileInfo file(path);
    if (file.isDir())
    {
        const QDir dirw(path);
        instance_wc->currentContentsMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

w_consumption_watcher *w_consumption_watcher::getInstance_wc()
{
    if (instance_wc == NULL)
    {
        instance_wc = new w_consumption_watcher();
        instance_wc->fileSystemWatcher_wc = new QFileSystemWatcher(instance_wc);

        connect(instance_wc->fileSystemWatcher_wc, SIGNAL(fileChanged(QString)), instance_wc, SLOT(fileUpdated(QString)));
    }
    return instance_wc;
}


// 监听的文件必须已经存在,探测不到删除和新建文件，只有文件名或文件内容被修改时才会被触发
void w_consumption_watcher::fileUpdated(const QString &file)
{
    QFileInfo fileInfo(file);
    QString strPath = fileInfo.absolutePath();
    QString strName = fileInfo.fileName();

    emit sigFileUpdated(strName,strPath);
     qDebug()<<"is send";
}
