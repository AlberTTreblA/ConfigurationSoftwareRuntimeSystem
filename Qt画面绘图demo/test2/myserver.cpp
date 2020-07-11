#include "myserver.h"
#include <QHostAddress>
#include <QDebug>

myServer::myServer(QObject *parent, int port):QTcpServer(parent)
{
    listen(QHostAddress::Any, port); //监听
}

void myServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"incomingConnection1";
    myTcpSocket *tcpclientsocket = new myTcpSocket(this);//只要有新的连接就生成一个新的通信套接字
    //将新创建的通信套接字描述符指定为参数socketdescriptor
    tcpclientsocket->setSocketDescriptor(socketDescriptor);

    //将这个套接字加入客户端套接字列表中
    tcpclientsocketlist.append(tcpclientsocket);

    connect(tcpclientsocket, &myTcpSocket::clientdisconnected, this, &myServer::slotclientdisconnect);

}

//void myServer::slotupdateserver(QString msg, int length)
//{

//}

void myServer::slotclientdisconnect(int descriptor)
{
    for(int i = 0; i < tcpclientsocketlist.count(); i++)
    {
        QTcpSocket *item = tcpclientsocketlist.at(i);
        if(item->socketDescriptor() == descriptor)
        {
            tcpclientsocketlist.removeAt(i);//如果有客户端断开连接， 就将列表中的套接字删除
            item->deleteLater();
            return;
        }
    }
    return;
}

void myServer::write(QByteArray str)
{
//    qDebug()<<"server:write";
    for(int i=0; i < tcpclientsocketlist.count(); i++)
    {
//        qDebug()<<i;
        tcpclientsocketlist.at(i)->write(str);
    }
}
