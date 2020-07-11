#ifndef DATASAVE_H
#define DATASAVE_H


#include <QObject>
#include <QVector>
#include <QJsonObject>
#include "global.h"

class DataSave : public QObject
{
    Q_OBJECT

public:
    static DataSave &getInstance()
    {
        static DataSave m_instance;
        return m_instance;
    }

public:

    void init();
    void getJsonObj();
    void saveData();

signals:

public slots:
private:
    QJsonObject rootObj;
    int minTime;
};


#endif // DATASAVE_H
