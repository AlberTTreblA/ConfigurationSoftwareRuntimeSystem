#ifndef WIDGET_H
#define WIDGET_H

//#include <QWidget>

#include <QMainWindow>

#include "myserver.h"

#include "addcontrollersdialog.h"
#include "mytcpclient.h"

#include <QThread>
#include <QEvent>
#include <QPainter>
#include <QPen>

#include <QTimer>

#include <QTcpSocket>
#include <QTcpServer>
#include <QList>

namespace Ui {
class Widget;
}

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:

     void updateControllersPlainText();

private slots:

    //tcp���������
    void on_btnSwitch_clicked();
//    void newConnection();
    void updateValueForTcpClient();


    //��ӿ��������
    void on_btnAddControllers_clicked();
    void slotShowControllers();
    void slotSaveControllerSettings(QMap<QString, QVector<QString>>);
    void slotCancelControllerSettings();
    void on_btnM1_clicked();
    void on_btnM2_clicked();
    void on_btnM3_clicked();
    //tcp client, connnect and send to controllers
    void on_btnConnectAndSend_clicked();
    void slotSendToControllers();

private:
    Ui::Widget *ui;

    QTimer *tcpSocketTimer;
//    QTcpServer server;
////    QTcpSocket *tcpSocket;
//    QList<QTcpSocket*> tcpclientsocketlist;
//    int MAX_CONNECTED_NUM;        //���������
//    int oldest;                  //����Ԫ�������ﵽ���ֵʱ��������ӵ�Ԫ��λ�ã�
    myServer* server;

    //���������
    AddControllersDialog *addControllersDialog = NULL;
    QMap<QString, QVector<QString>> controllers;
    MyTcpClient* myclient;
    QTimer *tcpClientTimer=NULL;

private:
    

protected:


};

#endif // WIDGET_H
