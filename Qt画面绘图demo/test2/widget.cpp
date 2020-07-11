#include "widget.h"
#include "ui_widget.h"
#include "global.h"
#include <QMovie>
#include <QString>
#include <QDebug>
#include <qmath.h>
#include <QString>
#include <QDialog>
//#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <stdio.h>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

Widget::Widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Widget)
{

    QMenuBar *mbar=menuBar();
    setMenuBar(mbar);
    QMenu *menu=mbar->addMenu("错误处理");
    QAction *a1=menu->addAction("重新设置水泵");
    QAction *a2=menu->addAction("重新设置发电机");
    QAction *a3=menu->addAction("重新设置汽轮机");

    connect(a1,&QAction::triggered,
            [=]()
            {

                int ret_water= QMessageBox::question(this,"waterpump","are you sure to change waterpump");
                switch (ret_water) {
                case QMessageBox::Yes:
                   {
                    waterpump_consumption_rw.lockForWrite();
                    waterpump_consumption=0;
                    waterpump_consumption_rw.unlock();

                    waterpump_heighth_rw.lockForWrite();
                    waterpump_heighth=0;
                    waterpump_heighth_rw.unlock();

                   }
                    break;
                case QMessageBox::No:
                    qDebug()<<"no";
                    break;
                default:
                    break;
                }

            }

            );
    connect(a2,&QAction::triggered,
            [=]()
            {
              //QMessageBox::about(this,"dia1","关于第一个")
               int ret_gen= QMessageBox::question(this,"gen","are you sure to change gen");
               switch (ret_gen) {
               case QMessageBox::Yes:
               {
                   rw_gen_capacitu.lockForWrite();
                   gen_capacity=0;
                   rw_gen_capacitu.unlock();

                   rw_gen_temperature.lockForWrite();
                   gen_temperature=0;
                   rw_gen_temperature.unlock();
               }
                   break;
               case QMessageBox::No:
                   qDebug()<<"no";
                   break;
               default:
                   break;

               }
            }
            );
    connect(a3,&QAction::triggered,
            [=]()
            {
                  //QMessageBox::about(this,"dia1","关于第一个")
                   int ret_turbine= QMessageBox::question(this,"gen","are you sure to change turbine");
                   switch (ret_turbine) {
                   case QMessageBox::Yes:
                   {
                       rw_tur_rotation.lockForWrite();
                       tur_rotation=0;
                       rw_tur_rotation.unlock();

                       rw_tur_consumption.lockForWrite();
                       tur_consumption=0;
                       rw_tur_consumption.unlock();
                   }
                       break;
                   case QMessageBox::No:
                       qDebug()<<"no";
                       break;
                   default:
                       break;

                   }
            }
            );

    /*
     * 下面是对主界面样式的设置
     */
    ui->setupUi(this);
    QMovie *movie1=new QMovie("../shuibeng.gif");
    ui->label->setMovie(movie1);
    ui->label->setScaledContents(true);
    movie1->start();
    QMovie *movie2=new QMovie("../fadian.gif");
    ui->label_13->setMovie(movie2);
    ui->label_13->setScaledContents(true);
    movie2->start();

    //按钮颜色设置
    ui->textEdit->setStyleSheet("background:lightgrey");
    ui->pushButton->setStyleSheet("background:green");
    ui->pushButton_2->setStyleSheet("background:red");
    ui->textEdit_2->setStyleSheet("background:lightgrey");
    ui->pushButton_7->setStyleSheet("background:green");
    ui->pushButton_8->setStyleSheet("background:red");
    ui->textEdit_4->setStyleSheet("background:lightgrey");
    ui->pushButton_3->setStyleSheet("background:green");
    ui->pushButton_4->setStyleSheet("background:red");

    //初始隐藏
    ui->textEdit->hide();
    ui->widget_9->hide();
    ui->textEdit_2->hide();
    ui->widget_10->hide();
    ui->textEdit_4->hide();
    ui->widget_11->hide();

    //subwidget控制窗口弹出
    connect(ui->widget,SIGNAL(show_water()),this,SLOT(w_show()));
    connect(ui->widget,SIGNAL(hide_water()),this,SLOT(w_hide()));
    connect(ui->widget,SIGNAL(show_subwater()),this,SLOT(subw_show()));

    connect(ui->widget_7,SIGNAL(show_genedit()),this,SLOT(gen_showedit()));
    connect(ui->widget_7,SIGNAL(show_gentest()),this,SLOT(gen_show()));
    connect(ui->widget_7,SIGNAL(hide_gentest()),this,SLOT(gen_hide()));
    //
    connect(ui->widget_3,SIGNAL(show_turedit()),this,SLOT(tur_showedit()));
    connect(ui->widget_3,SIGNAL(show_turtest()),this,SLOT(tur_show()));
    connect(ui->widget_3,SIGNAL(hide_turtest()),this,SLOT(tur_hide()));

    /*
     * 下面是对线程的设置
     */
    w_thread=new w_consumption_thread;
    mythread_1=new QThread(this);
    w_thread->moveToThread(mythread_1);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(w_start_slots()));
    mythread_1->start();
