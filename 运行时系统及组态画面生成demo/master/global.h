#ifndef GLOBAL_H
#define GLOBAL_H

#include <QMap>
#include <QVector>
#include <QString>

/**
 * int:
 *     �����������ʶ(��0��ʼ������0:ˮ��Һ�ߣ�1:ˮ���¶ȣ�2:���ֻ�ת�٣�3:���ֻ�����)
 * QVector<QString>:
 *     vector[0]������ȡֵ
 *     vector[1]����������("0":int��"1":float)
**/

extern QMap<int, QVector<QString>> global_var;
void initGlobalVars();

#endif // GLOBAL_H
