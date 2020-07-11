#ifndef WIDGET_H
#define WIDGET_H

//#include <QWidget>

#include <QMainWindow>

#include "myserver.h"

#include <QTimer>
#include <QString>
#include <QTcpSocket>
#include <QTcpServer>
#include <QList>

namespace Ui {
class Widget;
}

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


signals:

     void updateSlavesPlainText();

private slots:
     void on_lineEdit_PumpH_textChanged();
     void on_lineEdit_PumpT_textChanged();
     void on_lineEdit_TurbineR_textChanged();
     void on_lineEdit_TurbineP_textChanged();

    void on_btnStartMaster_clicked();

    void slotSynchroDate();

    void slotClientConnected(QString);
    void slotClientDisconnected(QString);

    void slotReceivedDate(QString);

private:
    void resetSlavePlaintText();
    void processReceivedData(QString);


    Ui::Widget *ui;

    QTimer *synchroTimer;

    MyServer* server;

    QMap<QString, QVector<QString>> controllers;
    QTimer *tcpClientTimer=NULL;

private:
    QList<QString> clientIPAdress;

protected:


};

#endif // WIDGET_H
