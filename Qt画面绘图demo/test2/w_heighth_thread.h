#ifndef W_HEIGHTH_THREAD_H
#define W_HEIGHTH_THREAD_H

#include <QObject>
#include "global.h"
#include "global.h"
#include <QFile>
#include <QFileInfo>
#include "w_height_watcher.h"

class w_heighth_thread : public QObject
{
    Q_OBJECT
public:
    explicit w_heighth_thread(QObject *parent = 0);
    ~w_heighth_thread();
    void my_height();

signals:

public slots:
    void myfile_height(QString fileName, QString filePath);
};

#endif // W_HEIGHTH_THREAD_H
