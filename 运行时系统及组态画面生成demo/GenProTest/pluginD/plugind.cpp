#include "plugind.h"
#include "ui_plugind.h"
#include <QDebug>
#include <QTimer>

pluginD::pluginD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pluginD)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("汽轮机"));
    //2:汽轮机转速，3:汽轮机功率
    var[2] = Q_NULLPTR;
    var[3] = Q_NULLPTR;

    rTimer = new QTimer(this);
    rTimer->setInterval(1000);
    connect(rTimer, SIGNAL(timeout()), this, SLOT(updateValueForRotation()));
    rTimer->start();

    pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(updateValueForPower()));
    pTimer->start();
}

pluginD::~pluginD()
{
    delete ui;
    qDebug()<<"delete d";
}

void pluginD::recMsgfromManager(PluginMetaData metedata)
{
    qDebug() << "recMsgfromManager : " << metedata.from;
}

void pluginD::bindVar(QMap<int, QVector<QString>>& map)
{
    QMap<int, QVector<QString>*>::iterator i;
    QMap<int, QVector<QString>>::iterator j;
    for(i=var.begin(); i!=var.end(); ++i)
    {
        for(j=map.begin(); j!=map.end(); ++j)
        {
            if( i.key()==j.key() )
                i.value() = &j.value();
        }
    }
}

void pluginD::updateValueForRotation()
{
    if( var[2]==Q_NULLPTR )
    {
        ui->lineEdit_TurbineRotation->setText("null");
    }
    else
    {
        ui->lineEdit_TurbineRotation->setText((*var[2])[0]);
    }
}

void pluginD::updateValueForPower()
{
    if( var[3]==Q_NULLPTR )
    {
        ui->lineEdit_TurbinePower->setText("null");
    }
    else
    {
        ui->lineEdit_TurbinePower->setText((*var[3])[0]);
    }
}
