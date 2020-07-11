#include "water_subwidget.h"

water_subwidget::water_subwidget(QWidget *parent) : QWidget(parent)
{

}

water_subwidget::~water_subwidget()
{

}

void water_subwidget::enterEvent(QEvent *)
{

    emit show_water();
}
void water_subwidget::leaveEvent(QEvent *)
{
    emit hide_water();
}
void water_subwidget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
        emit show_subwater();

}
