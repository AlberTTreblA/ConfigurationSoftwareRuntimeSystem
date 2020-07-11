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
    void on_btnCancelAlarm_clicked();

    void on_btnStartMaster_clicked();

    void slotSynchroDate();

    void slotClientConnected(QString);
    void slotClientDisconnected(QString);

    void slotReceivedDate(QString);

private:
    void resetSlavePlaintText();
    void resetMPlainText();
    void processReceivedData(QString);


    Ui::Widget *ui;

    QTimer *synchroTimer;

    MyServer* server;

    QMap<QString, QVector<QString>> controllers;
    QTimer *tcpClientTimer=NULL;

private:
    QList<QString> clientIPAdress;
    int alarmWaterHeightValue = 50;
    int alarmRotSpeedValue = 50;
    int alarmGenTempValue = 50;

    void checkAlarm();

protected:


};

#endif // WIDGET_H
