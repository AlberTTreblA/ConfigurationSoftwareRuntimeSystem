#ifndef GEN_TEMPERATURE_THREAD_H
#define GEN_TEMPERATURE_THREAD_H

#include <QObject>
#include <global.h>
#include "global.h"
#include <QFile>
#include <QFileInfo>
#include "gen_temperature_watcher.h"
class gen_temperature_thread : public QObject
{
    Q_OBJECT
public:
    explicit gen_temperature_thread(QObject *parent = 0);
    ~gen_temperature_thread();

signals:

public slots:
     void my_temperature();
private slots:
    void myfile_temp(QString fileName, QString filePath);
};

#endif // GEN_TEMPERATURE_THREAD_H
