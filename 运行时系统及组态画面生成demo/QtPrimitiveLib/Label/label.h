#ifndef LABEL_H
#define LABEL_H

#include <QWidget>
#include <QLabel>

class Label : public QWidget
{
    Q_OBJECT
public:
    Label(QWidget *parent = 0, QString text="", int x=0, int y=0, int w=100, int h=20);
    ~Label();
    void setText(QString);

private:
    QLabel *label;

};

#endif // LABEL_H
