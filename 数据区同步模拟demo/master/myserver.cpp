#include "myserver.h"
#include <QHostAddress>
#include <QDebug>

MyServer::MyServer(QObject *parent, int port):QTcpServer(parent)
{
    listen(QHostAddress::Any, port); //����
    qDebug() << port;
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"incomingConnection1";
    myTcpSocket *tcpclientsocket = new myTcpSocket(this);//ֻҪ���µ����Ӿ�����һ���µ�ͨ���׽���
    //���´�����ͨ���׽���������ָ��Ϊ����socketdescriptor
    tcpclientsocket->setSocketDescriptor(socketDescriptor);

    //������׽��ּ���ͻ����׽����б���
    tcpclientsocketlist.append(tcpclientsocket);
    emit clientConnected(tcpclientsocket->peerAddress().toString()+":"+QString::number(tcpclientsocket->peerPort()));
    connect(tcpclientsocket, &myTcpSocket::receivedData, this, &MyServer::slotReceivedDate);
    connect(tcpclientsocket, &myTcpSocket::clientdisconnected, this, &MyServer::slotclientdisconnect);
}

void MyServer::slotReceivedDate(QString msg)
{
    qDebug()<<"in master/server slotReceiveDate";
    emit receivedDate(msg);
}

void MyServer::slotclientdisconnect(int descriptor)
{
    for(int i = 0; i < tcpclientsocketlist.count(); i++)
    {
        QTcpSocket *item = tcpclientsocketlist.at(i);
        if(item->socketDescriptor() == descriptor)
        {
            tcpclientsocketlist.removeAt(i);//����пͻ��˶Ͽ����ӣ� �ͽ��б��е��׽���ɾ��
            emit clientDisconnected(item->peerAddress().toString()+":"+QString::number(item->peerPort()));
            item->deleteLater();
            return;
        }
    }
    return;
}

void MyServer::write(QByteArray str)
{
//    qDebug()<<"server:write";
    for(int i=0; i < tcpclientsocketlist.count(); i++)
    {
//        qDebug()<<i;
        tcpclientsocketlist.at(i)->write(str);
    }
}

void MyServer::Close()
{
    for(int i=0; i < tcpclientsocketlist.count(); i++)
    {
//        qDebug()<<i;
        tcpclientsocketlist.at(i)->close();
    }
    this->close();
}
