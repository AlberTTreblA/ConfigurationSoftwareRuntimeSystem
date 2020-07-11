#ifndef GLOBAL_H
#define GLOBAL_H

#include <QMap>
#include <QVector>
#include <QString>

/**
 * int:
 *     变量物理含义标识(从0开始递增，0:水泵液高，1:水泵温度，2:汽轮机转速，3:汽轮机功率)
 * QVector<QString>:
 *     vector[0]；变量取值
 *     vector[1]：变量类型("0":int，"1":float)
**/

extern QMap<int, QVector<QString>> global_var;
void initGlobalVars();

#endif // GLOBAL_H
