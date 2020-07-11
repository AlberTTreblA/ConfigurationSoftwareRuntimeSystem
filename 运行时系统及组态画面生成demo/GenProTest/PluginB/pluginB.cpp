#include "pluginB.h"
#include <QtDebug>
#include <QPropertyAnimation>

PluginB::PluginB(QObject *parent) :
    QObject(parent)
{
}

void PluginB::recMsgfromManager(PluginMetaData metedata)
{
    qDebug() << "PluginB recMsgfromManager : ";
    qDebug() << "metedata.from:" << metedata.from;
    qDebug() << "metedata.dest:" << metedata.dest;
    qDebug() << "metedata.type:" << metedata.type;
    if(metedata.object)
    {
        animation((QWidget*)metedata.object);
        qDebug() << "metedata.object:" << metedata.object->objectName();
    }
}

void PluginB::animation(QWidget *widget)
{
    QPropertyAnimation *pScaleAnimation = new QPropertyAnimation(widget, "geometry");
    pScaleAnimation->setDuration(1000);
    pScaleAnimation->setStartValue(QRect(0, 0, 0, 0));
    pScaleAnimation->setEndValue(QRect(100, 100, 200, 200));
    pScaleAnimation->start();
}

void PluginB::bindVar(QMap<int, QVector<QString> > &)
{

}
