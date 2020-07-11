#include "gen_subwidget.h"

gen_subwidget::gen_subwidget(QWidget *parent) : QWidget(parent)
{

}

gen_subwidget::~gen_subwidget()
{

}

void gen_subwidget::leaveEvent(QEvent *)
{
    emit hide_gentest();
}
void gen_subwidget::enterEvent(QEvent *)
{
    emit show_gentest();
}
void gen_subwidget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
        emit show_genedit();
}
