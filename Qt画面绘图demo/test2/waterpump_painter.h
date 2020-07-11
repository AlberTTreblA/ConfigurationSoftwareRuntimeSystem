#ifndef WATERPUMP_PAINTER_H
#define WATERPUMP_PAINTER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <qevent.h>
#include <QBrush>
#include "global.h"
class waterpump_painter : public QWidget
{
    Q_OBJECT
public:
    explicit waterpump_painter(QWidget *parent = 0);
    ~waterpump_painter();

signals:
    void waterpump_update();

public slots:
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    int m_nTimerId;
};

#endif // WATERPUMP_PAINTER_H
