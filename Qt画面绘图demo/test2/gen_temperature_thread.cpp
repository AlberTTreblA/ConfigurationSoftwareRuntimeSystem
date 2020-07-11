#include "gen_temperature_thread.h"
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

gen_temperature_thread::gen_temperature_thread(QObject *parent) : QObject(parent)
{
    gen_temperature_watcher::getInstance_gt()->addWatchPath("E:/qtcode/qt/test5.txt");
    connect(gen_temperature_watcher::getInstance_gt(),&gen_temperature_watcher::sigFileUpdated,this,&gen_temperature_thread::myfile_temp);
}

gen_temperature_thread::~gen_temperature_thread()
{
//    gen_temperature_watcher::getInstance_gt()->addWatchPath("E:/qtcode/qt/test5.txt");
//    connect(gen_temperature_watcher::getInstance_gt(),&gen_temperature_watcher::sigFileUpdated,this,&gen_temperature_thread::myfile_temp);
}

void gen_temperature_thread::my_temperature()
{
    while(1)
    {
    QEventLoop loop1;
    QTimer::singleShot(1000,&loop1,SLOT(quit()));
            loop1.exec();
            rw_gen_temperature.lockForWrite();
            gen_temperature+=3;
            rw_gen_temperature.unlock();
    }
}
void gen_temperature_thread::myfile_temp(QString fileName, QString filePath)
{
    qDebug()<<"text is ok";
    QString path=(filePath+"/"+fileName);
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();

    rw_gen_temperature.lockForWrite();
    gen_temperature=t.toInt();
    rw_gen_temperature.unlock();
     file.close();
}
