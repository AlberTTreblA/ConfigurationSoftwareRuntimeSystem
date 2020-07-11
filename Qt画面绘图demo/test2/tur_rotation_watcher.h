#ifndef TUR_ROTATION_WATCHER_H
#define TUR_ROTATION_WATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
class tur_rotation_watcher : public QObject
{
    Q_OBJECT
public:
    explicit tur_rotation_watcher(QObject *parent = 0);
    ~tur_rotation_watcher();

    static tur_rotation_watcher *getInstance_tr();
   void addWatchPath(QString path);
signals:
   void sigFileUpdated(QString fileName,QString filePath);

public slots:
   void fileUpdated(const QString &file);          // 文件名或文件内容被修改时调用

private:
   static tur_rotation_watcher *instance_tr;           // 单例
   QFileSystemWatcher *fileSystemWatcher_tr;
   QMap<QString, QStringList> currentContentsMap;  // 当前每个监控的内容目录列表


   // 内存释放
   class GC
   {
   public:
       ~GC()
       {
           // 可以在这里销毁所有的资源
           if (instance_tr != NULL) {
               qDebug() << "destroy instance...";
               delete instance_tr->fileSystemWatcher_tr;
               delete instance_tr;
               instance_tr = NULL;
           }
       }
       static GC gc_tr;  // 用于释放单例
   };

};


#endif // TUR_ROTATION_WATCHER_H
