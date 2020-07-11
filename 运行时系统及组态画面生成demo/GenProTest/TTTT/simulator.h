#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QJsonObject>
#include <QObject>
#include <QMutex>

class  Simulator : public QObject
{
    Q_OBJECT

public:
    static Simulator &getInstance()
    {
        static Simulator m_instance;
        return m_instance;
    }
public:
    void init();
    void getJsonObj();
    void loadData();

public slots:

private:
    QJsonObject rootObj;
    QMutex m_lock;
};

#endif // SIMULATOR_H
