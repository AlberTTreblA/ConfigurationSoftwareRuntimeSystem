#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    frameTitle.insert("0", QString::fromLocal8Bit("水泵画面"));
    frameTitle.insert("1", QString::fromLocal8Bit("汽轮机画面"));
    ui->setupUi(this);
    initFiles();

//    QFile *readFile=new QFile("D:/Qt5.9.0test/GenPro/1.pro");
//    QString strAll;
//    if( !readFile->exists() ){
//        qDebug() << QString::fromLocal8Bit("所读文件不存在！");
//    }
//    else{
//        if(!readFile->open(QIODevice::ReadOnly|QIODevice::Text)) {
//            qDebug() << QString::fromLocal8Bit("打开文件失败！") << endl;
//        }
//        else{
//            QTextStream stream(readFile);
//            strAll=stream.readAll();
//        }
//    }
//    readFile->close();
//    if( strAll.isEmpty() ){
//        qDebug() << QString::fromLocal8Bit("所读文件为空！");
//    }
//    else {
//        qDebug() << strAll;
//    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddLabel_clicked()
{
    static int labelOrder = 0;
    QString text = ui->lineEdit_labelText->text();
    QString x = ui->lineEdit_labelX->text();
    QString y = ui->lineEdit_labelY->text();
    QString w = ui->lineEdit_labelW->text();
    QString h = ui->lineEdit_labelH->text();
    components["Label"].append(QVector<QString>({QString::number(labelOrder), \
                                        QString("QString::fromLocal8Bit(\"") + text + QString("\")"), \
                                                x, y, w, h}));
    labelOrder = labelOrder + 1;

    QString oldContent = ui->label_labelNum->text();
    int oldNum = oldContent.right(1).toInt();
    QString newContent = QString(oldContent.mid(0,oldContent.length()-1) ) + QString::number( oldNum+1 );
    ui->label_labelNum->setText(newContent);
}

void MainWindow::on_btnAddLine_clicked()
{
    static int lineOrder = 0;
    QString var = ui->lineEdit_lineVar->text();
    QString x = ui->lineEdit_lineX->text();
    QString y = ui->lineEdit_lineY->text();
    QString w = ui->lineEdit_lineW->text();
    QString h = ui->lineEdit_lineH->text();
    components["Line"].append(QVector<QString>({QString::number(lineOrder), var, x, y, w, h}));
    lineOrder = lineOrder + 1;

    QString oldContent = ui->label_lineNum->text();
    int oldNum = oldContent.right(1).toInt();
    QString newContent = QString(oldContent.mid(0,oldContent.length()-1) ) + QString::number( oldNum+1 );
    ui->label_lineNum->setText(newContent);
}

void MainWindow::on_btnAddAlarm_clicked()
{
    static int alarmOrder = 0;
    QString text = ui->lineEdit_alarmText->text();
    QString var = ui->lineEdit_alarmVar->text();
    QString x = ui->lineEdit_alarmX->text();
    QString y = ui->lineEdit_alarmY->text();
    components["Alarm"].append(QVector<QString>({QString::number(alarmOrder), \
                                        QString("QString::fromLocal8Bit(\"") + text + QString("\")"), \
                                                var, x, y}));
    alarmOrder = alarmOrder + 1;

    QString oldContent = ui->label_alarmNum->text();
    int oldNum = oldContent.right(1).toInt();
    QString newContent = QString(oldContent.mid(0,oldContent.length()-1) ) + QString::number( oldNum+1 );
    ui->label_alarmNum->setText(newContent);
}

void MainWindow::on_btnAddJson_clicked()
{
    QString auth = ui->lineEdit_auth->text();
    QString des = ui->lineEdit_des->text();
    QString type = ui->lineEdit_type->text();
    QString version = ui->lineEdit_version->text();
    if( components["Json"].size()==0 )
    {
        components["Json"].append(QVector<QString>({auth, version, type, des}));
    }
    else
    {
        components["Json"][0] = QVector<QString>({auth, version, type, des});
    }
}

void MainWindow::on_btnCreateFrame_clicked()
{
    createContents();

    createFolder();

    createProFile();

    createHeaderFile();

    createSourceFile();

    createJsonFile();
}

