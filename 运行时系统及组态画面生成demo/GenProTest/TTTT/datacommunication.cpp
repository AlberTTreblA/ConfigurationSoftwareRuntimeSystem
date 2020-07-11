#include "datacommunication.h"
#include "global.h"
#include <QStringList>
#include <QDebug>

void DataCommunication::init()
{
    masters["controller_1"] = QVector<QString>({"127.0.0.1", "8888", "0 1 2 3"});
    myclient = new MyTcpClient;
    myclient->connectToHost(masters);
    connect(myclient, &MyTcpClient::receivedData, this, &DataCommunication::slotReceivedData);
}

void DataCommunication::disconnect()
{
    myclient->disconnect();
}

void DataCommunication::slotReceivedData(QString msg)
{
    QStringList strL = msg.split(" ");        //"0:12 1:22"
    strL.removeAll("");
    foreach (QString str, strL) {
        QStringList subStrL = str.split(":");
        int mIndex = subStrL.at(0).toInt();
        global_var[ mIndex ][0] = subStrL.at(1);
    }
//        qDebug() << "in datacommunication, &global_var[0][0]:" << &global_var[0][0];
}
