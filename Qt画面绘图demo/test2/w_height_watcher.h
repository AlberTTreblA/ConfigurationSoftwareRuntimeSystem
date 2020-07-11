#ifndef W_HEIGHT_WATCHER_H
#define W_HEIGHT_WATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
class w_height_watcher : public QObject
{
    Q_OBJECT
public:
    explicit w_height_watcher(QObject *parent = 0);
    ~w_height_watcher();

    static w_height_watcher *getInstance_wh();
   void addWatchPath(QString path);
signals:
   void sigFileUpdated(QString fileName,QString filePath);

public slots:
   void fileUpdated(const QString &file);          // 文件名或文件内容被修改时调用

private:
   static w_height_watcher *instance_wh;           // 单例
   QFileSystemWatcher *fileSystemWatcher_wh;
   QMap<QString, QStringList> currentContentsMap;  // 当前每个监控的内容目录列表


   // 内存释放
   class GC
   {
   public:
       ~GC()
       {
           // 可以在这里销毁所有的资源
           if (instance_wh != NULL) {
               qDebug() << "destroy instance...";
               delete instance_wh->fileSystemWatcher_wh;
               delete instance_wh;
               instance_wh = NULL;
           }
       }
       static GC gc_wh;  // 用于释放单例
   };

};


#endif // W_HEIGHT_WATCHER_H
