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
    ui->label_M2->setText(QString("���ֻ�ת��: %1").arg(MPoint[1]));
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

void Widget::on_btnStartTurbine_clicked()
{
    if( ui->btnStartTurbine->text()=="�������ֻ�" ){
        if( MPoint[0]>=20 )
        {
            emit run_turbine();
            mythread_tur->start();
            ui->btnStartTurbine->setText("�ر����ֻ�");
        }
        else
        {
            QMessageBox::information(this, "����", "ˮ��Һ��߶ȴ���20���ܿ���������");
        }
    }
    else if( ui->btnStartTurbine->text()=="�ر����ֻ�" )
    {
        mythread_tur->terminate();
        qDebug()<<"stop turbine";
        ui->btnStartTurbine->setText("�������ֻ�");
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
    ui->label_M1->setText(QString("ˮ��Һ��߶�: %1").arg(MPoint[0]));
//    ui->label_M2->setText(QString("M��2��ֵ: %1").arg(MPoint[1]));
    ui->label_M3->setText(QString("������¶�: %1").arg(MPoint[2]));
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