//    mythread_2->start();
    connect(this,&Widget::run_waterpump,w_thread,&w_consumption_thread::my_consuomption);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(w_stop_slots()));

    //这是水泵的液面
    wh_thread=new w_heighth_thread;
    mythread_2=new QThread(this);
    wh_thread->moveToThread(mythread_2);
    mythread_2->start();
    connect(this,&Widget::run_waterpump,wh_thread,&w_heighth_thread::my_height);

    //这是发电机的功率
    gc_thread=new gen_capacity_thread;
    mythread_3=new QThread(this);
    gc_thread->moveToThread(mythread_3);
    mythread_3->start();
    connect(this,&Widget::run_gen,gc_thread,&gen_capacity_thread::my_capacity);
    //这是发电机的温度
    gt_thread=new gen_temperature_thread;
    mythread_4=new QThread(this);
    gt_thread->moveToThread(mythread_4);
    mythread_4->start();
    connect(this,&Widget::run_gen,gt_thread,&gen_temperature_thread::my_temperature);

    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(gen_start_slots()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(gen_stop_slots()));

    //这是汽轮机转速
    tr_thread=new tur_rotation_thread;
    mythread_5=new QThread(this);
    tr_thread->moveToThread(mythread_5);
    mythread_5->start();
    connect(this,&Widget::run_tur,tr_thread,&tur_rotation_thread::my_rotation);
    //这是汽轮机功耗
    tc_thread=new tur_consumption_thread;
    mythread_6=new QThread(this);
    tc_thread->moveToThread(mythread_6);
    mythread_6->start();
    connect(this,&Widget::run_tur,tc_thread,&tur_consumption_thread::my_consumption);

    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(tur_start_slots()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(tur_stop_slots()));
    /*
     * 下面是定时器更新主页面上的值
     */
    connect(&paint,&waterpump_painter::waterpump_update,this,&Widget::waterpump_update);
    connect(&g_painter,&gen_painter::gen_update,this,&Widget::gen_update);
    connect(&t_painter,&tur_painter::tur_update,this,&Widget::tur_update);

   //设置定时器刷新curvechart数据
    curvechartTimer = new QTimer(this);
    curvechartTimer->setInterval(1000);
    connect(curvechartTimer, SIGNAL(timeout()), this, SLOT(addDataForCurvechart()));

    //设置定时器刷新roundplot数据
     roundplotTimer = new QTimer(this);
     roundplotTimer->setInterval(3000);
     connect(roundplotTimer, SIGNAL(timeout()), this, SLOT(addDataForRoundplot()));
     
     //设置定时器刷新lednumber数据
     lednumberTimer = new QTimer(this);
     lednumberTimer->setInterval(2000);
     connect(lednumberTimer, SIGNAL(timeout()), this, SLOT(updateValueForLednumber()));

     //设置定时器刷新barruler数据
     barrulerTimer = new QTimer(this);
     barrulerTimer->setInterval(2000);
     connect(barrulerTimer, SIGNAL(timeout()), this, SLOT(updateValueForBarruler()));

//     //设置最大监听数量
//     MAX_CONNECTED_NUM = 2;
//     oldest = 0;
//     //服务器监听设置
//     server.listen(QHostAddress::Any,8080);
//     connect(&server,SIGNAL(newConnection()),this,SLOT(newConnection()));
     server = new myServer(0, 8080);
     //设置定时器向客户端输出开关值
     tcpSocketTimer = new QTimer(this);
     tcpSocketTimer->setInterval(1000);
     connect(tcpSocketTimer, SIGNAL(timeout()), this, SLOT(updateValueForTcpClient()));
     tcpSocketTimer->start();

}

