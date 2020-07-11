#ifndef MYSERVER_H
#define MYSERVER_H

#include "mytcpsocket.h"
#include <QTcpServer>
#include <QObject>
#include <QList>
#include <QByteArray>
#include <QString>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    MyServer(QObject *parent = 0, int port = 8080);
    QList<myTcpSocket*> tcpclientsocketlist;
    void write(QByteArray);
    void Close();
protected:
    void incomingConnection(qintptr socketDescriptor);//ֻҪ����һ���µ����ӣ��ͻ��Զ������������
protected slots:
    void slotReceivedDate(QString);
    void slotclientdisconnect(int);

signals:
    void clientDisconnected(QString);
    void receivedDate(QString);
    void clientConnected(QString);
    

};

#endif // MYSERVER_H
