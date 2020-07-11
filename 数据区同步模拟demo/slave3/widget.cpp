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
    QMovie *movie1=new QMovie(":/new/prefix1/fadian.gif");
    ui->label_gen->setMovie(movie1);
    ui->label_gen->setScaledContents(true);
    movie1->start();

    connect(this, &Widget::updateMlabels, this, &Widget::slotUpdateMlabels);

    gen_thread = new gen_temperature_thread;
    mythread_gen = new QThread(this);
    gen_thread->moveToThread(mythread_gen);
    mythread_gen->start();
    connect(this, &Widget::run_gentemp, gen_thread, &gen_temperature_thread::my_temperature);
    connect(gen_thread, &gen_temperature_thread::temperatureChanged, this, &Widget::slotTempChanged);

}

Widget::~Widget()
{
    mythread_gen->terminate();
    delete ui;
}

void Widget::slotTempChanged()
{
    updateGenTempShow();
    sendGenTemp();
}

void Widget::on_btnStartGen_clicked()
{
    if( ui->btnStartGen->text()=="���������" ){
        if( MPoint[1]>=30 )
        {
            emit run_gentemp();
            mythread_gen->start();
            ui->btnStartGen->setText("�رշ����");
        }
        else
        {
            QMessageBox::information(this, "����", "������ת�ٴ���30���ܿ��������");
        }
    }
    else if( ui->btnStartGen->text()=="�رշ����" )
    {
        mythread_gen->terminate();
        qDebug()<<"stop pump";
        ui->btnStartGen->setText("���������");
    }
}

void Widget::on_btnResetGenTemp_clicked()
{
    rw_gen_temperature.lockForWrite();
    MPoint[2] = 0;
    rw_gen_temperature.unlock();
    updateGenTempShow();
    sendGenTemp();
}

void Widget::updateGenTempShow()
{
    rw_gen_temperature.lockForRead();
    ui->label_M3->setText(QString("������¶�: %1").arg(MPoint[2]));
    rw_gen_temperature.unlock();
}

void Widget::sendGenTemp()
{
    QString s;
    s.append("2:"+QString::number(MPoint[2]));
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

void Widget::on_btnChangeAndSend_clicked()
{
    if( flagM3==false ){
        MPoint[2] = 5;
        flagM3 = true;
    }
    else {
        MPoint[2] = 4;
        flagM3 = false;
    }

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
    ui->label_M2->setText(QString("���ֻ�ת��: %1").arg(MPoint[1]));
//    ui->label_M3->setText(QString("M��3��ֵ: %1").arg(MPoint[2]));
}

void Widget::updateMArea(QString newMdata)
{
    QStringList strL = newMdata.split(" ");        //"0:12 1:22"
    strL.removeAll("");
    foreach (QString str, strL) {
        QStringList subStrL = str.split(":");
        int mIndex = subStrL.at(0).toInt();
        if( mIndex==2 )
            continue;
        MPoint[ mIndex ] = subStrL.at(1).toInt();
//        isUpdated[ mIndex ] = true;
    }
}


