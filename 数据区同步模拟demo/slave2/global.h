#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QReadWriteLock>
extern QReadWriteLock waterpump_heighth_rw;
extern QReadWriteLock waterpump_consumption_rw;
extern QReadWriteLock rw_gen_capacitu;
extern QReadWriteLock rw_gen_temperature;
extern QReadWriteLock rw_tur_consumption;
extern QReadWriteLock rw_tur_rotation;

extern int waterpump_consumption;
extern int gen_temperature;
extern int gen_capacity;
extern int tur_rotation;
extern int tur_consumption;
extern int switch_value;
extern int MPoint[3];


class global : public QObject
{
    Q_OBJECT
public:
    explicit global(QObject *parent = 0);
    ~global();

signals:

public slots:
};

#endif // GLOBAL_H
