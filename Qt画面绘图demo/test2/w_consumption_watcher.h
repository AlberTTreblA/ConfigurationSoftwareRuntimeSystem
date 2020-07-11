#ifndef W_CONSUMPTION_WATCHER_H
#define W_CONSUMPTION_WATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

class w_consumption_watcher : public QObject
{
    Q_OBJECT
public:
    explicit w_consumption_watcher(QObject *parent = 0);
    ~w_consumption_watcher();
     static w_consumption_watcher *getInstance_wc();
    void addWatchPath(QString path);
signals:
    void sigFileUpdated(QString fileName,QString filePath);

public slots:
    void fileUpdated(const QString &file);          // 文件名或文件内容被修改时调用

private:
    static w_consumption_watcher *instance_wc;           // 单例
    QFileSystemWatcher *fileSystemWatcher_wc;
    QMap<QString, QStringList> currentContentsMap;  // 当前每个监控的内容目录列表


    // 内存释放
    class GC
    {
    public:
        ~GC()
        {
            // 可以在这里销毁所有的资源
            if (instance_wc != NULL) {
                qDebug() << "destroy instance...";
                delete instance_wc->fileSystemWatcher_wc;
                delete instance_wc;
                instance_wc = NULL;
            }
        }
        static GC gc_wc;  // 用于释放单例
    };

};

#endif // W_CONSUMPTION_WATCHER_H
