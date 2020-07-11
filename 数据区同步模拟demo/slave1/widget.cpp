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
     * �����Ƕ���������ʽ������
     */
    ui->setupUi(this);
    QMovie *movie1=new QMovie(":/new/prefix1/shuibeng.gif");
    ui->label_pump->setMovie(movie1);
    ui->label_pump->setScaledContents(true);
    movie1->start();

    connect(this, &Widget::updateMlabels, this, &Widget::slotUpdateMlabels);

    wh_thread=new w_heighth_thread;
    mythread_pumpHeight=new QThread(this);
    wh_thread->moveToThread(mythread_pumpHeight);
    mythread_pumpHeight->start();
    connect(this, &Widget::run_waterpump, wh_thread, &w_heighth_thread::my_height);
    connect(wh_thread, &w_heighth_thread::waterHeightChanged, this, &Widget::slotWaterHeightChanged);

}

Widget::~Widget()
{
    mythread_pumpHeight->terminate();
    delete ui;
}


//���master���
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
    for (i = masters.begin(); i != masters.end(); ++i) {   //������const_iterator
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

void Widget::on_btnStartPump_clicked()
{
    if( ui->btnStartPump->text()=="����ˮ��" ){
        emit run_waterpump();
        mythread_pumpHeight->start();
        ui->btnStartPump->setText("�ر�ˮ��");
    }
    else if( ui->btnStartPump->text()=="�ر�ˮ��" )
    {
        mythread_pumpHeight->terminate();
        qDebug()<<"stop pump";
        ui->btnStartPump->setText("����ˮ��");
    }
}

void Widget::on_btnResetWaterHeight_clicked()
{
    waterpump_heighth_rw.lockForWrite();
    MPoint[0] = 0;
    waterpump_heighth_rw.unlock();
    updateWaterHeightShow();
    sendWaterHeight();
}

void Widget::slotWaterHeightChanged()
{
    updateWaterHeightShow();
    sendWaterHeight();
}

void Widget::updateWaterHeightShow()
{
    waterpump_heighth_rw.lockForRead();
    ui->label_M1->setText(QString("ˮ��Һ��߶�: %1").arg(MPoint[0]));
    waterpump_heighth_rw.unlock();
}

void Widget::on_btnConnectToMaster_clicked()
{
    if(ui->btnConnectToMaster->text() == "���ӵ�master") {
        myclient = new MyTcpClient;
        myclient->connectToHost(masters);
        connect(myclient, &MyTcpClient::receivedData, this, &Widget::slotReceivedData);
        ui->btnConnectToMaster->setText("�Ͽ�����");
    }
    else if(ui->btnConnectToMaster->text() == "�Ͽ�����") {
        myclient->disconnect();
        myclient->deleteLater();
        myclient=NULL;
        ui->btnConnectToMaster->setText("���ӵ�master");
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
//    ui->label_M1->setText(QString("M��1��ֵ: %1").arg(MPoint[0]));
    ui->label_M2->setText(QString("���ֻ�ת��: %1").arg(MPoint[1]));
    ui->label_M3->setText(QString("������¶�: %1").arg(MPoint[2]));
}

void Widget::updateMArea(QString newMdata)
{
    QStringList strL = newMdata.split(" ");        //"0:12 1:22"
    strL.removeAll("");
    foreach (QString str, strL) {
        QStringList subStrL = str.split(":");
        int mIndex = subStrL.at(0).toInt();
        if( mIndex==0 )
            continue;
        MPoint[ mIndex ] = subStrL.at(1).toInt();
//        isUpdated[ mIndex ] = true;
    }
}

void Widget::sendWaterHeight()
{
    QString s;
    s.append("0:"+QString::number(MPoint[0]));
    if( myclient&&myclient->isConnected() ){
        myclient->write( s.toLatin1() );
    }
}


