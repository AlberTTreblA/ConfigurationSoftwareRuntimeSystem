#include "gen_painter.h"

gen_painter::gen_painter(QWidget *parent) : QWidget(parent)
{
 m_timer=startTimer(1000);
}

gen_painter::~gen_painter()
{
  if(m_timer!=0)
      killTimer(m_timer);
}

void gen_painter::paintEvent(QPaintEvent *)
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
                rw_gen_capacitu.lockForRead();
                rw_gen_temperature.lockForRead();
                int average=(gen_capacity+gen_temperature)/2;
                rw_gen_temperature.unlock();
                rw_gen_capacitu.unlock();
                if(average<50)
                p.fillRect(1,1,w-2,h-2,Qt::blue);
                else if(average<70)
                    p.fillRect(1,1,w-2,h-2,Qt::yellow);
                else if (average<100)
                    p.fillRect(1,1,w-2,h-2,Qt::darkRed);
}
void gen_painter::timerEvent(QTimerEvent *)
{
    update();
    emit gen_update();
}