Widget::~Widget()
{
    mythread_1->terminate();
    mythread_1->quit();
    mythread_1->wait();

    mythread_2->terminate();
    mythread_2->quit();
    mythread_2->wait();

    mythread_3->terminate();
    mythread_3->quit();
    mythread_3->wait();

    mythread_4->terminate();
    mythread_4->quit();
    mythread_4->wait();

    mythread_5->terminate();
    mythread_5->quit();
    mythread_5->wait();

    mythread_6->terminate();
    mythread_6->quit();
    mythread_6->wait();

    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPen pen;
    pen.setWidth(3);
    p.setPen(pen);
    p.drawLine(70,320,70,360);
//     p.drawLine(40,320,40,360);
    //  p.drawLine(0,360,40,360);
       p.drawLine(70,360,350,360);
       p.drawLine(350,360,350,320);
       p.drawLine(380,360,380,320);
      // p.drawLine(350,360,380,360);
         p.drawLine(660,360,380,360);
           p.drawLine(660,360,660,320);
//           p.drawLine(690,360,690,320);
//           QVector <qreal> dashes;
//           qreal space = 3;
//           dashes << 5 << space << 5 <<space;
//           pen.setDashPattern(dashes);
           pen.setStyle(Qt::DotLine);
           p.setPen(pen);
           p.drawLine(0,360,40,360);
            p.drawLine(40,320,40,360);
             p.drawLine(690,360,690,320);
             p.drawLine(690,360,800,360);


}
void Widget::tur_start_slots()
{
    emit run_tur();
     mythread_5->start();
    mythread_6->start();
}
void Widget::tur_stop_slots()
{
    mythread_5->terminate();
    mythread_6->terminate();
}
void Widget::tur_update()
{
    int tur_max;
    rw_tur_consumption.lockForRead();
    rw_tur_rotation.lockForRead();
    tur_max=qMax(tur_consumption,tur_rotation);
    rw_tur_rotation.unlock();
    rw_tur_consumption.unlock();
    if(tur_max<50)
    ui->label_8->setText("正常");
    else if(tur_max<70)
        ui->label_8->setText("良好");
    else if(tur_max<100)
        ui->label_8->setText("超负荷");
    QString tur_s=QString("汽轮机""\r当前压力：""%1""\r当前转速：""%2").arg(QString::number(tur_consumption)).arg(QString::number(tur_rotation));
    ui->textEdit_4->setText(tur_s);

}
void Widget::tur_hide()
{
    ui->textEdit_4->hide();
}
void Widget::tur_show()
{
    ui->textEdit_4->show();
}
void Widget::tur_showedit()
{
     ui->widget_11->show();
}
void Widget::gen_hide()
{
     ui->textEdit_2->hide();
}
void Widget::gen_show()
{
     ui->textEdit_2->show();
}
void Widget::gen_showedit()
{
    ui->widget_10->show();
}
void Widget::gen_update()
{
    int gen_max;
    rw_gen_capacitu.lockForRead();
    rw_gen_temperature.lockForRead();
    gen_max=qMax(gen_capacity,gen_temperature);
    rw_gen_temperature.unlock();
    rw_gen_capacitu.unlock();
    if(gen_max<50)
    ui->label_16->setText("正常");
    else if(gen_max<70)
        ui->label_16->setText("良好");
    else if(gen_max<100)
        ui->label_16->setText("超负荷");
    QString gen_s=QString("发电机""\r当前功率：""%1""\r当前温度：""%2").arg(QString::number(gen_capacity)).arg(QString::number(gen_temperature));
    ui->textEdit_2->setText(gen_s);

}
void Widget::gen_start_slots()
{
    emit run_gen();
     mythread_3->start();
    mythread_4->start();
    //mythread_3->start();
}
void Widget::gen_stop_slots()
{
    mythread_3->terminate();
    mythread_4->terminate();

}

void Widget::w_start_slots()
{
    emit run_waterpump();
    mythread_1->start();
    mythread_2->start();
    qDebug()<<"start";
}
void Widget::w_stop_slots()
{
    mythread_1->terminate();
    mythread_2->terminate();
     qDebug()<<"stop";
}
void Widget::waterpump_update()
{
    int water_max;
    waterpump_consumption_rw.lockForRead();
    waterpump_heighth_rw.lockForRead();
     water_max=qMax(waterpump_consumption,waterpump_heighth);
    waterpump_heighth_rw.unlock();
    waterpump_consumption_rw.unlock();
    water_max=qMax(waterpump_consumption,waterpump_heighth);
    if(water_max<50)
    ui->label_4->setText("正常");
    else if(water_max<70)
        ui->label_4->setText("良好");
    else if(water_max<100)
        ui->label_4->setText("超负荷");
    QString water_s=QString("水泵""\r当前液高：""%1""\r当前功耗：""%2").arg(QString::number(waterpump_heighth)).arg(QString::number(waterpump_consumption));
    ui->textEdit->setText(water_s);

}
void Widget::w_hide()
{
    ui->textEdit->hide();
}
void Widget::w_show()
{
    ui->textEdit->show();
}
void Widget::subw_show()
{
    ui->widget_9->show();
}

