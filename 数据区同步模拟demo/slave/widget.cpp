#include "widget.h"
#include "ui_widget.h"
#include "global.h"
#include <QMovie>
#include <QString>
#include <QDebug>
#include <qmath.h>
#include <QString>
#include <QDialog>
//#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <stdio.h>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

Widget::Widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Widget)
{

    /*
     * 下面是对主界面样式的设置
     */
    ui->setupUi(this);


//     //设置最大监听数量
//     MAX_CONNECTED_NUM = 2;
//     oldest = 0;
//     //服务器监听设置
//     server.listen(QHostAddress::Any,8080);
//     connect(&server,SIGNAL(newConnection()),this,SLOT(newConnection()));
     server = new myServer(0, 8080);
     //设置定时器向客户端输出开关值
     tcpSocketTimer = new QTimer(this);
     tcpSocketTimer->setInterval(1000);
     connect(tcpSocketTimer, SIGNAL(timeout()), this, SLOT(updateValueForTcpClient()));
     tcpSocketTimer->start();

}

Widget::~Widget()
{
    delete ui;
}


//tcp、开关相关
void Widget::on_btnSwitch_clicked()
{
    if (ui->btnSwitch->text() == "打开开关") {
        switch_value = 1;
        ui->labelSwitchValue->setText(QString("开关变量值：%1").arg(QString::number(switch_value, 10)));
        ui->btnSwitch->setText("关闭开关");
    } else {
        switch_value = 0;
        ui->labelSwitchValue->setText(QString("开关变量值：%1").arg(QString::number(switch_value, 10)));
        ui->btnSwitch->setText("打开开关");
    }
}

//void Widget::newConnection()
//{
////    qDebug()<<"newConnection";
//    if( tcpclientsocketlist.size() < MAX_CONNECTED_NUM )
//        tcpclientsocketlist.append(server.nextPendingConnection());
//    else{
//        tcpclientsocketlist.replace(oldest%MAX_CONNECTED_NUM, server.nextPendingConnection());
//        oldest++;
//    }
//}

void Widget::updateValueForTcpClient()
{
//    qDebug()<<"updateValueForTcpClient";
    QString str=QString::number(switch_value, 10);
    QByteArray strByte = str.toLatin1();

//    if(tcpSocket)
//        tcpSocket->write(strByte);
//    for( int i=0; i<tcpclientsocketlist.size(); i++ ){
//        tcpclientsocketlist.at(i)->write(strByte);
//    }
    server->write(strByte);

}

//添加控制器相关
void Widget::on_btnAddControllers_clicked()
{
    addControllersDialog = new AddControllersDialog(this, controllers);
    addControllersDialog->setModal(false);
    addControllersDialog->show();
    connect(addControllersDialog, &AddControllersDialog::saveControllerSettings, this, &Widget::slotSaveControllerSettings);
    connect(this, &Widget::updateControllersPlainText, this, &Widget::slotShowControllers);
    connect(addControllersDialog, &AddControllersDialog::cancelControllerSettings, this, &Widget::slotCancelControllerSettings);
}

void Widget::slotSaveControllerSettings(QMap<QString, QVector<QString>> c)
{
    controllers = c;
    delete addControllersDialog;
    addControllersDialog = NULL;
    emit updateControllersPlainText();
}

void Widget::slotShowControllers()
{
//    qDebug()<<"slotShowControllers";
    ui->plainTextEdit_controllers->clear();
    QString s;
    QMap<QString, QVector<QString>>::iterator i;
    for (i = controllers.begin(); i != controllers.end(); ++i) {   //不能用const_iterator
        s.append(i.key()).append(": \n");
//        qDebug()<<"loop1";
        QVector<QString>::iterator j;
        for(j = controllers[i.key()].begin();  j != controllers[i.key()].end(); ++j)
        {
//            qDebug()<<*j;
            s.append(*j).append(" ");
        }
        s.append("\n");
    }
    ui->plainTextEdit_controllers->setPlainText(s);
}

void Widget::slotCancelControllerSettings()
{
    delete addControllersDialog;
    addControllersDialog = NULL;
}

void Widget::on_btnM1_clicked()
{
    if (ui->btnM1->text() == "打开") {
        MPoint[0] = 1;
        ui->label_M1->setText(QString("M点1的值: %1").arg(QString::number(MPoint[0], 10)));
        ui->btnM1->setText("关闭");
    } else {
        MPoint[0] = 0;
        ui->label_M1->setText(QString("M点1的值: %1").arg(QString::number(MPoint[0], 10)));
        ui->btnM1->setText("打开");
    }
}

void Widget::on_btnM2_clicked()
{
    if (ui->btnM2->text() == "打开") {
        MPoint[1] = 3;
        ui->label_M2->setText(QString("M点2的值: %1").arg(QString::number(MPoint[1], 10)));
        ui->btnM2->setText("关闭");
    } else {
        MPoint[1] = 2;
        ui->label_M2->setText(QString("M点2的值: %1").arg(QString::number(MPoint[1], 10)));
        ui->btnM2->setText("打开");
    }
}

void Widget::on_btnM3_clicked()
{
    if (ui->btnM3->text() == "打开") {
        MPoint[2] = 5;
        ui->label_M3->setText(QString("M点3的值: %1").arg(QString::number(MPoint[2], 10)));
        ui->btnM3->setText("关闭");
    } else {
        MPoint[2] = 4;
        ui->label_M3->setText(QString("M点3的值: %1").arg(QString::number(MPoint[2], 10)));
        ui->btnM3->setText("打开");
    }
}

void Widget::on_btnConnectAndSend_clicked()
{
    if(ui->btnConnectAndSend->text() == "连接到控制器并发送数据") {
        myclient = new MyTcpClient;
        myclient->connectToHost(controllers);

        if( tcpClientTimer==NULL ){
            tcpClientTimer = new QTimer(this);
            tcpClientTimer->setInterval(3000);
            connect(tcpClientTimer, SIGNAL(timeout()), this, SLOT(slotSendToControllers()));
        }
        tcpClientTimer->start();
        ui->btnConnectAndSend->setText("断开连接");
    }
    else if(ui->btnConnectAndSend->text() == "断开连接") {
        tcpClientTimer->stop();
        myclient->disconnect();
        ui->btnConnectAndSend->setText("连接到控制器并发送数据");
    }
}

void Widget::slotSendToControllers()
{
    if( myclient->isConnected() )
        myclient->write();
}


