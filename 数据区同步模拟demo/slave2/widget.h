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
#include "tur_rotation_thread.h"

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
    void run_turbine();

    void updateMastersPlainText();
    void updateMlabels();

private slots:

//    void newConnection();
//    void updateValueForTcpClient();

    void slotRotSpeedChanged();


    void slotShowMasters();
    void slotSaveMasterSettings(QMap<QString, QVector<QString>>);
    void slotCancelMasterSettings();

    void on_btnResetTurRotation_clicked();
    void on_btnStartTurbine_clicked();
    void on_btnConnectToMaster_clicked();
    void on_btnAddMaster_clicked();

    void slotReceivedData(QString);   //更新M区数据后，发出updateMlabels信号，调用slotUpdateMlabels更新显示
    void slotUpdateMlabels();


private:

    void updateRotSpeedShow();
    void sendRotSpeed();

    void updateMArea(QString msg);

    Ui::Widget *ui;

    //汽轮机相关
    tur_rotation_thread *tur_thread;
    QThread *mythread_tur;

    //控制器相关
    AddMastersDialog *addMastersDialog = NULL;
    QMap<QString, QVector<QString>> masters;
    MyTcpClient* myclient=NULL;

    bool flagM1 = false;

private:
    

protected:


};

#endif // WIDGET_H
