#include "simulator.h"
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

void Simulator::init()
{
    getJsonObj();
}

void Simulator::loadData()
{
//    PdbErr_t retVal = PdbE_OK;
//    int handle = 0;
////    size_t sucessCnt = 0;

//    char* sqlBuf;

////    qDebug() << QThread::currentThreadId();

//    retVal = pdb_connect("127.0.0.1", 8105, &handle);
//    if (retVal != PdbE_OK)
//    {
//        qDebug() << QString::fromLocal8Bit("�������ݿ�ʧ��:") << QString::fromLocal8Bit(pdb_get_error_msg(retVal));
//        return;
//    }
//    retVal = pdb_login(handle, "sa", "123456");
//    if (retVal != PdbE_OK)
//    {
//        qDebug() << QString::fromLocal8Bit("��¼ʧ��:") << QString::fromLocal8Bit(pdb_get_error_msg(retVal));
//    }

//    //����SQL���
//    QVector<QString> sql;
//    QMap<QString, int> index;    //�洢���ݿ���field���ڴ�����±��ӳ��
//    QStringList keys = rootObj.keys();
//    QVector<void*> pTable;

//    for( int i =0; i < keys.size(); ++i )
//    {
//        pTable.push_back(nullptr);
//        sql.append(QString("select * from %1").arg(keys.at(i)));
//        QJsonObject subObj = rootObj.value(keys.at(i)).toObject();
//        QStringList subKeys = subObj.keys();

//        for( int j=0; j < subKeys.size(); ++j )
//        {
//            QString val = subObj[subKeys.at(j)].toString();
//            if( val.endsWith("_") )
//            {
//                index[subKeys.at(j)] = val.mid(0, val.size()-1).toDouble();
//            }
//        }
////        qDebug() << sql[i];
//    }
////    qDebug() << pTable.size();
////    QMap<QString, int>::iterator i;
////    for(i=index.begin(); i!=index.end() ;++i)
////    {
////        qDebug() << i.key() << "," <<i.value();
////    }
//    QVector<int> rowsCount;
//    QVector<int> colsCount;
//    for(int i=0; i<sql.size(); ++i)
//    {
//        QByteArray ba = sql[i].toLatin1();
//        sqlBuf = ba.data();
//        //��ѯ��
//        retVal = pdb_execute_query(handle, sqlBuf, &pTable[i]);
//        if (retVal != PdbE_OK)
//        {
//            std::cout << "��ѯ��ʧ��:" << pdb_get_error_msg(retVal) << std::endl;
//            break;
//        }

//        size_t columnCount = 0;
//        //��ñ������
//        retVal = pdb_table_get_column_count(pTable[i], &columnCount);
//        if (retVal != PdbE_OK)
//        {
//            std::cout << "��ñ�����ʧ��:" << pdb_get_error_msg(retVal) << std::endl;
//            break;
//        }
//        colsCount.append(columnCount);

//        size_t rowCount = 0;
//        //��ñ������
//        retVal = pdb_table_get_row_count(pTable[i], &rowCount);
//        if (retVal != PdbE_OK)
//        {
//            std::cout << "��ñ�����ʧ��:" << pdb_get_error_msg(retVal) << std::endl;
//            break;
//        }
//        rowsCount.append(rowCount);
//    }

////    qDebug() << "sub thread id: " << QThread::currentThreadId();
//    int j = 0;
//    while( !QThread::currentThread()->isInterruptionRequested() )
//    {
//        QEventLoop loop1;
//        QTimer::singleShot(1000,&loop1,SLOT(quit()));
//        loop1.exec();

//        for(int i=0; i<pTable.size(); ++i)
//        {

//                for(int k=0; k<colsCount[i]; ++k)
//                {
//                    ColumnInfo columnInfo;
//                    //�������Ϣ
//                    retVal = pdb_table_get_column_info(pTable[i], k, &columnInfo);
//                    if (retVal != PdbE_OK)
//                    {
//                        std::cout << "�������Ϣʧ��:" << pdb_get_error_msg(retVal) << std::endl;
//                        break;
//                    }

//                    if( !index.contains( columnInfo.colName_ ) )
//                        continue;

//                    double columnVal;
////                    qDebug() << columnInfo.colName_;
//                    retVal = pdb_table_get_double_by_colname(pTable[i], j, columnInfo.colName_, &columnVal);
//                    if (retVal != PdbE_OK)
//                    {
//                        std::cout << "��ñ�����ֵʧ��:" << pdb_get_error_msg(retVal) << std::endl;
//                        break;
//                    }
//                    qDebug() << columnVal;
//                    global_var[ index[columnInfo.colName_] ] = QVector<QString>{QString::number(columnVal), ""};
//                }
//                j++;
//            }

//        }
//    for(int i=0; i<pTable.size(); ++i)
//    {
//        retVal = pdb_table_free(pTable[i]);
//        if (retVal != PdbE_OK)
//        {
//            std::cout << "�ͷű�ʧ��:" << pdb_get_error_msg(retVal) << std::endl;
//            break;
//        }
//    }

//    pdb_disconnect(handle);
//    return;
}

void Simulator::getJsonObj()
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

