#ifndef TUR_ROTATION_THREAD_H
#define TUR_ROTATION_THREAD_H

#include <QObject>
#include "global.h"
#include <QFile>
#include <QFileInfo>
#include "tur_rotation_watcher.h"
class tur_rotation_thread : public QObject
{
    Q_OBJECT
public:
    explicit tur_rotation_thread(QObject *parent = 0);
    ~tur_rotation_thread();
    void my_rotation();

signals:

public slots:
private slots:
    void myfile_rotation(QString fileName, QString filePath);
};

#endif // TUR_ROTATION_THREAD_H
