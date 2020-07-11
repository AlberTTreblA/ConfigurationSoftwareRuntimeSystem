#include "pluginc.h"
PluginC::PluginC(QWidget *parent):QWidget(parent)
{
var[0]=nullptr;
var[1]=nullptr;
this->setWindowTitle(QString::fromLocal8Bit("水泵画面"));
this->setGeometry(QRect(500,300,400,500));
}
void PluginC::bindVar(QMap<int, QVector<QString>>& map)
{
QMap<int, QVector<QString>*>::iterator i;
QMap<int, QVector<QString>>::iterator j;
for(i=var.begin(); i!=var.end(); ++i)
{
for(j=map.begin(); j!=map.end(); ++j)
{
if( i.key()==j.key() )
{
i.value() = &j.value();
}
}
}
alarm0=new Alarm(this,QString::fromLocal8Bit("液高"),&(*var[0])[0],200,0);
label0=new Label(this,QString::fromLocal8Bit("水泵液高"),20,40,100,20);
line0=new Line(this,&(*var[0])[0],20,20,100,20);
}
void PluginC::recMsgfromManager(PluginMetaData metedata)
{}
