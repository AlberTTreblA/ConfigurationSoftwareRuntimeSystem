#include "datasave.h"
#include "pdb_api.h"
#include <iostream>
#include <time.h>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QEventLoop>
#include <QTimer>
#include <QThread>
#include "stdio.h"
#include "global.h"


void DataSave::init()
{
    getJsonObj();

    QStringList keys = rootObj.keys();
    QJsonObject subObj = rootObj.value(keys.at(0)).toObject();
    int t = subObj["period"].toString().toInt();

    for(int i = 1; i < keys.size(); i++)
    {
        QJsonObject subObj =  rootObj.value(keys.at(i)).toObject();

        if( subObj["period"].toString().toInt() < t )
            t = subObj["period"].toString().toInt();
    }
    minTime = t;
//    qDebug() << t;
}

void DataSave::getJsonObj()
{
    QFile loadFile("D:/Qt5.9.0test/QtPluginDemo-master/QtPluginDemo-master/TTTT/dataSave.json");

     if(!loadFile.open(QIODevice::ReadOnly))
     {
         qDebug() << "could't open projects json";
         return;
     }

     QByteArray allData = loadFile.readAll();
     loadFile.close();

     QJsonParseError json_error;
     QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

     if(json_error.error != QJsonParseError::NoError)
     {
         qDebug() << "json error!";
         return;
     }

     rootObj = jsonDoc.object();
}

void DataSave::saveData()
{
//    PdbErr_t retVal = PdbE_OK;
//    int handle = 0;
//    size_t sucessCnt = 0;
//    char timeBuf[32];
//    char* sqlBuf;

////    qDebug() << QThread::currentThreadId();

//    retVal = pdb_connect("127.0.0.1", 8105, &handle);
//    if (retVal != PdbE_OK)
//    {
//        qDebug() << QString::fromLocal8Bit("连接数据库失败:") << QString::fromLocal8Bit(pdb_get_error_msg(retVal));
//        return;
//    }
//    retVal = pdb_login(handle, "sa", "123456");
//    if (retVal != PdbE_OK)
//    {
//        qDebug() << QString::fromLocal8Bit("登录失败:") << QString::fromLocal8Bit(pdb_get_error_msg(retVal));
//    }

//    //创建SQL语句
//    QVector<QString> sql;
//    QVector<QVector<QString> > index;    //存储每条sql语句中对应的metrics变量在global_var中的index
//    QStringList keys = rootObj.keys();
        
//    for( int i =0; i < keys.size(); ++i )
//    {
//        int count = 2;

//        QString s1 = QString("insert into %1").arg(keys.at(i));
//        QJsonObject subObj = rootObj.value(keys.at(i)).toObject();
//        QStringList subKeys = subObj.keys();
//        QString s2 = QString("(");
//        QString s3 = QString(" values(");

//        QVector<QString> temp;
//        for( int j=0; j < subKeys.size(); ++j )
//        {
//            if( subKeys.at(j)=="period" )
//                continue;

//            s2 = s2 + QString(subKeys.at(j)) + QString(",");

//            QString val = subObj[subKeys.at(j)].toString();
//            if( val.endsWith("_") )
//            {
//                temp.append(val.mid(0, val.size()-1));
//                s3 = s3 + QString("%") + QString::number(count++) + QString(",");
//            }
//            else
//            {
//                s3 = s3 + val + QString(",");
//            }
//        }
//        index.append(temp);
//        temp.clear();

//        s2 = s2 + QString("tstamp)");
//        s3 = s3 + QString("\"%1\")");
//        sql.append(s1 + s2 + s3);
////        qDebug() << sql[i];
//    }

//    while( !QThread::currentThread()->isInterruptionRequested() )
//    {
//        QEventLoop loop1;
//        QTimer::singleShot(minTime,&loop1,SLOT(quit()));
//        loop1.exec();
//\
//        time_t t;
//        tm tm;
//        time(&t);
//        localtime_s(&tm, &t);
//        sprintf_s(timeBuf, "%d-%d-%d %d:%d:%d", (1900 + tm.tm_year), (1 + tm.tm_mon), tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

//        QVector<QString> sql_exe;
//        for(int i=0; i<sql.size(); ++i)
//        {
//            sql_exe.append(sql[i].arg(timeBuf));

//            for(int j=0; j<index[i].size(); ++j)
//            {
//                sql_exe[i] = sql_exe[i].arg( global_var[index[i][j].toInt()][0] );
//            }
////            qDebug() << sql_exe[i];


//            QByteArray ba = sql_exe[i].toLatin1();
//            sqlBuf = ba.data();
//            qDebug() << sqlBuf;
//            retVal = pdb_execute_insert(handle, sqlBuf, &sucessCnt, nullptr);
//            if (retVal != PdbE_OK)
//            {
//                qDebug() << QString::fromLocal8Bit("插入数据失败:") << QString::fromLocal8Bit(pdb_get_error_msg(retVal));
//                break;
//            }

//        }
//        memset(timeBuf,0,sizeof(timeBuf)/sizeof(char));
//        sql_exe.clear();
//    }
//    pdb_disconnect(handle);
//    return;
}
