#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
#include <QString>

class myTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    myTcpSocket(QObject *parent = 0);
protected slots:
    void receivedata();//处理readyRead信号读取数据
    void slotclientdisconnected();//客户端断开连接触发disconnected信号，这个槽函数用来处理这个信号
    void slotclientconnected();

signals:
    void clientdisconnected(int); //告诉server有客户端断开连接
    void receivedData(QString);   //告诉server有客户端发送数据过来
};


#endif // MYTCPSOCKET_H