void Widget::on_pushButton_10_clicked()
{
    ui->widget_9->hide();
}

void Widget::on_pushButton_9_clicked()
{

    if(ui->lineEdit_3->text().isEmpty()==0)
    {
        waterpump_consumption_rw.lockForWrite();
        waterpump_consumption=ui->lineEdit_3->text().toInt();
        waterpump_consumption_rw.unlock();
    }
    if(ui->lineEdit_2->text().isEmpty()==0)
    {
        waterpump_heighth_rw.lockForWrite();
        waterpump_heighth=ui->lineEdit_2->text().toInt();
        waterpump_heighth_rw.unlock();
    }
}

void Widget::on_pushButton_11_clicked()
{
    if(ui->lineEdit_4->text().isEmpty()==0)
    {
        rw_gen_capacitu.lockForWrite();
        gen_capacity=ui->lineEdit_4->text().toInt();
        rw_gen_capacitu.unlock();
    }
    if(ui->lineEdit_5->text().isEmpty()==0)
    {
        rw_gen_temperature.lockForWrite();
        gen_temperature=ui->lineEdit_5->text().toInt();
        rw_gen_temperature.unlock();
    }
}

void Widget::on_pushButton_12_clicked()
{
    ui->widget_10->hide();
}

void Widget::on_pushButton_13_clicked()
{
    if(ui->lineEdit_6->text().isEmpty()==0)
    {
        rw_tur_rotation.lockForWrite();
        tur_rotation=ui->lineEdit_6->text().toInt();
        rw_tur_rotation.unlock();
    }
    if(ui->lineEdit_7->text().isEmpty()==0)
    {
        rw_tur_consumption.lockForWrite();
        tur_consumption=ui->lineEdit_7->text().toInt();
        rw_tur_consumption.unlock();
    }
}

void Widget::on_pushButton_14_clicked()
{
    ui->widget_11->hide();
}


//curvechart相关
void Widget::addDataForCurvechart()
{
    waterpump_heighth_rw.lockForRead();
    ui->widget_chart->addData(waterpump_heighth);
    waterpump_heighth_rw.unlock();
}

void Widget::on_ckShowHLine_stateChanged(int arg1)
{
    bool show = (arg1 != 0);
    ui->widget_chart->setShowHLine(show);
}

void Widget::on_ckShowPoint_stateChanged(int arg1)
{
    bool show = (arg1 != 0);
    ui->widget_chart->setShowPoint(show);
}

void Widget::on_ckShowPointBg_stateChanged(int arg1)
{
    bool show = (arg1 != 0);
    ui->widget_chart->setShowPointBg(show);
}

//void Widget::on_btnSetData_clicked()
//{
//    if (ui->btnAddData->text() == "停止加载") {
//        on_btnAddData_clicked();
//    }

//    on_btnClearData_clicked();

//    QVector<double> data;

//    for (int i = 0; i < 10; i++) {
//        data.push_front(i * 10);
//    }

//    ui->widget_chart->setData(data);
//}

void Widget::on_btnAddData_clicked()
{
    if (ui->btnAddData->text() == "加载数据") {
        curvechartTimer->start();
        ui->btnAddData->setText("停止加载");
    } else {
        curvechartTimer->stop();
        ui->btnAddData->setText("加载数据");
    }
}

void Widget::on_btnClearData_clicked()
{
    ui->widget_chart->clearData();
}

//roundplot相关
void Widget::addDataForRoundplot()
{
    QString unit = ui->txtUnit->text();
    double minValue = ui->txtMinValue->text().toDouble();
    double maxValue = ui->txtMaxValue->text().toDouble();

    ui->widget_roundplot->setUnit(unit);
    ui->widget_roundplot->setRange(minValue, maxValue);

    waterpump_heighth_rw.lockForRead();
    ui->widget_roundplot->setValue(waterpump_heighth);
    waterpump_heighth_rw.unlock();
}

