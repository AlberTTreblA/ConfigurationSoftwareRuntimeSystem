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
    void incomingConnection(qintptr socketDescriptor);//只要出现一个新的连接，就会自动调用这个函数
protected slots:
//    void slotupdateserver(QString, int);//用来处理tcpclient发过来的信号
    void slotclientdisconnect(int);

signals:

};

#endif // MYSERVER_H
