#include "line.h"
#include <QLineEdit>

Line::Line(QWidget *parent):
    QWidget(parent)
{
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setEnabled(false);
    lineEdit->setObjectName(QStringLiteral("lineEdit_TurbineRotation"));
    lineEdit->setGeometry(QRect(170, 80, 113, 21));

}
