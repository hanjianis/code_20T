#include "ZJ_Manager.h"

ZJ_Manager*  ZJ_Manager::m_pInstance = nullptr;

ZJ_Manager::ZJ_Manager(QObject *parent)
    : DeviceBase(DEV_ZJ,parent)
{
    pUDPServer->RegisterEvent(ZJ_CMD_HEARD_BEAT, std::bind(&ZJ_Manager::ParseMsgHeartBeat, this, std::placeholders::_1));
    pUDPServer->RegisterEvent(ZJ_CMD_VERSION, std::bind(&ZJ_Manager::ParseMsgVersion, this, std::placeholders::_1));
    pUDPServer->RegisterEvent(ZJ_CMD_SELF_CHECK, std::bind(&ZJ_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
   // pUDPServer->RegisterEvent(ZJ_CMD_POWER_CONTROL, std::bind(&ZJ_Manager::ParseMsgPowerControl, this, std::placeholders::_1));

}

ZJ_Manager::~ZJ_Manager()
{
}

ZJ_Manager* ZJ_Manager::getInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new ZJ_Manager(nullptr);
    }
    return m_pInstance;
}
//查看设备是否连接
int ZJ_Manager::ParseMsgHeartBeat(PMsgData pPacket)
{
    hearBeat_ZJ=1;
    qDebug() << "heart beat....";
    return 1;
}
int ZJ_Manager::ParseMsgVersion(PMsgData pPacket)
{
    //版本高位（1字节），版本低位（1字节）。 0x0100 V1.0
    qDebug() << "Version...";
    QString strVer = QString("%1.%2").arg(pPacket->msgBuf[0]).arg(pPacket->msgBuf[1]);
    qDebug() << strVer;
    return 1;
}

int ZJ_Manager::ParseMsgSelfCheck(PMsgData pPacket)
{
    qDebug() << "self check...";
    qDebug() << pPacket->msgBuf;

    return 1;
}
/*
int ZJ_Manager::ParseMsgPowerControl(PMsgData pPacket)
{
    qDebug() << "SPQ_Manager::ParseMsgPowerStatus";
    if (pPacket->MsgLen < 4)//数组长度不够
        return 1;
    //4字节 0-31位
    int *cmd = (int*)&(pPacket->msgBuf[0]);//电压
    _lineState = *cmd;
    return 1;
}
*/
bool ZJ_Manager::CheckLineConnected()
{
    //决定是否设备连接
    return true;
    bool bConnected = true;
    //目前第4位不检测
    for (int i = 2; i <=10;i++)
    {
        if (i != 4)
        {
            if (_lineState&(0x1 << i)) //没连接号
                bConnected = false;
        }
    }
    return bConnected;
}

#pragma region 请求
void ZJ_Manager::RequestVersion()
{
    pUDPServer->WriteData(SPQ_CMD_VERSION, _ip, _port);
}

void ZJ_Manager::RequsetSelfCheck()
{
    pUDPServer->WriteData(SPQ_CMD_SELF_CHECK, _ip, _port);
}
/*
void ZJ_Manager::RequestPowerControl()
{
    pUDPServer->WriteData(ZJ_CMD_POWER_CONTROL, _ip, _port);
}
*/
#pragma endregion

