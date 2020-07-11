#ifndef WIDGET_H
#define WIDGET_H

//#include <QWidget>

#include <QMainWindow>

#include "addmastersdialog.h"
#include "mytcpclient.h"
#include "gen_temperature_thread.h"

#include <QTimer>
#include <QThread>
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
     void run_gentemp();
     void updateMastersPlainText();
     void updateMlabels();

private slots:

//    void newConnection();
//    void updateValueForTcpClient();

    void slotTempChanged();

    void slotShowMasters();
    void slotSaveMasterSettings(QMap<QString, QVector<QString>>);
    void slotCancelMasterSettings();

    void on_btnResetGenTemp_clicked();
    void on_btnStartGen_clicked();
    void on_btnChangeAndSend_clicked();
    void on_btnConnectToMaster_clicked();
    void on_btnAddMaster_clicked();

    void slotReceivedData(QString);   //����M�����ݺ󣬷���updateMlabels�źţ�����slotUpdateMlabels������ʾ
    void slotUpdateMlabels();


private:
    void updateGenTempShow();
    void sendGenTemp();

    void updateMArea(QString msg);

    Ui::Widget *ui;

    //��������
    gen_temperature_thread *gen_thread;
    QThread *mythread_gen;

    //���������
    AddMastersDialog *addMastersDialog = NULL;
    QMap<QString, QVector<QString>> masters;
    MyTcpClient* myclient=NULL;

    bool flagM3 = false;

private:
    

protected:


};

#endif // WIDGET_H
