#ifndef WIDGET_H
#define WIDGET_H

//#include <QWidget>

#include <QMainWindow>

#include "addmastersdialog.h"
#include "mytcpclient.h"

#include <QTimer>

#include <QTcpSocket>
#include <QTcpServer>
#include <QList>

#include <QThread>
#include "w_heighth_thread.h"

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

     void updateMastersPlainText();
     void updateMlabels();
     void run_waterpump();

private slots:

//    void newConnection();
//    void updateValueForTcpClient();


    void on_btnResetWaterHeight_clicked();
    void on_btnStartPump_clicked();

    void slotWaterHeightChanged();

    void slotShowMasters();
    void slotSaveMasterSettings(QMap<QString, QVector<QString>>);
    void slotCancelMasterSettings();

    void on_btnConnectToMaster_clicked();
    void on_btnAddMaster_clicked();

    void slotReceivedData(QString);   //更新M区数据后，发出updateMlabels信号，调用slotUpdateMlabels更新显示
    void slotUpdateMlabels();


private:
    void updateWaterHeightShow();
    void sendWaterHeight();

    void updateMArea(QString msg);

    Ui::Widget *ui;

    //水泵相关
    w_heighth_thread *wh_thread;
    QThread *mythread_pumpHeight;

    //控制器相关
    AddMastersDialog *addMastersDialog = NULL;
    QMap<QString, QVector<QString>> masters;
    MyTcpClient* myclient=NULL;

    bool flagM1 = false;

private:
    

protected:


};

#endif // WIDGET_H
