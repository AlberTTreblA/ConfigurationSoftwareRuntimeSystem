#include "widget.h"
#include <QApplication>
#include "qtpluginmanager.h"
#include "datacommunication.h"
#include "global.h"
#include "datasave.h"
#include "simulator.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initGlobalVars();

    QtPluginsManager::getInstance().loadAllPlugins();
    QtPluginsManager::getInstance().initSignalAndSlot();
    QtPluginsManager::getInstance().bindVarForAllPlugins(global_var);

//    DataCommunication::getInstance().init();

    DataSave::getInstance().init();

//    Simulator::getInstance().init();

//    qDebug() << "main thread id: " << QThread::currentThreadId();
    //在widget中启动子线程，开始saveData;
    Widget w;
    w.show();

    return a.exec();
}
