#ifndef GEN_CAPACITY_THREAD_H
#define GEN_CAPACITY_THREAD_H

#include <QObject>
#include "global.h"
#include "global.h"
#include <QFile>
#include <QFileInfo>
#include "gen_capacity_watcher.h"

class gen_capacity_thread : public QObject
{
    Q_OBJECT
public:
    explicit gen_capacity_thread(QObject *parent = 0);
    ~gen_capacity_thread();

signals:

public slots:
     void my_capacity();
private slots:

    void myfile_capa(QString fileName, QString filePath);

};

#endif // GEN_CAPACITY_THREAD_H
