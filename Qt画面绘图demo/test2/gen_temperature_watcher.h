#ifndef GEN_TEMPERATURE_WATCHER_H
#define GEN_TEMPERATURE_WATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
class gen_temperature_watcher : public QObject
{
    Q_OBJECT
public:
    explicit gen_temperature_watcher(QObject *parent = 0);
    ~gen_temperature_watcher();

    static gen_temperature_watcher *getInstance_gt();
   void addWatchPath(QString path);
signals:
   void sigFileUpdated(QString fileName,QString filePath);

public slots:
   void fileUpdated(const QString &file);          // 文件名或文件内容被修改时调用

private:
   static gen_temperature_watcher *instance_gt;           // 单例
   QFileSystemWatcher *fileSystemWatcher_gt;
   QMap<QString, QStringList> currentContentsMap;  // 当前每个监控的内容目录列表


   // 内存释放
   class GC
   {
   public:
       ~GC()
       {
           // 可以在这里销毁所有的资源
           if (instance_gt != NULL) {
               qDebug() << "destroy instance...";
               delete instance_gt->fileSystemWatcher_gt;
               delete instance_gt;
               instance_gt = NULL;
           }
       }
       static GC gc_gt;  // 用于释放单例
   };

};

#endif // GEN_TEMPERATURE_WATCHER_H
