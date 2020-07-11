#include "global.h"
 QReadWriteLock waterpump_heighth_rw;
 QReadWriteLock waterpump_consumption_rw;
 QReadWriteLock rw_gen_capacitu;
 QReadWriteLock rw_gen_temperature;
 QReadWriteLock rw_tur_consumption;
 QReadWriteLock rw_tur_rotation;

 int waterpump_consumption=0;
 int gen_capacity;
 int gen_temperature;
 int tur_consumption;
 int tur_rotation;
 int switch_value=0;
 int MPoint[3]={0,0,0};//M[0]:水泵液面高度； M[1]:汽轮机转速； M[2]:发电机温度

global::global(QObject *parent) : QObject(parent)
{

}

global::~global()
{

}

