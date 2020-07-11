#include "mainwindow.h"
#include <QApplication>
//#include <QMap>
//#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QMap<QString, QVector<QString>> aa;
////    aa["hh"].append(QVector<QString>({"hhh","j"}));
////    aa["hh"].remove(0);
//    qDebug() << aa["hh"].size();
//    QString s("hh%1");
//    QString ss("d");
//    qDebug() << s.arg(ss);
    return a.exec();
}
