#include "tur_consumption_thread.h"
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

tur_consumption_thread::tur_consumption_thread(QObject *parent) : QObject(parent)
{
    tur_consumption_watcher::getInstance_tc()->addWatchPath("E:/qtcode/qt/test2.txt");
    connect(tur_consumption_watcher::getInstance_tc(),&tur_consumption_watcher::sigFileUpdated,this,&tur_consumption_thread::myfile_consumption);
}

tur_consumption_thread::~tur_consumption_thread()
{

}

void tur_consumption_thread::my_consumption()
{
    while(1)
    {
    QEventLoop loop1;
    QTimer::singleShot(1000,&loop1,SLOT(quit()));
            loop1.exec();
           rw_tur_consumption.lockForWrite();
           tur_consumption+=4;
           rw_tur_consumption.unlock();
    }
}
void tur_consumption_thread::myfile_consumption(QString fileName, QString filePath)
{
    qDebug()<<"text is ok";
    QString path=(filePath+"/"+fileName);
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();

    rw_tur_consumption.lockForWrite();
    tur_consumption=t.toInt();
    rw_tur_consumption.unlock();
     file.close();
}
