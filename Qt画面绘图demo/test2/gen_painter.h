#ifndef GEN_PAINTER_H
#define GEN_PAINTER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <qevent.h>
#include <QBrush>
#include "global.h"

class gen_painter : public QWidget
{
    Q_OBJECT
public:
    explicit gen_painter(QWidget *parent = 0);
    ~gen_painter();

signals:
    void gen_update();

public slots:
protected:
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);
    int m_timer;


};

#endif // GEN_PAINTER_H
