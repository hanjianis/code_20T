#pragma once

#include <QObject>
#include "../Packet.h"
#include "DeviceBase.h"

class CK_Manager12A : public DeviceBase
{
    Q_OBJECT

public:
    CK_Manager12A(QObject *parent);
    ~CK_Manager12A();
private:
    static CK_Manager12A* m_pInstance;


public:
    static CK_Manager12A* getInstance();
public:
    int ParseMsgHeartBeat(PMsgData pPacket);
    int ParseMsgVersion(PMsgData pPacket);
    int ParseMsgSelfCheck(PMsgData pPacket);
    int ParseMsgPowerControl(PMsgData pPacket);
    int ParseMsgPowerStatus(PMsgData pPacket);
    int ParseMsgTestIO(PMsgData pPacket);
    bool CheckLineConnected();//检测适配器线连接状态  //2-10位 全部是0 返回true
    //请求消息
    //void RequestHeartBeat();
    void RequestVersion();
    void RequsetSelfCheck();
    void RequestPowerControl(char num, char control);//num 编号 control 开关控制
    //void RequestPowerControl();
    void RequestPowerStatus();
    void RequestTestIO();
};
