#include "tur_rotation_thread.h"
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

tur_rotation_thread::tur_rotation_thread(QObject *parent) : QObject(parent)
{
//    tur_rotation_watcher::getInstance_tr()->addWatchPath("E:/qtcode/qt/test3.txt");
//    connect(tur_rotation_watcher::getInstance_tr(),&tur_rotation_watcher::sigFileUpdated,this,&tur_rotation_thread::myfile_rotation);
}

tur_rotation_thread::~tur_rotation_thread()
{

}

void tur_rotation_thread::my_rotation()
{
    while(1)
    {
    QEventLoop loop1;
    QTimer::singleShot(1000,&loop1,SLOT(quit()));
            loop1.exec();
           rw_tur_rotation.lockForWrite();
           MPoint[1]+=2;
           rw_tur_rotation.unlock();
           emit RotSpeedChanged();
    }
}
//void tur_rotation_thread::myfile_rotation(QString fileName, QString filePath)

//{
//    qDebug()<<"text is ok";
//    QString path=(filePath+"/"+fileName);
//    QFile file(path);
//    file.open(QIODevice::ReadOnly | QIODevice::Text);
//    QByteArray t = file.readAll();

//    rw_tur_rotation.lockForWrite();
//    tur_rotation=t.toInt();
//    rw_tur_rotation.unlock();
//     file.close();
//}
