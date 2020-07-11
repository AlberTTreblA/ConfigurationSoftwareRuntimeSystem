#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
//#include <QList>
#include <QByteArray>
#include <QMap>
#include <QVector>
#include <QString>
#include "global.h"

class MyTcpClient : public QObject
{
    Q_OBJECT
public:
    MyTcpClient(QObject *parent = 0);
    ~MyTcpClient();
    void write();

    void connectToHost(QMap<QString, QVector<QString>>&);
    void disconnect();
    bool isConnected();



signals:

public slots:

private:
    QMap<QTcpSocket*, QVector<int>> tcpserversocketlist;
    bool connected;


};
#endif // MYTCPCLIENT_H
