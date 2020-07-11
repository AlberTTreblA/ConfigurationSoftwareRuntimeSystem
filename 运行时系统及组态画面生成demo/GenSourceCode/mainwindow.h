#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_btnAddLabel_clicked();
    void on_btnAddLine_clicked();
    void on_btnAddAlarm_clicked();
    void on_btnAddJson_clicked();
    void on_btnCreateFrame_clicked();

private:
    void initFiles();
    void createContents();
    void createFolder();
    void createProFile();
    void createHeaderFile();
    void createSourceFile();
    void createJsonFile();

    Ui::MainWindow *ui;
    QMap<QString, QVector<QVector<QString>>> components;
    QVector<QString> proFile;
    QVector<QString> headerFile;
    QVector<QString> sourceFile;
    QVector<QString> jsonFile;

    QString primitivesLibRoute = "D:/QtPrimitiveLib/";
    QString folderRoute = "D:/Qt5.9.0test/GenProTest/QtPluginDemo-master/";
    QString folderName = "PluginC";
    QString headerFileName = "pluginc.h";
    QString sourceFileName = "pluginc.cpp";
    QString jsonFileName = "programmer.json";

    QString destRoute = "../plugins";
    QString pluginName = "pluginC";

    QMap<QString, QString> frameTitle;
};

#endif // MAINWINDOW_H
