#include "pluginA.h"
#include <QtDebug>
#include <QFileDialog>
#include <QPixmap>
PluginA::PluginA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PluginA)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(clickOpenImg()));
    connect(ui->pushButton2,SIGNAL(clicked()),this,SLOT(click2Animation()));
}

void PluginA::clickOpenImg()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Ñ¡ÔñÍ¼Æ¬"), ".", tr("Image Files(*.jpg *.png)"));
    ui->label->setPixmap(QPixmap(path));
}

void PluginA::click2Animation()
{
        PluginMetaData metadata;
        metadata.from = "pluginA";
        metadata.dest = "pluginB";
        metadata.type = 1;
        metadata.object = ui->label;
        emit sendMsg2Manager(metadata);
}

void PluginA::recMsgfromManager(PluginMetaData metedata)
{
    qDebug() << "recMsgfromManager : " << metedata.from;
}

void PluginA::bindVar(QMap<int, QVector<QString> > &)
{

}

