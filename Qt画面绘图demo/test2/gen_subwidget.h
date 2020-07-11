#ifndef GEN_SUBWIDGET_H
#define GEN_SUBWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>

class gen_subwidget : public QWidget
{
    Q_OBJECT
public:
    explicit gen_subwidget(QWidget *parent = 0);
    ~gen_subwidget();

signals:
     void show_gentest();
     void hide_gentest();
     void show_genedit();
public slots:
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *ev);

};

#endif // GEN_SUBWIDGET_H
