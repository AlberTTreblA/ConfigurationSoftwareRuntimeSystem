#include "alarm.h"

Alarm::Alarm(QWidget *parent, QString s, QString *val, int x, int y):
    QWidget(parent)
{
    keyWord = s;
    monitoredObj = val;

    label = new Label(this, "", x, y, 150, 20);
    QString temp = QString::fromLocal8Bit("当前") + keyWord\
            + QString::fromLocal8Bit("报警阈值：");
    label->setText(temp);

    led = new HLed(this);
    led->setGeometry(QRect(x, y+20, 91, 80));

    lineEdit = new QLineEdit(this);
    lineEdit->setGeometry(QRect(x, y+100, 150, 25));

    button = new QPushButton(this);
    button->setGeometry(QRect(x, y+125, 150, 25));
    button->setText(QString::fromLocal8Bit("设置报警阈值"));

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(alarm()));
    timer->start();

    connect(button, &QPushButton::clicked, this, &Alarm::button_clicked);
}

Alarm::~Alarm()
{}

void Alarm::button_clicked()
{
    QString s = QString::fromLocal8Bit("当前") + keyWord\
            + QString::fromLocal8Bit("报警阈值：%1").arg(lineEdit->text());
    label->setText(s);
    led->setThred(lineEdit->text());
}

void Alarm::alarm()
{
    if( monitoredObj==nullptr )
    {
        return;
    }
    led->alarm(*monitoredObj);
}






