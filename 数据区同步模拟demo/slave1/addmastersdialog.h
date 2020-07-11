#ifndef ADDMASTERSDIALOG_H
#define ADDMASTERSDIALOG_H

#include <QDialog>
#include <QString>
#include <QMap>
#include <QVector>

namespace Ui {
class Dialog;
}

class AddMastersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMastersDialog(QWidget *parent = 0, QMap<QString, QVector<QString>> c= QMap<QString, QVector<QString>>());
    ~AddMastersDialog();
    bool isIPaddress(QString);
    void updateItemForComobox();

signals:
    void saveMasterSettings(QMap<QString, QVector<QString>>);
    void cancelMasterSettings();

public slots:

    void on_btnAddMaster_clicked();
    void on_btnDelMaster_clicked();

    void slotButtonBox_OK();
    void slotButtonBox_Cancel();

    void slotButtonBox2_OK();
    void slotButtonBox2_Cancel();

    void on_btnPrint_clicked();

private:

    QMap<QString, QVector<QString>> masters; //QVector:IP,Port,Mµ„–Ú∫≈ "0 1 2"
    Ui::Dialog *ui;
};


#endif // ADDMASTERSDIALOG_H
