#ifndef ADDCONTROLLERSDIALOG_H
#define ADDCONTROLLERSDIALOG_H

#include <QDialog>
#include <QString>
#include <QMap>
#include <QVector>

namespace Ui {
class Dialog;
}

class AddControllersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddControllersDialog(QWidget *parent = 0, QMap<QString, QVector<QString>> c= QMap<QString, QVector<QString>>());
    ~AddControllersDialog();
    bool isIPaddress(QString);
    void setCurrentController(QString);
    void updateItemForComobox();

signals:
    void saveControllerSettings(QMap<QString, QVector<QString>>);
    void cancelControllerSettings();

public slots:

    void on_btnAddController_clicked();
    void on_btnDelController_clicked();

    void slotButtonBox_OK();
    void slotButtonBox_Cancel();

    void slotButtonBox2_OK();
    void slotButtonBox2_Cancel();

    void on_btnPrint_clicked();

private:
    QString currentController;
    QMap<QString, QVector<QString>> controllers; //QVector:IP,Port,Mµ„–Ú∫≈ "0 1 2"
    Ui::Dialog *ui;
};


#endif // ADDCONTROLLERSDIALOG_H
