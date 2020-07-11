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
#include <QMovie>

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
    connect(this, &Widget::updateMlabels, this, &Widget::slotUpdateMlabels);

    tur_thread = new tur_rotation_thread;
    mythread_tur = new QThread(this);
    tur_thread->moveToThread(mythread_tur);
    mythread_tur->start();
    connect(this, &Widget::run_turbine, tur_thread, &tur_rotation_thread::my_rotation);
    connect(tur_thread, &tur_rotation_thread::RotSpeedChanged, this, &Widget::slotRotSpeedChanged);
}

Widget::~Widget()
{
    mythread_tur->terminate();
    delete ui;
}

void Widget::slotRotSpeedChanged()
{
    updateRotSpeedShow();
    sendRotSpeed();
}

void Widget::updateRotSpeedShow()
{
    rw_tur_rotation.lockForRead();
    ui->label_M2->setText(QString("汽轮机转速: %1").arg(MPoint[1]));
    rw_tur_rotation.unlock();
}

void Widget::sendRotSpeed()
{
    QString s;
    s.append("1:"+QString::number(MPoint[1]));
    if( myclient&&myclient->isConnected() ){
        myclient->write( s.toLatin1() );
    }
}


//添加master相关
void Widget::on_btnAddMaster_clicked()
{
    addMastersDialog = new AddMastersDialog(this, masters);
    addMastersDialog->setModal(false);
    addMastersDialog->show();
    connect(addMastersDialog, &AddMastersDialog::saveMasterSettings, this, &Widget::slotSaveMasterSettings);
    connect(this, &Widget::updateMastersPlainText, this, &Widget::slotShowMasters);
    connect(addMastersDialog, &AddMastersDialog::cancelMasterSettings, this, &Widget::slotCancelMasterSettings);
}

void Widget::slotSaveMasterSettings(QMap<QString, QVector<QString>> c)
{
    masters = c;
    delete addMastersDialog;
    addMastersDialog = NULL;
    emit updateMastersPlainText();
}

void Widget::slotShowMasters()
{
//    qDebug()<<"slotShowControllers";
    ui->plainTextEdit_masters->clear();
    QString s;
    QMap<QString, QVector<QString>>::iterator i;
    for (i = masters.begin(); i != masters.end(); ++i) {   //不能用const_iterator
        s.append(i.key()).append(": \n");
//        qDebug()<<"loop1";
        QVector<QString>::iterator j;
        for(j = masters[i.key()].begin();  j != masters[i.key()].end(); ++j)
        {
//            qDebug()<<*j;
            s.append(*j).append(" ");
        }
        s.append("\n");
    }
    ui->plainTextEdit_masters->setPlainText(s);
}

void Widget::slotCancelMasterSettings()
{
    delete addMastersDialog;
    addMastersDialog = NULL;
}

void Widget::on_btnStartTurbine_clicked()
{
    if( ui->btnStartTurbine->text()=="开启汽轮机" ){
        if( MPoint[0]>=20 )
        {
            emit run_turbine();
            mythread_tur->start();
            ui->btnStartTurbine->setText("关闭汽轮机");
        }
        else
        {
            QMessageBox::information(this, "错误", "水泵液面高度大于20才能开启蒸汽机");
        }
    }
    else if( ui->btnStartTurbine->text()=="关闭汽轮机" )
    {
        mythread_tur->terminate();
        qDebug()<<"stop turbine";
        ui->btnStartTurbine->setText("开启汽轮机");
    }
}

void Widget::on_btnResetTurRotation_clicked()
{
    rw_tur_rotation.lockForWrite();
    MPoint[1] = 0;
    rw_tur_rotation.unlock();
    updateRotSpeedShow();
    sendRotSpeed();
}


void Widget::on_btnConnectToMaster_clicked()
{
    if(ui->btnConnectToMaster->text() == "连接到master") {
        myclient = new MyTcpClient;
        myclient->connectToHost(masters);
        connect(myclient, &MyTcpClient::receivedData, this, &Widget::slotReceivedData);
        ui->btnConnectToMaster->setText("断开连接");
    }
    else if(ui->btnConnectToMaster->text() == "断开连接") {
        myclient->disconnect();
        myclient->deleteLater();
        myclient=NULL;
        ui->btnConnectToMaster->setText("连接到master");
    }
}

void Widget::slotReceivedData(QString newMdata)
{
//    qDebug()<<"in slave1/widget reveived newMdata:"<<newMdata;
    updateMArea(newMdata);
    emit updateMlabels();
}

void Widget::slotUpdateMlabels()
{
    ui->label_M1->setText(QString("水泵液面高度: %1").arg(MPoint[0]));
//    ui->label_M2->setText(QString("M点2的值: %1").arg(MPoint[1]));
    ui->label_M3->setText(QString("发电机温度: %1").arg(MPoint[2]));
}

void Widget::updateMArea(QString newMdata)
{
    QStringList strL = newMdata.split(" ");        //"0:12 1:22"
    strL.removeAll("");
    foreach (QString str, strL) {
        QStringList subStrL = str.split(":");
        int mIndex = subStrL.at(0).toInt();
        if( mIndex==1 )
            continue;
        MPoint[ mIndex ] = subStrL.at(1).toInt();
//        isUpdated[ mIndex ] = true;
    }
}


