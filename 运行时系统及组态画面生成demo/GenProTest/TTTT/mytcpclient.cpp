#include "mytcpclient.h"
#include <QHostAddress>
#include <QDebug>
#include <QStringList>

MyTcpClient::MyTcpClient(QObject *parent):QObject(parent)
{
    connected = false;
}

MyTcpClient::~MyTcpClient()
{
    QMap<QTcpSocket*, QVector<int>>::iterator i;
    for(i=tcpserversocketlist.begin(); i!=tcpserversocketlist.end(); ++i)
    {
        i.key()->close();
//        delete *(i.key());
    }
}

void MyTcpClient::connectToHost(QMap<QString, QVector<QString> >& controllers)
{
    tcpserversocketlist.clear();
    QMap<QString, QVector<QString> >::iterator i;
    for(i=controllers.begin(); i!= controllers.end(); ++i){

        QVector<QString>::iterator j=i.value().begin();
        QTcpSocket *socket =  new QTcpSocket(this);
        socket->connectToHost(QHostAddress(j[0]), j[1].toInt());
        connect(socket, &QTcpSocket::readyRead, this, &MyTcpClient::slotReceiveData);
        connect(socket, &QTcpSocket::disconnected, this, &MyTcpClient::slotServerDisconnected);
        connect(socket, &QTcpSocket::connected, this, &MyTcpClient::slotConnected);

        QVector<int> mIndex;
//        qDebug()<<"j[2]:"<<j[2];
        if( !j[2].isEmpty() )
        {
            QStringList strM =  j[2].split(" ");
            strM.removeAll("");
            foreach (QString str, strM) {
//                qDebug()<<"str in list:"<<str;
//                qDebug()<<"size:"<<strM.count();
                mIndex.push_back(str.toInt());
            }
        }
        tcpserversocketlist[socket] = mIndex;

    }
    connected = true;
}

void MyTcpClient::slotConnected()
{
    qDebug()<<"connected";
}

void MyTcpClient::disconnect()
{
    QMap<QTcpSocket*, QVector<int>>::iterator i;
    for(i=tcpserversocketlist.begin(); i!=tcpserversocketlist.end(); ++i)
    {
        i.key()->close();
    }
    connected = false;
}

void MyTcpClient::slotReceiveData()
{
    QTcpSocket *obj = (QTcpSocket*)sender();
    QString msg = obj->readAll();
    qDebug()<<"slave1 client received data: "<< msg <<" from"<<obj->peerAddress().toString();
    emit receivedData(msg);
    //#######TODO根据收到的数据更新M区
}

void MyTcpClient::slotServerDisconnected()
{
    QTcpSocket *obj = (QTcpSocket*)sender();
    qDebug()<<"in slave1:"<<obj->peerAddress().toString()<<" port:"<<obj->peerPort()<<"  disconnected.";
}

void MyTcpClient::write(QByteArray strB)
{

    QMap<QTcpSocket*, QVector<int> >::iterator i;
    qDebug()<<"list size:"<<tcpserversocketlist.count();
    for(i=tcpserversocketlist.begin(); i != tcpserversocketlist.end(); ++i)
    {
////        qDebug()<<"write:loop1";
//        QString s;
//        for(int j=0; j<i.value().count(); ++j){
////            qDebug()<<"write loop2";
////            qDebug()<<i.value()[j];
//            s.append( QString::number(MPoint[ i.value()[j] ]) );
//        }
//        if( !s.isEmpty() )
//        {
////            qDebug()<<"data to be sent:"<<s;
//            i.key()->write(s.toLatin1());
//        }
        i.key()->write( strB );
    }
}

bool MyTcpClient::isConnected()
{
    return connected;
}
