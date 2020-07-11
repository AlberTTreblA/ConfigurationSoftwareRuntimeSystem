#ifndef ALARM_H
#define ALARM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
#include "label.h"
#include "hled.h"


class Alarm : public QWidget
{
    Q_OBJECT
public:
    Alarm(QWidget *parent = 0, QString s=" ", QString *val=nullptr, int x=200, int y=0);
    ~Alarm();

public slots:
    void button_clicked();
    void alarm();

private:
    HLed *led;
    QPushButton *button;
    Label *label;
    QLineEdit *lineEdit;
    QTimer *timer;
    QString *monitoredObj;
    QString keyWord;
};

#endif // ALARM_H
