#ifndef DATACOMMUNICATION_H
#define DATACOMMUNICATION_H

#include <QObject>
#include "mytcpclient.h"

class  DataCommunication : public QObject
{
    Q_OBJECT

public:
    static DataCommunication &getInstance()
    {
        static DataCommunication m_instance;
        return m_instance;
    }
public:
    void init();
    void disconnect();

public slots:
    void slotReceivedData(QString);
private:
    QMap<QString, QVector<QString>> masters;
    MyTcpClient* myclient=Q_NULLPTR;
};

#endif // DATACOMMUNICATION_H
