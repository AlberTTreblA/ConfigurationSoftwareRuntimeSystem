#ifndef WATER_SUBWIDGET_H
#define WATER_SUBWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>

class water_subwidget : public QWidget
{
    Q_OBJECT
public:
    explicit water_subwidget(QWidget *parent = 0);
    ~water_subwidget();

signals:
    void show_water();
    void hide_water();
    void show_subwater();

public slots:
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *ev);
};

#endif // WATER_SUBWIDGET_H
