#ifndef TUR_CONSUMPTION_WATCHER_H
#define TUR_CONSUMPTION_WATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
class tur_consumption_watcher : public QObject
{
    Q_OBJECT
public:
    explicit tur_consumption_watcher(QObject *parent = 0);
    ~tur_consumption_watcher();

    static tur_consumption_watcher *getInstance_tc();
   void addWatchPath(QString path);
signals:
   void sigFileUpdated(QString fileName,QString filePath);

public slots:
   void fileUpdated(const QString &file);          // 文件名或文件内容被修改时调用

private:
   static tur_consumption_watcher *instance_tc;           // 单例
   QFileSystemWatcher *fileSystemWatcher_tc;
   QMap<QString, QStringList> currentContentsMap;  // 当前每个监控的内容目录列表


   // 内存释放
   class GC
   {
   public:
       ~GC()
       {
           // 可以在这里销毁所有的资源
           if (instance_tc != NULL) {
               qDebug() << "destroy instance...";
               delete instance_tc->fileSystemWatcher_tc;
               delete instance_tc;
               instance_tc = NULL;
           }
       }
       static GC gc_tc;  // 用于释放单例
   };

};


#endif // TUR_CONSUMPTION_WATCHER_H
