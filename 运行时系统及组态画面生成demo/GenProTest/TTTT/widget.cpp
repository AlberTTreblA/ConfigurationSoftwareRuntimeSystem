#include "widget.h"
#include "ui_widget.h"
#include "qtpluginmanager.h"
#include "interfaceplugin.h"
#include "datasave.h"
#include "simulator.h"
#include "datacommunication.h"
#include <QMessageBox>
#include <QDebug>
#include "global.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
//    qDebug() << "&global_var[0][0]:" << &global_var[0][0];
    ui->setupUi(this);
    connect(ui->pushButtonA,SIGNAL(clicked()),this,SLOT(clickA()));

    connect(this, &Widget::startSavingData, &DataSave::getInstance(), &DataSave::saveData);
    dataSaveThread = new QThread(this);
    DataSave::getInstance().moveToThread(dataSaveThread);
    dataSaveThread->start();
    emit startSavingData();

    connect(this, &Widget::startSimulate, &Simulator::getInstance(), &Simulator::loadData);
    simulatorThread = new QThread(this);
    Simulator::getInstance().moveToThread(simulatorThread);
    simulatorThread->start();
    emit startSimulate();
}

Widget::~Widget()
{
//    disconnect(this, &Widget::startSavingData, &DataSave::getInstance(), &DataSave::saveData);
//    dataSaveThread->terminate();
//    dataSaveThread->quit();
//    dataSaveThread->wait();
//    dataSaveThread->deleteLater();
    dataSaveThread->requestInterruption();
    dataSaveThread->quit();
    dataSaveThread->wait();

    simulatorThread->requestInterruption();
    simulatorThread->quit();
    simulatorThread->wait();

    delete ui;
}

void Widget::on_btnPump_clicked()
{
    QList<QPluginLoader *> pluginsList =  QtPluginsManager::getInstance().getPluginsByType(QVariant(0));
    QPluginLoader *loader = Q_NULLPTR;
    if( pluginsList.length()>0 )
    {
        loader = pluginsList[0];
    }
    if(loader)
    {
        auto obj = loader->instance();
        if(obj->isWidgetType())
        {
            QWidget *widget = qobject_cast<QWidget*>(obj);
            widget->show();
        }
    }
    else
    {
     qDebug() << "δ���ҵ����C";
    }
}

void Widget::on_btnTurbine_clicked()
{
    QList<QPluginLoader *> pluginsList =  QtPluginsManager::getInstance().getPluginsByType(QVariant(1));
    QPluginLoader *loader = Q_NULLPTR;
    if( pluginsList.length()>0 )
    {
        loader = pluginsList[0];
    }
    if(loader)
    {
        auto obj = loader->instance();
        if(obj->isWidgetType())
        {
            QWidget *widget = qobject_cast<QWidget*>(obj);
            widget->show();
        }
    }
    else
    {
     qDebug() << "δ���ҵ����D";
    }
}

void Widget::clickA()
{
    QPluginLoader *loader =  QtPluginsManager::getInstance().getPlugin("pluginA");
//    QList<QPluginLoader *> pluginsList =  QtPluginsManager::getInstance().getPluginsByType(QVariant(0));
//    QPluginLoader *loader = Q_NULLPTR;
//    if( pluginsList.length()>0 )
//    {
//        loader = pluginsList[0];
//    }
    if(loader)
    {
        auto obj = loader->instance();
        if(obj->isWidgetType())
        {
            QWidget *widget = qobject_cast<QWidget*>(obj);
            widget->show();
        }
    }
    else
    {
     qDebug() << "δ���ҵ����A";
    }
}

void Widget::on_btnSimulator_clicked()
{
    if( ui->btnSimulator->text()==QString::fromLocal8Bit("������") )
    {
        ui->btnSimulator->setText(QString::fromLocal8Bit("��������ģʽ"));
        simulatorThread->requestInterruption();
        simulatorThread->quit();
        simulatorThread->wait();
    }
    else if( ui->btnRunMode->text()==QString::fromLocal8Bit("��������ģʽ") )
    {
        ui->btnSimulator->setText(QString::fromLocal8Bit("������"));
        if( simulatorThread==Q_NULLPTR )
        {
            simulatorThread = new QThread(this);
            Simulator::getInstance().moveToThread(simulatorThread);
            connect(this, &Widget::startSimulate, &Simulator::getInstance(), &Simulator::loadData);
        }
        simulatorThread->start();
        emit startSimulate();

    }
    else if( ui->btnRunMode->text()==QString::fromLocal8Bit("������") )
    {
        QMessageBox::critical(0 ,
        QString::fromLocal8Bit("��ʾ") , QString::fromLocal8Bit("�����˳�����ģʽ"),
        QMessageBox::Ok | QMessageBox::Default ,
        QMessageBox::Cancel | QMessageBox::Escape , 0 );
    }
}

void Widget::on_btnRunMode_clicked()
{
    if( ui->btnRunMode->text()==QString::fromLocal8Bit("������") )
    {
        ui->btnRunMode->setText(QString::fromLocal8Bit("��������ģʽ"));
        DataCommunication::getInstance().disconnect();
        dataSaveThread->requestInterruption();
        dataSaveThread->quit();
        dataSaveThread->wait();
    }
    else if( ui->btnSimulator->text()==QString::fromLocal8Bit("��������ģʽ") )
    {
        ui->btnRunMode->setText(QString::fromLocal8Bit("������"));
        DataCommunication::getInstance().init();
        if( dataSaveThread==Q_NULLPTR )
        {
            connect(this, &Widget::startSavingData, &DataSave::getInstance(), &DataSave::saveData);
            dataSaveThread = new QThread(this);
            DataSave::getInstance().moveToThread(dataSaveThread);
        }
        dataSaveThread->start();
        emit startSavingData();

    }
    else if( ui->btnSimulator->text()==QString::fromLocal8Bit("������") )
    {
        QMessageBox::critical(0 ,
        QString::fromLocal8Bit("��ʾ") , QString::fromLocal8Bit("�����˳�����ģʽ"),
        QMessageBox::Ok | QMessageBox::Default ,
        QMessageBox::Cancel | QMessageBox::Escape , 0 );
    }
}

