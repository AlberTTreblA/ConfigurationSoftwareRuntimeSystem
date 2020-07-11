#ifndef WIDGET_H
#define WIDGET_H

//#include <QWidget>

#include <QMainWindow>
#include "w_consumption_thread.h"
#include "w_heighth_thread.h"
#include "waterpump_painter.h"
#include "water_subwidget.h"

#include "gen_capacity_thread.h"
#include "gen_painter.h"
#include "gen_temperature_thread.h"
#include "gen_subwidget.h"

#include "turbine_subwidget.h"
#include "tur_consumption_thread.h"
#include "tur_painter.h"
#include "tur_rotation_thread.h"

#include "myserver.h"

#include "addcontrollersdialog.h"
#include "mytcpclient.h"

#include <QThread>
#include <QEvent>
#include <QPainter>
#include <QPen>

#include <QTimer>

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
    void waterpump_start();
      //void waterpump_controlfalse(int w_controler1);
    // void waterpump_stop();
     void run_waterpump();\
     void run_gen();
     void run_tur();
     void updateControllersPlainText();

private slots:
//    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();
    void w_start_slots();
    void w_stop_slots();
    void waterpump_update();
    void w_show();
    void w_hide();
    void subw_show();
    //void diaw_show();

    void gen_start_slots();
    void gen_stop_slots();
    void gen_update();
    void gen_show();
    void gen_hide();
    void gen_showedit();

    void tur_start_slots();
    void tur_stop_slots();
    void tur_update();
    void tur_show();
    void tur_hide();
    void tur_showedit();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    //水泵液面高度报警相关
    void on_btnSetAlarmHeight_clicked();
    void on_btnUnsetAlarmHeight_clicked();

    //水泵液面高度curvechart相关
    void addDataForCurvechart();
    void on_ckShowHLine_stateChanged(int arg1);
    void on_ckShowPoint_stateChanged(int arg1);
    void on_ckShowPointBg_stateChanged(int arg1);
//	void on_btnSetData_clicked();
    void on_btnAddData_clicked();
    void on_btnClearData_clicked();

    //水泵液面高度roundplot相关
    void addDataForRoundplot();
    void on_btnLoadRoundplotData_clicked();

    //水泵液面高度lednumber相关
    void updateValueForLednumber();
    void on_btnLednumber_clicked();

    //水泵液面高度barruler相关
    void updateValueForBarruler();
    void on_btnBarruler_clicked();

    //tcp、开关相关
    void on_btnSwitch_clicked();
//    void newConnection();
    void updateValueForTcpClient();

    //液面高度报警相关
    void heightAlarm();

    //添加控制器相关
    void on_btnAddControllers_clicked();
    void slotShowControllers();
    void slotSaveControllerSettings(QMap<QString, QVector<QString>>);
    void slotCancelControllerSettings();
    void on_btnM1_clicked();
    void on_btnM2_clicked();
    void on_btnM3_clicked();
    //tcp client, connnect and send to controllers
    void on_btnConnectAndSend_clicked();
    void slotSendToControllers();

private:
    Ui::Widget *ui;

    w_consumption_thread *w_thread;
    QThread *mythread_1;
    w_heighth_thread *wh_thread;
    QThread *mythread_2;
    waterpump_painter paint;
    water_subwidget w_sub;

    gen_capacity_thread *gc_thread;
    gen_temperature_thread *gt_thread;
    QThread *mythread_3;
    QThread *mythread_4;
    gen_painter g_painter;

    tur_consumption_thread *tc_thread;
    tur_rotation_thread *tr_thread;
    QThread *mythread_5;
    QThread *mythread_6;
    tur_painter t_painter;

    //curvechart,roundplot,lednumber,barruler显示控制定时器
    QTimer *curvechartTimer;
    QTimer *roundplotTimer;
    QTimer *lednumberTimer;
    QTimer *barrulerTimer;

    QTimer *tcpSocketTimer;
//    QTcpServer server;
////    QTcpSocket *tcpSocket;
//    QList<QTcpSocket*> tcpclientsocketlist;
//    int MAX_CONNECTED_NUM;        //最大连接数
//    int oldest;                  //队列元素数量达到最大值时，最早入队的元素位置；
    myServer* server;

    //水泵液面高度报警
    int alarmHeight = -1;
    QTimer* alarmHeightTimer = NULL;

    //控制器相关
    AddControllersDialog *addControllersDialog = NULL;
    QMap<QString, QVector<QString>> controllers;
    MyTcpClient* myclient;
    QTimer *tcpClientTimer=NULL;


private:
    

protected:
    void paintEvent(QPaintEvent *);

};

#endif // WIDGET_H
