#pragma once
//滑台
#include <QObject>
#include "DeviceBase.h"

class HT_Manager : public DeviceBase
{
public:
    HT_Manager(QObject *parent);
    ~HT_Manager();
private:
    static HT_Manager* m_pInstance;
public:
    int _lineState = 0xFFC;//线路状态

public:
    static HT_Manager* getInstance();
public:
    int ParseMsgHeartBeat(PMsgData pPacket);
    int ParseMsgVersion(PMsgData pPacket);
    int ParseMsgSelfCheck(PMsgData pPacket);
    int ParseMsgPowerControl(PMsgData pPacket);
public:// 请求方法
    void RequestVersion();
    void RequsetSelfCheck();
   // void RequestPowerControl();//num 编号 control 开关控制
    void RequestPowerControl(uint8_t num, uint8_t control,uint16_t controlvalue);//num 编号 control 开关控制
};
