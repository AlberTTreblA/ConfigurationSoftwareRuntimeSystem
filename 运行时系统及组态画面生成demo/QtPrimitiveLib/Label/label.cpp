#include "label.h"

Label::Label(QWidget *parent, QString text, int x, int y, int w, int h):
    QWidget(parent)
{
    label = new QLabel(this);
    label->setGeometry(QRect(x, y, w, h));
    label->setText(text);
}

Label::~Label()
{}

void Label::setText(QString s)
{
    label->setText(s);
}
