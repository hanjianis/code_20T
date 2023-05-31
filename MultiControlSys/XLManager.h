#ifndef XLMANAGER_HEADER_H
#define XLMANAGER_HEADER_H
#pragma once
#include <QObject>
#include <QMap>
#include "Packet.h"
#include "ITask.h"
//sqlite 数据管理
class XLManager : public QObject
{
    Q_OBJECT

public:
    XLManager(QObject *parent);
    ~XLManager();

public:
    static XLManager* m_pInstance;

    //单体实例获取方法 唯一的对象指针
    static XLManager* GetInstance();

private:
    void LoadXL();
    void LoadItems();
    void LoadDevice();
public:
    QList<ITask*> m_lstTasks;//testitemsdlg勾选的数据项的list

    //系统自检->系统自检
    QMap<int,QList<AutoTestData>> m_lstSystemselftest;//数据库Systemselftest表
    //系统自检->气密检查
    QMap<int,QList<AutoTestData>> m_lstAirtightnessinspection;//数据库Airtightnessinspection表
    //系统自检项
    QMap<int,QList<AutoTestData>> m_lstMNLTDJC;//数据库mnltdjc表 字典的value是list 系统自检时 根据数据下标依次显示数据项
    //系统自检项目
    QList<QString> m_lstSelfCheckItems;
    //自动测试->综合测试
     QMap<int, QList< AutoTestData>> m_lstIntegratedtesting;
     //自动测试->舵机回零
      QMap<int, QList< AutoTestData>> m_lstZeroreturnsteeringgear;
    //自动测试项目
    QList<QString> m_lstAutoTestItems;
    //自动测试时 下面的listwidget项
    QMap<int, AutoTestList> m_mapAutoTestList;
    //自动测试时  单项测试-连续测试 数据项
    QMap<int, QList< AutoTestData>> m_mapSINGLE_TEST;
    //惯导测试数据项
    QMap<int,AutoTestData> m_mapINS;//key是数据库中的id
    //自动测试 综合测试-连续 数据项
    QMap<int, QList<AutoTestData>> m_mapMULT_TEST;
    //各个硬件设备的ip地址 key值是心跳命令
    QMap<int, DeviceInfo> m_mapDevice;    

};
#endif
