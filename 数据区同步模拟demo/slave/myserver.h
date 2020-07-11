#ifndef MYSERVER_H
#define MYSERVER_H

#include "mytcpsocket.h"
#include <QTcpServer>
#include <QObject>
#include <QList>
#include <QByteArray>

class myServer : public QTcpServer
{
    Q_OBJECT
public:
    myServer(QObject *parent = 0, int port = 8080);
    QList<myTcpSocket*> tcpclientsocketlist;
    void write(QByteArray);
protected:
    void incomingConnection(qintptr socketDescriptor);//ֻҪ����һ���µ����ӣ��ͻ��Զ������������
protected slots:
//    void slotupdateserver(QString, int);//��������tcpclient���������ź�
    void slotclientdisconnect(int);

signals:

};

#endif // MYSERVER_H
