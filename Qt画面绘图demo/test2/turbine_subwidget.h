#ifndef TURBINE_SUBWIDGET_H
#define TURBINE_SUBWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>

class turbine_subwidget : public QWidget
{
    Q_OBJECT
public:
    explicit turbine_subwidget(QWidget *parent = 0);
    ~turbine_subwidget();

signals:
    void show_turtest();
    void hide_turtest();
    void show_turedit();

public slots:
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *ev);
};

#endif // TURBINE_SUBWIDGET_H
