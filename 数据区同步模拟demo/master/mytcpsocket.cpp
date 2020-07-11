#include "mytcpsocket.h"

myTcpSocket::myTcpSocket(QObject *parent)
{
    //客户端发送数据过来就会触发readyRead信号
    connect(this, &QTcpSocket::readyRead, this, &myTcpSocket::receivedata);
    connect(this, &QTcpSocket::disconnected, this, &myTcpSocket::slotclientdisconnected);
    connect(this, &QTcpSocket::connected, this, &myTcpSocket::slotclientconnected);
}

void myTcpSocket::receivedata()
{
    QByteArray array = readAll();
    QString msg = array;
    emit receivedData(msg);
}

void myTcpSocket::slotclientdisconnected()
{
    qDebug()<<"disconnected";
    emit clientdisconnected(this->socketDescriptor());
}

void myTcpSocket::slotclientconnected()
{
    qDebug()<<"connected";
}
