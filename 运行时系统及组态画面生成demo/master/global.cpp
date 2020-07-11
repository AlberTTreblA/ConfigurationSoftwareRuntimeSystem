#include "global.h"

QMap<int, QVector<QString>> global_var = QMap<int, QVector<QString>>();

void initGlobalVars()
{
    global_var[0] = QVector<QString>({"11","0"});
    global_var[1] = QVector<QString>({"12.1","1"});
    global_var[2] = QVector<QString>({"13","0"});
    global_var[3] = QVector<QString>({"14.1","1"});
}
