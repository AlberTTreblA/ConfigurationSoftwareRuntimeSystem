#include "tur_painter.h"

tur_painter::tur_painter(QWidget *parent) : QWidget(parent)
{
m_nTimerId=startTimer(100);
}

tur_painter::~tur_painter()
{
    if(m_nTimerId!=0)
        killTimer(m_nTimerId);
}

void tur_painter::paintEvent(QPaintEvent *)
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
                rw_tur_consumption.lockForRead();
                rw_tur_rotation.lockForRead();
                int average=(tur_consumption+tur_rotation)/2;
                rw_tur_rotation.unlock();
                rw_tur_consumption.unlock();
                if(average<50)
                p.fillRect(1,1,w-2,h-2,Qt::blue);
                else if(average<70)
                    p.fillRect(1,1,w-2,h-2,Qt::yellow);
                else if (average<100)
                    p.fillRect(1,1,w-2,h-2,Qt::darkRed);


}
void tur_painter::timerEvent(QTimerEvent *)
{
    update();
    emit tur_update();
}
