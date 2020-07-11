#include "turbine_subwidget.h"

turbine_subwidget::turbine_subwidget(QWidget *parent) : QWidget(parent)
{

}

turbine_subwidget::~turbine_subwidget()
{

}

void turbine_subwidget::enterEvent(QEvent *)
{

    emit show_turtest();
}
void turbine_subwidget::leaveEvent(QEvent *)
{
    emit hide_turtest();
}
void turbine_subwidget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
        emit show_turedit();

}
