#ifndef LINE_H
#define LINE_H

#include <QWidget>
#include <QTimer>
#include <QLineEdit>

class Line : public QWidget
{
    Q_OBJECT
public:
    Line(QWidget *parent = 0, QString* v=nullptr, int x=0, int y=0, int w=100, int h=20);
    ~Line();

public slots:
    void updateValueForLineEdit();

private:
    QLineEdit *lineEdit;
    QTimer *timer;
    QString *val=nullptr;

};

#endif // LINE_H
