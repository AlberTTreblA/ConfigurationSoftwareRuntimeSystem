#include "w_consumption_thread.h"
#include <QThread>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
w_consumption_thread::w_consumption_thread(QObject *parent) : QObject(parent)
{

    w_consumption_watcher::getInstance_wc()->addWatchPath("../waterpumpPower.txt");
    connect(w_consumption_watcher::getInstance_wc(),&w_consumption_watcher::sigFileUpdated,this,&w_consumption_thread::myfile_cons);

}

w_consumption_thread::~w_consumption_thread()
{

}


void w_consumption_thread::my_consuomption()
{

    while(1)
    {
        QEventLoop loop1;
        QTimer::singleShot(1000,&loop1,SLOT(quit()));
                loop1.exec();

         waterpump_consumption_rw.lockForWrite();
         waterpump_consumption+=1;
         waterpump_consumption_rw.unlock();

    }

}

void w_consumption_thread::myfile_cons(QString fileName, QString filePath)
{
    qDebug()<<"text is ok";
    QString path=(filePath+"/"+fileName);
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();

    waterpump_consumption_rw.lockForWrite();
    waterpump_consumption=t.toInt();
    waterpump_consumption_rw.unlock();
     file.close();
}
