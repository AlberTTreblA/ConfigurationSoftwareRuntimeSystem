#include "widget.h"
#include "ui_widget.h"
#include "global.h"
#include <QString>
#include <QDebug>
#include <qmath.h>
#include <QString>
#include <QDialog>
#include <QMessageBox>
#include <stdio.h>
#include <QStringList>
#include "global.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

Widget::Widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initGlobalVars();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotClientConnected(QString clientIP)
{
    qDebug()<<"client connected   "<<clientIP;
    clientIPAdress.append(clientIP);
    resetSlavePlaintText();
}

void Widget::slotClientDisconnected(QString clientIP)
{
    qDebug()<<"client disconnected   "<<clientIP;
    clientIPAdress.removeAll(clientIP);
    resetSlavePlaintText();
}

void Widget::slotReceivedDate(QString msg)
{
    //#####TODU根据msg修改global_var和isUpdated;
    qDebug()<<"in master/widget:received data";
//    global_var[0]++;
    processReceivedData(msg);
}

void Widget::slotSynchroDate()
{
//############TODO
//    qDebug()<<"in master/widget: synchroDate";
    QString s;
    QMap<int, QVector<QString>>::iterator i;
    for(i=global_var.begin(); i!=global_var.end(); ++i)
    {
        s.append(QString::number(i.key())+":"+i.value()[0]+" ");
    }
    server->write(s.toLatin1());
}


void Widget::on_btnStartMaster_clicked()
{
    if (ui->btnStartMaster->text() == "开启master") {
        server = new MyServer(0, 8888);
        synchroTimer = new QTimer(this);
        synchroTimer->setInterval(1000);
        connect(synchroTimer, SIGNAL(timeout()), this, SLOT(slotSynchroDate()));
        connect(server, &MyServer::clientConnected, this, &Widget::slotClientConnected);
        connect(server, &MyServer::clientDisconnected, this, &Widget::slotClientDisconnected);
        connect(server, &MyServer::receivedDate, this, &Widget::slotReceivedDate);
        synchroTimer->start();
        ui->btnStartMaster->setText("关闭master");
    } else {
        server->Close();
        server->deleteLater();
        synchroTimer->deleteLater();
        ui->plainTextEdit_slaves->clear();
        ui->btnStartMaster->setText("开启master");

    }
}

void Widget::resetSlavePlaintText()
{
    ui->plainTextEdit_slaves->clear();
    QString s;
    for(int i=0; i<clientIPAdress.count(); ++i){
        s.append(clientIPAdress[i]+"\n");
    }
    ui->plainTextEdit_slaves->setPlainText(s);
}

void Widget::processReceivedData(QString msg)
{
    QStringList strL = msg.split(" ");    //"0:12 1:33" ===>某slave拥有的M区序号:slave发送的整个该M区的更新值(本例中只有一个值)
    strL.removeAll("");
    foreach (QString str, strL) {
        QStringList subStrL = str.split(":");
        int mIndex = subStrL.at(0).toInt();
        global_var[ mIndex ] = QVector<QString>({subStrL.at(1)});
    }
}

void Widget::on_lineEdit_PumpH_textChanged()
{
    global_var[0][0] = ui->lineEdit_PumpH->text();
}

void Widget::on_lineEdit_PumpT_textChanged()
{
    global_var[1][0] = ui->lineEdit_PumpT->text();

}

void Widget::on_lineEdit_TurbineR_textChanged()
{
    global_var[2][0] = ui->lineEdit_TurbineR->text();
}

void Widget::on_lineEdit_TurbineP_textChanged()
{
    global_var[3][0] = ui->lineEdit_TurbineP->text();

}


