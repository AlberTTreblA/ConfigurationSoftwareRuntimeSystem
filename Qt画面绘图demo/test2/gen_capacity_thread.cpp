#include "gen_capacity_thread.h"
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

gen_capacity_thread::gen_capacity_thread(QObject *parent) : QObject(parent)
{
    gen_capacity_watcher::getInstance_gc()->addWatchPath("E:/qtcode/qt/test4.txt");
    connect(gen_capacity_watcher::getInstance_gc(),&gen_capacity_watcher::sigFileUpdated,this,&gen_capacity_thread::myfile_capa);
}

gen_capacity_thread::~gen_capacity_thread()
{
//    gen_capacity_watcher::getInstance_gc()->addWatchPath("E:/qtcode/qt/test4.txt");
//    connect(gen_capacity_watcher::getInstance_gc(),&gen_capacity_watcher::sigFileUpdated,this,&gen_capacity_thread::myfile_capa);
}

void gen_capacity_thread::my_capacity()
{
    while(1)
    {
    QEventLoop loop1;
    QTimer::singleShot(1000,&loop1,SLOT(quit()));
            loop1.exec();
           rw_gen_capacitu.lockForWrite();
           gen_capacity+=1;
           rw_gen_capacitu.unlock();
    }
}
void gen_capacity_thread::myfile_capa(QString fileName, QString filePath)
{
    qDebug()<<"text is ok";
    QString path=(filePath+"/"+fileName);
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();

    rw_gen_capacitu.lockForWrite();
    gen_capacity=t.toInt();
    rw_gen_capacitu.unlock();
     file.close();
}
