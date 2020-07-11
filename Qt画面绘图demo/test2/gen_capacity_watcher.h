#ifndef GEN_CAPACITY_WATCHER_H
#define GEN_CAPACITY_WATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
class gen_capacity_watcher : public QObject
{
    Q_OBJECT
public:
    explicit gen_capacity_watcher(QObject *parent = 0);
    ~gen_capacity_watcher();

    static gen_capacity_watcher *getInstance_gc();
   void addWatchPath(QString path);
signals:
   void sigFileUpdated(QString fileName,QString filePath);

public slots:
   void fileUpdated(const QString &file);          // 文件名或文件内容被修改时调用

private:
   static gen_capacity_watcher *instance_gc;           // 单例
   QFileSystemWatcher *fileSystemWatcher_gc;
   QMap<QString, QStringList> currentContentsMap;  // 当前每个监控的内容目录列表


   // 内存释放
   class GC
   {
   public:
       ~GC()
       {
           // 可以在这里销毁所有的资源
           if (instance_gc != NULL) {
               qDebug() << "destroy instance...";
               delete instance_gc->fileSystemWatcher_gc;
               delete instance_gc;
               instance_gc = NULL;
           }
       }
       static GC gc_gc;  // 用于释放单例
   };

};


#endif // GEN_CAPACITY_WATCHER_H
