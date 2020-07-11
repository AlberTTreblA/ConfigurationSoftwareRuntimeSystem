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
     qDebug() << "未能找到插件C";
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
     qDebug() << "未能找到插件D";
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
     qDebug() << "未能找到插件A";
    }
}

void Widget::on_btnSimulator_clicked()
{
    if( ui->btnSimulator->text()==QString::fromLocal8Bit("仿真中") )
    {
        ui->btnSimulator->setText(QString::fromLocal8Bit("开启仿真模式"));
        simulatorThread->requestInterruption();
        simulatorThread->quit();
        simulatorThread->wait();
    }
    else if( ui->btnRunMode->text()==QString::fromLocal8Bit("开启运行模式") )
    {
        ui->btnSimulator->setText(QString::fromLocal8Bit("仿真中"));
        if( simulatorThread==Q_NULLPTR )
        {
            simulatorThread = new QThread(this);
            Simulator::getInstance().moveToThread(simulatorThread);
            connect(this, &Widget::startSimulate, &Simulator::getInstance(), &Simulator::loadData);
        }
        simulatorThread->start();
        emit startSimulate();

    }
    else if( ui->btnRunMode->text()==QString::fromLocal8Bit("运行中") )
    {
        QMessageBox::critical(0 ,
        QString::fromLocal8Bit("提示") , QString::fromLocal8Bit("请先退出运行模式"),
        QMessageBox::Ok | QMessageBox::Default ,
        QMessageBox::Cancel | QMessageBox::Escape , 0 );
    }
}

void Widget::on_btnRunMode_clicked()
{
    if( ui->btnRunMode->text()==QString::fromLocal8Bit("运行中") )
    {
        ui->btnRunMode->setText(QString::fromLocal8Bit("开启运行模式"));
        DataCommunication::getInstance().disconnect();
        dataSaveThread->requestInterruption();
        dataSaveThread->quit();
        dataSaveThread->wait();
    }
    else if( ui->btnSimulator->text()==QString::fromLocal8Bit("开启仿真模式") )
    {
        ui->btnRunMode->setText(QString::fromLocal8Bit("运行中"));
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
    else if( ui->btnSimulator->text()==QString::fromLocal8Bit("仿真中") )
    {
        QMessageBox::critical(0 ,
        QString::fromLocal8Bit("提示") , QString::fromLocal8Bit("请先退出仿真模式"),
        QMessageBox::Ok | QMessageBox::Default ,
        QMessageBox::Cancel | QMessageBox::Escape , 0 );
    }
}