void Widget::on_btnLoadRoundplotData_clicked()
{
    if (ui->btnLoadRoundplotData->text() == "加载水泵液面高度") {
        roundplotTimer->start();
        ui->btnLoadRoundplotData->setText("停止加载水泵液面高度");
    } else {
        roundplotTimer->stop();
        ui->btnLoadRoundplotData->setText("加载水泵液面高度");
    }

}


//lednumber相关
void Widget::updateValueForLednumber()
{
    waterpump_heighth_rw.lockForRead();
    ui->widget_lednumber1->setNumber(waterpump_heighth/10);
    ui->widget_lednumber2->setNumber(waterpump_heighth%10);
    waterpump_heighth_rw.unlock();
}

void Widget::on_btnLednumber_clicked()
{
    if (ui->btnLednumber->text() == "跟踪水泵液面高度") {
        lednumberTimer->start();
        ui->btnLednumber->setText("停止跟踪水泵液面高度");
    } else {
        lednumberTimer->stop();
        ui->btnLednumber->setText("跟踪水泵液面高度");
    }    
}


//barruler相关
void Widget::updateValueForBarruler()
{
    waterpump_heighth_rw.lockForRead();
    ui->widget_barruler1->setValue(waterpump_heighth);
    ui->widget_barruler2->setValue(waterpump_heighth);
    ui->widget_barruler3->setValue(waterpump_heighth);
    waterpump_heighth_rw.unlock();
}

void Widget::on_btnBarruler_clicked()
{
    if (ui->btnBarruler->text() == "跟踪水泵液面高度") {
        barrulerTimer->start();
        ui->btnBarruler->setText("停止跟踪水泵液面高度");
    } else {
        barrulerTimer->stop();
        ui->btnBarruler->setText("跟踪水泵液面高度");
    }
}

//tcp、开关相关
void Widget::on_btnSwitch_clicked()
{
    if (ui->btnSwitch->text() == "打开开关") {
        switch_value = 1;
        ui->labelSwitchValue->setText(QString("开关变量值：%1").arg(QString::number(switch_value, 10)));
        ui->btnSwitch->setText("关闭开关");
    } else {
        switch_value = 0;
        ui->labelSwitchValue->setText(QString("开关变量值：%1").arg(QString::number(switch_value, 10)));
        ui->btnSwitch->setText("打开开关");
    }
}

//void Widget::newConnection()
//{
////    qDebug()<<"newConnection";
//    if( tcpclientsocketlist.size() < MAX_CONNECTED_NUM )
//        tcpclientsocketlist.append(server.nextPendingConnection());
//    else{
//        tcpclientsocketlist.replace(oldest%MAX_CONNECTED_NUM, server.nextPendingConnection());
//        oldest++;
//    }
//}

void Widget::updateValueForTcpClient()
{
//    qDebug()<<"updateValueForTcpClient";
    QString str=QString::number(switch_value, 10);
    QByteArray strByte = str.toLatin1();

//    if(tcpSocket)
//        tcpSocket->write(strByte);
//    for( int i=0; i<tcpclientsocketlist.size(); i++ ){
//        tcpclientsocketlist.at(i)->write(strByte);
//    }
    server->write(strByte);

}

//水泵液面高度报警相关
void Widget::heightAlarm()
{
    qDebug()<<"slot responsed:"<<alarmHeight;
    waterpump_heighth_rw.lockForRead();
    if( waterpump_heighth >= alarmHeight )
        ui->alarmLight->alarm();
    else
        ui->alarmLight->unalarm();
    waterpump_heighth_rw.unlock();
}

void Widget::on_btnSetAlarmHeight_clicked()
{
    if( ui->lineEdit_setAlarmH->text() == QString("") )
        return;
    int temp = ui->lineEdit_setAlarmH->text().toDouble();
//    qDebug()<<"temp:"<<temp;
    if( temp < 0 )
        QMessageBox::critical(0 ,
        "critical message" , "Illegal input value",
        QMessageBox::Ok | QMessageBox::Default ,
        QMessageBox::Cancel | QMessageBox::Escape , 0 );
    else if( temp >= 0 )
    {
//        qDebug()<<"temp >=0";
        alarmHeight = temp;
        ui->label_alrmH->setText(QString("当前报警液高：%1").arg(alarmHeight));
        //设置定时器定时检查液面高度决定是否报警报警
        if( alarmHeightTimer == NULL ){
            alarmHeightTimer = new QTimer(this);
            alarmHeightTimer->setInterval(1000);
            connect(alarmHeightTimer, SIGNAL(timeout()), this, SLOT(heightAlarm()));
        }
        alarmHeightTimer->start();
        qDebug()<<"btn clicked:"<<alarmHeight;        
    }

}

