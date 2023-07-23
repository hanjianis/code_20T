#pragma once
//自检模拟器
#include <QObject>
#include "DeviceBase.h"

class ZJ_Manager : public DeviceBase
{
public:
    ZJ_Manager(QObject *parent);
    ~ZJ_Manager();
private:
    static ZJ_Manager* m_pInstance;
public:
    int _lineState = 0xFFC;//线路状态

public:
    static ZJ_Manager* getInstance();
public:
    int ParseMsgHeartBeat(PMsgData pPacket);
   // int ParseMsgPowerControl(PMsgData pPacket);
    int ParseMsgVersion(PMsgData pPacket);
    int ParseMsgSelfCheck(PMsgData pPacket);
    bool CheckLineConnected();//检测适配器线连接状态  //2-10位 全部是0 返回true
public:// 请求方法
    void RequestVersion();
    void RequsetSelfCheck();
   // void RequestPowerControl();//num 编号 control 开关控制
};
