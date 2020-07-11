#include "waterpump_painter.h"
#include <QDebug>

waterpump_painter::waterpump_painter(QWidget *parent) : QWidget(parent)
{
 m_nTimerId=startTimer(100);
}

waterpump_painter::~waterpump_painter()
{
    if(m_nTimerId!=0)
        killTimer(m_nTimerId);
}

void waterpump_painter::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPen pen;
    pen.setWidth(1);
    p.setPen(pen);
    int h=height();
    int w=width();

          //p.fillRect(1,1,w-2,h-2,Qt::blue);
          p.drawLine(0,0,w,0);
            p.drawLine((w-1),0,(w-1),(h-1));
              p.drawLine(w,(h-1),0,(h-1));
                p.drawLine(0,h,0,0);
                waterpump_consumption_rw.lockForRead();
                waterpump_heighth_rw.lockForRead();
                int average=(waterpump_consumption+waterpump_heighth)/2;
                waterpump_heighth_rw.unlock();
                waterpump_consumption_rw.unlock();
                if(average<50)
                p.fillRect(1,1,w-2,h-2,Qt::blue);
                else if(average<70)
                    p.fillRect(1,1,w-2,h-2,Qt::yellow);
                else if (average<100)
                    p.fillRect(1,1,w-2,h-2,Qt::darkRed);




}
void waterpump_painter::timerEvent(QTimerEvent *)
{
    update();
    //qDebug()<<"ok";
    emit waterpump_update();

}
