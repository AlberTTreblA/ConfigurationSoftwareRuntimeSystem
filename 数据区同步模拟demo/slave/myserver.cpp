#include "myserver.h"
#include <QHostAddress>
#include <QDebug>

myServer::myServer(QObject *parent, int port):QTcpServer(parent)
{
    listen(QHostAddress::Any, port); //����
}

void myServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"incomingConnection1";
    myTcpSocket *tcpclientsocket = new myTcpSocket(this);//ֻҪ���µ����Ӿ�����һ���µ�ͨ���׽���
    //���´�����ͨ���׽���������ָ��Ϊ����socketdescriptor
    tcpclientsocket->setSocketDescriptor(socketDescriptor);

    //������׽��ּ���ͻ����׽����б���
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
            tcpclientsocketlist.removeAt(i);//����пͻ��˶Ͽ����ӣ� �ͽ��б��е��׽���ɾ��
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
