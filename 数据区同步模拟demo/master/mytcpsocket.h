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
    void receivedata();//����readyRead�źŶ�ȡ����
    void slotclientdisconnected();//�ͻ��˶Ͽ����Ӵ���disconnected�źţ�����ۺ���������������ź�
    void slotclientconnected();

signals:
    void clientdisconnected(int); //����server�пͻ��˶Ͽ�����
    void receivedData(QString);   //����server�пͻ��˷������ݹ���
};


#endif // MYTCPSOCKET_H