void Widget::on_btnUnsetAlarmHeight_clicked()
{

    ui->label_alrmH->setText("当前报警液高：");
    if( alarmHeightTimer == NULL )
        return;

    alarmHeightTimer->stop();
//    qDebug()<<"haha";

    ui->alarmLight->unalarm();
}

//添加控制器相关
void Widget::on_btnAddControllers_clicked()
{
    addControllersDialog = new AddControllersDialog(this, controllers);
    addControllersDialog->setModal(false);
    addControllersDialog->show();
    connect(addControllersDialog, &AddControllersDialog::saveControllerSettings, this, &Widget::slotSaveControllerSettings);
    connect(this, &Widget::updateControllersPlainText, this, &Widget::slotShowControllers);
    connect(addControllersDialog, &AddControllersDialog::cancelControllerSettings, this, &Widget::slotCancelControllerSettings);
}

void Widget::slotSaveControllerSettings(QMap<QString, QVector<QString>> c)
{
    controllers = c;
    delete addControllersDialog;
    addControllersDialog = NULL;
    emit updateControllersPlainText();
}

void Widget::slotShowControllers()
{
//    qDebug()<<"slotShowControllers";
    ui->plainTextEdit_controllers->clear();
    QString s;
    QMap<QString, QVector<QString>>::iterator i;
    for (i = controllers.begin(); i != controllers.end(); ++i) {   //不能用const_iterator
        s.append(i.key()).append(": \n");
//        qDebug()<<"loop1";
        QVector<QString>::iterator j;
        for(j = controllers[i.key()].begin();  j != controllers[i.key()].end(); ++j)
        {
//            qDebug()<<*j;
            s.append(*j).append(" ");
        }
        s.append("\n");
    }
    ui->plainTextEdit_controllers->setPlainText(s);
}

void Widget::slotCancelControllerSettings()
{
    delete addControllersDialog;
    addControllersDialog = NULL;
}

void Widget::on_btnM1_clicked()
{
    if (ui->btnM1->text() == "打开") {
        MPoint[0] = 1;
        ui->label_M1->setText(QString("M点1的值: %1").arg(QString::number(MPoint[0], 10)));
        ui->btnM1->setText("关闭");
    } else {
        MPoint[0] = 0;
        ui->label_M1->setText(QString("M点1的值: %1").arg(QString::number(MPoint[0], 10)));
        ui->btnM1->setText("打开");
    }
}

void Widget::on_btnM2_clicked()
{
    if (ui->btnM2->text() == "打开") {
        MPoint[1] = 3;
        ui->label_M2->setText(QString("M点2的值: %1").arg(QString::number(MPoint[1], 10)));
        ui->btnM2->setText("关闭");
    } else {
        MPoint[1] = 2;
        ui->label_M2->setText(QString("M点2的值: %1").arg(QString::number(MPoint[1], 10)));
        ui->btnM2->setText("打开");
    }
}

void Widget::on_btnM3_clicked()
{
    if (ui->btnM3->text() == "打开") {
        MPoint[2] = 5;
        ui->label_M3->setText(QString("M点3的值: %1").arg(QString::number(MPoint[2], 10)));
        ui->btnM3->setText("关闭");
    } else {
        MPoint[2] = 4;
        ui->label_M3->setText(QString("M点3的值: %1").arg(QString::number(MPoint[2], 10)));
        ui->btnM3->setText("打开");
    }
}

void Widget::on_btnConnectAndSend_clicked()
{
    if(ui->btnConnectAndSend->text() == "连接到控制器并发送数据") {
        myclient = new MyTcpClient;
        myclient->connectToHost(controllers);

        if( tcpClientTimer==NULL ){
            tcpClientTimer = new QTimer(this);
            tcpClientTimer->setInterval(3000);
            connect(tcpClientTimer, SIGNAL(timeout()), this, SLOT(slotSendToControllers()));
        }
        tcpClientTimer->start();
        ui->btnConnectAndSend->setText("断开连接");
    }
    else if(ui->btnConnectAndSend->text() == "断开连接") {
        tcpClientTimer->stop();
        myclient->disconnect();
        ui->btnConnectAndSend->setText("连接到控制器并发送数据");
    }
}

void Widget::slotSendToControllers()
{
    if( myclient->isConnected() )
        myclient->write();
}


