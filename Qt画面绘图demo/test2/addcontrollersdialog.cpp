#include "addcontrollersdialog.h"
#include "ui_addcontrollersdialog.h"
#include <QDebug>
#include <QRegExp>
#include <QMessageBox>
#include <stdio.h>

AddControllersDialog::AddControllersDialog(QWidget *parent, QMap<QString, QVector<QString>> c) :
    QDialog(parent), controllers(c), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->widget_addController->hide();
    updateItemForComobox();

    this->setWindowTitle("Add Controllers");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(slotButtonBox_OK()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(slotButtonBox_Cancel()));

    connect(ui->buttonBox_2, SIGNAL(accepted()), this, SLOT(slotButtonBox2_OK()));
    connect(ui->buttonBox_2, SIGNAL(rejected()), this, SLOT(slotButtonBox2_Cancel()));

}

AddControllersDialog::~AddControllersDialog()
{
    delete ui;
}

void AddControllersDialog::setCurrentController(const QString controller)
{
    currentController = controller;
}

void AddControllersDialog::on_btnAddController_clicked()
{
    ui->widget_addController->show();
}

void AddControllersDialog::on_btnDelController_clicked()
{
    QString text = ui->comboBox_controllers->currentText();

    int ret_water= QMessageBox::question(this, "deleteController", QString("are you sure to delete %1?").arg(text));
    switch (ret_water) {
        case QMessageBox::Yes:
           {
                controllers.remove(text);
                updateItemForComobox();
           }
            break;
        case QMessageBox::No:
            break;
        default:
            break;
    }
}

void AddControllersDialog::slotButtonBox_OK()
{
    emit saveControllerSettings(controllers);
}

void AddControllersDialog::slotButtonBox_Cancel()
{
    emit cancelControllerSettings();
}

void AddControllersDialog::slotButtonBox2_OK()
{


    bool ok=false;
    int port = ui->lineEdit_Port->text().toInt(&ok, 10);
    QString ip = ui->lineEdit_IP->text();
    QString name = ui->lineEdit_Name->text();
    bool ok2 = isIPaddress( ip );

    if( name==NULL || !ok || !ok2 || port<0 || port>65535 ){
        QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("输入不合法"));
        ui->lineEdit_IP->clear();
        ui->lineEdit_Port->clear();
        ui->lineEdit_Name->clear();
        return;
    }

    QString M;
    if( ui->checkBox_M1->isChecked() )
        M.append("0 ");
    if( ui->checkBox_M2->isChecked() )
        M.append("1 ");
    if( ui->checkBox_M3->isChecked() )
        M.append("2 ");

    controllers[name] = QVector<QString>({ip, QString::number(port), M});
    updateItemForComobox();
    ui->widget_addController->hide();
    ui->lineEdit_IP->clear();
    ui->lineEdit_Port->clear();
    ui->lineEdit_Name->clear();
    ui->checkBox_M1->setChecked(false);
    ui->checkBox_M2->setChecked(false);
    ui->checkBox_M3->setChecked(false);
    return;
}

void AddControllersDialog::slotButtonBox2_Cancel()
{
    ui->widget_addController->hide();
    ui->lineEdit_IP->clear();
    ui->lineEdit_Port->clear();
    ui->lineEdit_Name->clear();
    ui->checkBox_M1->setChecked(false);
    ui->checkBox_M2->setChecked(false);
    ui->checkBox_M3->setChecked(false);
}

bool AddControllersDialog::isIPaddress(QString ip)
{
    QRegExp rx("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");

    if( !rx.exactMatch(ip) )

    {
          return false;
    }

    return true;
}

void AddControllersDialog::on_btnPrint_clicked()
{
    QMap<QString, QVector<QString>>::iterator i;
    for (i = controllers.begin(); i != controllers.end(); ++i) {     //i,j全使用const_iterator使用时会发生错误
        printf("%s: ", i.key().toStdString().data());
        QVector<QString>::iterator j;
        for(j = controllers[i.key()].begin();  j != controllers[i.key()].end(); ++j)
            printf("%s ", j->toStdString().data());
        printf("\n");
    }
    fflush(stdout);
}

void AddControllersDialog::updateItemForComobox()
{
    ui->comboBox_controllers->clear();
    QMap<QString, QVector<QString>>::const_iterator i;
    for (i = controllers.constBegin(); i != controllers.constEnd(); ++i) {
        ui->comboBox_controllers->addItem(i.key());
    }
}

