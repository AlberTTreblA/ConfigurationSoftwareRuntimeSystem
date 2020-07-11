#ifndef TUR_PAINTER_H
#define TUR_PAINTER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <qevent.h>
#include <QBrush>
#include "global.h"

class tur_painter : public QWidget
{
    Q_OBJECT
public:
    explicit tur_painter(QWidget *parent = 0);
    ~tur_painter();

signals:
    void tur_update();

public slots:
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    int m_nTimerId;
};

#endif // TUR_PAINTER_H
