#ifndef CK_MANAGER20T_H
#define CK_MANAGER20T_H

#include <QObject>
#include "../Packet.h"
#include "DeviceBase.h"
//12A另一个程控电源
class CK_Manager20T : public DeviceBase
{
    Q_OBJECT
public:
    CK_Manager20T(QObject *parent);
    ~CK_Manager20T();
private:
    static CK_Manager20T* m_pInstance;


public:
    static CK_Manager20T* getInstance();
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

#endif // CK_MANAGER20T_H
