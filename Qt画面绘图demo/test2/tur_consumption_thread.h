#ifndef TUR_CONSUMPTION_THREAD_H
#define TUR_CONSUMPTION_THREAD_H

#include <QObject>
#include "global.h"
#include <QFile>
#include <QFileInfo>
#include "tur_consumption_watcher.h"

class tur_consumption_thread : public QObject
{
    Q_OBJECT
public:
    explicit tur_consumption_thread(QObject *parent = 0);
    ~tur_consumption_thread();
    void my_consumption();

signals:

public slots:
private slots:
    void myfile_consumption(QString fileName, QString filePath);
};

#endif // TUR_CONSUMPTION_THREAD_H
