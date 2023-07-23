#include "HT_Manager.h"
#include <string.h>
HT_Manager*  HT_Manager::m_pInstance = nullptr;

HT_Manager::HT_Manager(QObject *parent)
    : DeviceBase(DEV_HT,parent)
{
    pUDPServer->RegisterEvent(HT_CMD_HEARD_BEAT, std::bind(&HT_Manager::ParseMsgHeartBeat, this, std::placeholders::_1));
    pUDPServer->RegisterEvent(HT_CMD_VERSION, std::bind(&HT_Manager::ParseMsgVersion, this, std::placeholders::_1));
    pUDPServer->RegisterEvent(HT_CMD_SELF_CHECK, std::bind(&HT_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
    pUDPServer->RegisterEvent(HT_CMD_POWER_CONTROL, std::bind(&HT_Manager::ParseMsgPowerControl, this, std::placeholders::_1));
}

HT_Manager::~HT_Manager()
{
}

HT_Manager* HT_Manager::getInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new HT_Manager(nullptr);
    }
    return m_pInstance;
}
//查看设备是否连接
int HT_Manager::ParseMsgHeartBeat(PMsgData pPacket)
{
    hearBeat_HT=1;
    qDebug() << "heart beat....";
    return 1;
}
int HT_Manager::ParseMsgVersion(PMsgData pPacket)
{
    //版本高位（1字节），版本低位（1字节）。 0x0100 V1.0
    qDebug() << "Version...";
    QString strVer = QString("%1.%2").arg(pPacket->msgBuf[0]).arg(pPacket->msgBuf[1]);
    qDebug() << strVer;
    return 1;
}

int HT_Manager::ParseMsgSelfCheck(PMsgData pPacket)
{
    qDebug() << "self check...";
    qDebug() << pPacket->msgBuf;

    return 1;
}

int HT_Manager::ParseMsgPowerControl(PMsgData pPacket)
{
    qDebug() << "SPQ_Manager::ParseMsgPowerStatus";
    if (pPacket->MsgLen < 4)//数组长度不够
        return 1;
    //4字节 0-31位
    int *cmd = (int*)&(pPacket->msgBuf[0]);//电压
    _lineState = *cmd;
    return 1;
}

void HT_Manager::RequestVersion()
{
    pUDPServer->WriteData(SPQ_CMD_VERSION, _ip, _port);
}

void HT_Manager::RequsetSelfCheck()
{
    pUDPServer->WriteData(SPQ_CMD_SELF_CHECK, _ip, _port);
}

void HT_Manager::RequestPowerControl(uint8_t num, uint8_t control,uint16_t controlvalue)
{
    char buf[4] = { 0 };
    buf[0]=num ;
    buf[1] = control;
  //  char* value=new char[2];
   // value=(char*)controlvalue;
    //*value=static_cast<char>(controlvalue);
    memcpy(&buf[2],&controlvalue,sizeof(controlvalue));
   // buf+2=&control;
   // buf[3]=control<<8;
    //buf[2]=reinterpret_cast<uint16_t>(controlvalue);
    pUDPServer->WriteData(HT_CMD_POWER_CONTROL, buf, 4,_ip, _port);
}
/*
void HT_Manager::RequestPowerControl()
{
    pUDPServer->WriteData(SPQ_CMD_POWER_CONTROL, _ip, _port);
}
*/
#pragma endregion