void MainWindow::initFiles()
{
    proFile.append(QString("TEMPLATE=lib\nCONFIG+= plugin\nQT+= widgets\nQT+= core gui qml\n"
            "TARGET=%1\nDESTDIR=%2\nHEADERS+=%3\nSOURCES+=%4\nDISTFILES+=%5\n"));
    proFile[0] = proFile[0].arg(pluginName).arg(destRoute).arg(headerFileName).arg(sourceFileName).arg(jsonFileName);
    proFile.append(QString("INCLUDEPATH+=\"")+primitivesLibRoute+"\"\n");
    proFile.append("LIBS+=");

    headerFile.append(QString("#ifndef %1_H\n#define %1_H\n"));
    headerFile[0] = headerFile[0].arg(headerFileName.mid(0, headerFileName.size()-2).toUpper());
    headerFile.append(QString("#include <QtPlugin>\n#include <QMap>\n"
             "#include \"D:/Qt5.9.0test/GenProTest/QtPluginDemo-master/TTTT/interfaceplugin.h\"\n"));
    headerFile.append(QString("class PluginC :public QWidget, public InterfacePlugin\n{\nQ_OBJECT\n"
            "Q_PLUGIN_METADATA(IID InterfacePlugin_iid FILE \"programmer.json\")\nQ_INTERFACES(InterfacePlugin)\n"
            "signals:\nvoid sendMsg2Manager(PluginMetaData) Q_DECL_OVERRIDE;\n"));
    headerFile.append(QString("public:\nexplicit PluginC(QWidget *parent = nullptr);\n"
             "virtual  void recMsgfromManager(PluginMetaData)  Q_DECL_OVERRIDE;\n"
             "virtual void bindVar(QMap<int, QVector<QString>>&)  Q_DECL_OVERRIDE;\n"));
    headerFile.append(QString("private:\nQMap<int, QVector<QString>*> var;\n"));
    headerFile.append(QString("};\n#endif\n"));

    sourceFile.append(QString("#include \"%1\"\n"));
    sourceFile[0] = sourceFile[0].arg(headerFileName);
    sourceFile.append(QString("PluginC::PluginC(QWidget *parent):QWidget(parent)\n{\n"));
    sourceFile.append(QString("var[0]=nullptr;\nvar[1]=nullptr;\nthis->setWindowTitle(QString::fromLocal8Bit(\"%1\"));\n"
                               "this->setGeometry(QRect(500,300,400,500));\n"));
    sourceFile[2] = sourceFile[2].arg(frameTitle[ui->lineEdit_type->text()]);
    sourceFile.append(QString("}\n"));
    sourceFile.append(QString("void PluginC::bindVar(QMap<int, QVector<QString>>& map)\n{\n"
            "QMap<int, QVector<QString>*>::iterator i;\nQMap<int, QVector<QString>>::iterator j;\n"
            "for(i=var.begin(); i!=var.end(); ++i)\n{\nfor(j=map.begin(); j!=map.end(); ++j)\n{\n"
            "if( i.key()==j.key() )\n{\ni.value() = &j.value();\n}\n}\n}\n"));
    sourceFile.append(QString(""));              //sourceFile[5]------创建图元对象
    sourceFile.append(QString("}\n"));
    sourceFile.append(QString("void PluginC::recMsgfromManager(PluginMetaData metedata)\n{}\n"));

    jsonFile.append(QString("{\n\"author\":\"%1\",\n\"version\":\"%2\",\n\"type\":\"%3\",\n\"des\":\"%4\"\n}\n"));
}

void MainWindow::createContents()
{
    QMap<QString, QVector<QVector<QString>>>::iterator i;
    for( i = components.begin(); i != components.end(); ++i )
    {
        if( i.key() == "Json" )
        {
            //添加json文件内容
            for( int j = 0; j < i.value()[0].size(); ++j )
            {
                jsonFile[0] = jsonFile[0].arg((i.value()[0][j]));
            }
            continue;
        }

        //在.pro中添加图元静态库
        proFile[2] += "\"" + primitivesLibRoute + i.key() + ".lib\"\\\n";

        //在.h中include头文件
        headerFile[1] = headerFile[1] + "#include \"" + i.key().toLower() + ".h\"\n";

        for( int j = 0; j < i.value().size(); ++j )
        {
            QString varName = i.key().toLower() + i.value()[j][0];
            //在.h中添加私有变量
            headerFile[4] = headerFile[4] + i.key() + " *" + varName + ";\n";

            //在.cpp中添加内容
            QString newContent = varName + "=new " + i.key() + "(this";
            for( int k = 1; k != i.value()[j].size(); ++k )
            {
                newContent += "," + i.value()[j][k];
            }
            newContent += ");\n";
            sourceFile[5] = sourceFile[5] + newContent;
        }
    }
}

void MainWindow::createFolder()
{
    QDir *folder = new QDir;
    bool exist = folder->exists(folderRoute + folderName);
    if(exist)
    {
        qDebug() << QString::fromLocal8Bit("文件夹已存在！");
    }
    else
    {
        bool ok = folder->mkdir(folderRoute + folderName);
           if(ok)
           {
               qDebug() << QString::fromLocal8Bit("创建文件夹成功！");
           }
           else
           {
               qDebug() << QString::fromLocal8Bit("创建文件夹失败！");
           }
    }
}

void MainWindow::createProFile()
{
    QFile *writeFile = new QFile(folderRoute + folderName + "/" + folderName + ".pro");

    QString content;
//    content = content.fromLocal8Bit("abc哈哈\naa");
    for(int i=0; i<proFile.size(); ++i)
    {
        content += proFile[i];
    }

    writeFile->open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(writeFile);
    stream << content;

    qDebug() << QString::fromLocal8Bit("写入.pro成功！");

    writeFile->close();
//    qDebug() << content;
}

void MainWindow::createHeaderFile()
{
    QFile *writeFile = new QFile(folderRoute + folderName + "/" + headerFileName);

    QString content;
    for(int i=0; i<headerFile.size(); ++i)
    {
        content += headerFile[i];
    }

    writeFile->open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(writeFile);
    stream << content;

    qDebug() << QString::fromLocal8Bit("写入.h成功！");

    writeFile->close();
//    qDebug() << content;
}

void MainWindow::createSourceFile()
{
    QFile *writeFile = new QFile(folderRoute + folderName + "/" + sourceFileName);

    QString content;
    for(int i=0; i<sourceFile.size(); ++i)
    {
        content += sourceFile[i];
    }

    writeFile->open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(writeFile);
    stream << content;

    qDebug() << QString::fromLocal8Bit("写入.cpp成功！");

    writeFile->close();
//    qDebug() << content;
}

void MainWindow::createJsonFile()
{
    QFile *writeFile = new QFile(folderRoute + folderName + "/" + jsonFileName);

    QString content;
    for(int i=0; i<jsonFile.size(); ++i)
    {
        content += jsonFile[i];
    }

    writeFile->open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(writeFile);
    stream.setCodec("UTF-8");
    stream << content;

    qDebug() << QString::fromLocal8Bit("写入.json成功！");

    writeFile->close();
//    qDebug() << content;
}
