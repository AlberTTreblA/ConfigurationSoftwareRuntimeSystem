#ifndef W_CONSUMPTION_THREAD_H
#define W_CONSUMPTION_THREAD_H

#include <QObject>
#include "global.h"
#include <QFile>
#include <QFileInfo>
#include "w_consumption_watcher.h"

class w_consumption_thread : public QObject
{
    Q_OBJECT
public:
    explicit w_consumption_thread(QObject *parent = 0);
    ~w_consumption_thread();
      void my_consuomption();


signals:

public slots:
private slots:

     void myfile_cons(QString fileName,QString filePath);
};

#endif // W_CONSUMPTION_THREAD_H
