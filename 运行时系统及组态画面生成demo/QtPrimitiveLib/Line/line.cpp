#include "line.h"

Line::Line(QWidget *parent, QString* v, int x, int y, int w, int h) :
    QWidget(parent)
{
    val = v;
    lineEdit = new QLineEdit(this);
    lineEdit->setEnabled(false);
    lineEdit->setObjectName(QStringLiteral("lineEdit_TurbineRotation"));
    lineEdit->setGeometry(QRect(x, y, w, h));

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValueForLineEdit()));
    timer->start();

}

Line::~Line()
{}

void Line::updateValueForLineEdit()
{
//    static QString s("1");
    if( val==nullptr )
    {
        lineEdit->setText("null");
    }
    else
    {
        lineEdit->setText(*val);
    }
//    s = QString::number(s.toInt() + 1);
}
