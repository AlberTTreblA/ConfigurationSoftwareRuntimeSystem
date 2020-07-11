#include "mytcpsocket.h"

myTcpSocket::myTcpSocket(QObject *parent)
{
    //�ͻ��˷������ݹ����ͻᴥ��readyRead�ź�
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
