#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>

class myTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    myTcpSocket(QObject *parent = 0);
protected slots:
//    void receivedata();//����readyRead�źŶ�ȡ����
    void slotclientdisconnected();//�ͻ��˶Ͽ����Ӵ���disconnected�źţ�����ۺ���������������ź�

signals:
    void clientdisconnected(int); //����server�пͻ��˶Ͽ�����
};


#endif // MYTCPSOCKET_H
