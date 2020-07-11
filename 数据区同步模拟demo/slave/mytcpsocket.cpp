#include "mytcpsocket.h"

myTcpSocket::myTcpSocket(QObject *parent)
{
    //客户端发送数据过来就会触发readyRead信号
//    connect(this, &TcpClientSocket::readyRead, this, &TcpClientSocket::receivedata);
    connect(this, &myTcpSocket::disconnected, this, &myTcpSocket::slotclientdisconnected);
}

//void myTcpSocket::receivedata()
//{
//    int length = 10;
//    QByteArray array = readAll();
//    QString msg = array;
//    emit updateserver(msg, length);
//}

void myTcpSocket::slotclientdisconnected()
{
    emit clientdisconnected(this->socketDescriptor());
}
