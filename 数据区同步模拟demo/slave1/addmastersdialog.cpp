#include "addmastersdialog.h"
#include "ui_addmastersdialog.h"
#include <QDebug>
#include <QRegExp>
#include <QMessageBox>
#include <stdio.h>

AddMastersDialog::AddMastersDialog(QWidget *parent, QMap<QString, QVector<QString>> c) :
    QDialog(parent), masters(c), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->widget_addMaster->hide();
    updateItemForComobox();

    this->setWindowTitle("Add Controllers");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(slotButtonBox_OK()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(slotButtonBox_Cancel()));

    connect(ui->buttonBox_2, SIGNAL(accepted()), this, SLOT(slotButtonBox2_OK()));
    connect(ui->buttonBox_2, SIGNAL(rejected()), this, SLOT(slotButtonBox2_Cancel()));

}

AddMastersDialog::~AddMastersDialog()
{
    delete ui;
}


void AddMastersDialog::on_btnAddMaster_clicked()
{
    ui->lineEdit_Name->setText("0");
    ui->lineEdit_IP->setText("127.0.0.1");
    ui->lineEdit_Port->setText("8080");
    ui->widget_addMaster->show();
}

void AddMastersDialog::on_btnDelMaster_clicked()
{
    QString text = ui->comboBox_masters->currentText();

    int ret_water= QMessageBox::question(this, "deleteMaster", QString("are you sure to Master %1?").arg(text));
    switch (ret_water) {
        case QMessageBox::Yes:
           {
                masters.remove(text);
                updateItemForComobox();
           }
            break;
        case QMessageBox::No:
            break;
        default:
            break;
    }
}

void AddMastersDialog::slotButtonBox_OK()
{
    emit saveMasterSettings(masters);
}

void AddMastersDialog::slotButtonBox_Cancel()
{
    emit cancelMasterSettings();
}

void AddMastersDialog::slotButtonBox2_OK()
{


    bool ok=false;
    int port = ui->lineEdit_Port->text().toInt(&ok, 10);
    QString ip = ui->lineEdit_IP->text();
    QString name = ui->lineEdit_Name->text();
    bool ok2 = isIPaddress( ip );

    if( name==NULL || !ok || !ok2 || port<0 || port>65535 ){
        QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("输入不合法"));
//        QMessageBox::information(this, tr("错误"), tr("输入不合法"));
        ui->lineEdit_IP->clear();
        ui->lineEdit_Port->clear();
        ui->lineEdit_Name->clear();
        return;
    }

    masters[name] = QVector<QString>({ip, QString::number(port), "0"});
    updateItemForComobox();
    ui->widget_addMaster->hide();
    ui->lineEdit_IP->clear();
    ui->lineEdit_Port->clear();
    ui->lineEdit_Name->clear();
    return;
}

void AddMastersDialog::slotButtonBox2_Cancel()
{
    ui->widget_addMaster->hide();
    ui->lineEdit_IP->clear();
    ui->lineEdit_Port->clear();
    ui->lineEdit_Name->clear();
}

bool AddMastersDialog::isIPaddress(QString ip)
{
    QRegExp rx("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");

    if( !rx.exactMatch(ip) )

    {
          return false;
    }

    return true;
}

void AddMastersDialog::on_btnPrint_clicked()
{
    QMap<QString, QVector<QString>>::iterator i;
    for (i = masters.begin(); i != masters.end(); ++i) {     //i,j脠芦脢鹿脫脙const_iterator脢鹿脫脙脢卤禄谩路垄脡煤麓铆脦贸
        printf("%s: ", i.key().toStdString().data());
        QVector<QString>::iterator j;
        for(j = masters[i.key()].begin();  j != masters[i.key()].end(); ++j)
            printf("%s ", j->toStdString().data());
        printf("\n");
    }
    fflush(stdout);
}

void AddMastersDialog::updateItemForComobox()
{
    ui->comboBox_masters->clear();
    QMap<QString, QVector<QString>>::const_iterator i;
    for (i = masters.constBegin(); i != masters.constEnd(); ++i) {
        ui->comboBox_masters->addItem(i.key());
    }
}

