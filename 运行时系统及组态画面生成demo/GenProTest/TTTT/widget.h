#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void clickA();
    void on_btnPump_clicked();
    void on_btnTurbine_clicked();
    void on_btnSimulator_clicked();
    void on_btnRunMode_clicked();

signals:
    void startSavingData();
    void startSimulate();

private:
    Ui::Widget *ui;
    QThread* dataSaveThread = Q_NULLPTR;
    QThread* simulatorThread = Q_NULLPTR;
};

#endif // WIDGET_H
