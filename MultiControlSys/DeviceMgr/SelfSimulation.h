#pragma once
//自检模拟器
#include <QObject>
#include "DeviceBase.h"

class SelfSimulation : public DeviceBase
{
    Q_OBJECT
public:
    SelfSimulation(QObject *parent);
    ~SelfSimulation();
private:
    static SPQ_Manager* m_pInstance;
public:
};




/
class SPQ_Manager : public DeviceBase
{
    Q_OBJECT

public:
    SPQ_Manager(QObject *parent);
    ~SPQ_Manager();
private:
    static SPQ_Manager* m_pInstance;
public:
    /*//使用了2-10位 0连接好 1没连接好   2---- X151   3---- X152
    //4---- 13X3
    //5---- X154
    //6---- X119
    //7---- X145
    //8---- X100-3X3
    //9---- X100-3X5
    //10---- X100-3X6
    */
    int _lineState = 0xFFC;//线路状态

public:
    static SPQ_Manager* getInstance();
public:
    int ParseMsgPowerControl(PMsgData pPacket);
    bool CheckLineConnected();//检测适配器线连接状态  //2-10位 全部是0 返回true
public:// 请求方法
    void RequestVersion();
    void RequsetSelfCheck();
    void RequestPowerControl();//num 编号 control 开关控制

};
