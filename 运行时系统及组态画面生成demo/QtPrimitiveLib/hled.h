#ifndef HLED_H
#define HLED_H

#include <QWidget>
#include <QTimer>

class QColor;

class HLed : public QWidget
{
    Q_OBJECT
public:
    HLed(QWidget *parent = 0);
    ~HLed();

    QColor color() const;
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void setColor(const QColor &color);
    void toggle();
    void turnOn(bool on=true);
    void turnOff(bool off=true);
    void alarm(QString);
    void unalarm();
    void alarmFlicker();
    void setThred(QString);

protected:
    void paintEvent(QPaintEvent*);
    int ledWidth() const;

private:
    struct Private;
    Private * const m_d;
    QTimer *alarmTimer;
    QString alarmThred;
};

#endif // HLED_H
