#include "w_heighth_thread.h"
#include <QThread>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

w_heighth_thread::w_heighth_thread(QObject *parent) : QObject(parent)
{
    w_height_watcher::getInstance_wh()->addWatchPath("../waterpumpHeight.txt");
    connect(w_height_watcher::getInstance_wh(),&w_height_watcher::sigFileUpdated,this,&w_heighth_thread::myfile_height);
}

w_heighth_thread::~w_heighth_thread()
{

}

void w_heighth_thread::my_height()
{
    while(1)
    {
        QEventLoop loop1;
        QTimer::singleShot(1000,&loop1,SLOT(quit()));
                loop1.exec();

        waterpump_heighth_rw.lockForWrite();
        waterpump_heighth+=2;
        waterpump_heighth_rw.unlock();
        qDebug("high is %d",waterpump_heighth);

    }

}
void w_heighth_thread::myfile_height(QString fileName, QString filePath)
{
    qDebug()<<"text is ok";
    QString path=(filePath+"/"+fileName);
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();

    waterpump_heighth_rw.lockForWrite();
    waterpump_heighth=t.toInt();
    waterpump_heighth_rw.unlock();
     file.close();
}
