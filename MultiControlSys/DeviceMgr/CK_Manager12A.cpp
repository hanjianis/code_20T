#include "CK_Manager12A.h"
#include "../UDPServer.h"

#include <QDebug>
#include "../XLManager.h"
CK_Manager12A* CK_Manager12A::m_pInstance = nullptr;

CK_Manager12A::CK_Manager12A(QObject *parent)
    : DeviceBase(DEV_CK12A,parent)
{
    pUDPServer->RegisterEvent(CK12A_CMD_HEARD_BEAT, std::bind(&CK_Manager12A::ParseMsgHeartBeat, this, std::placeholders::_1));
    pUDPServer->RegisterEvent(CK12A_CMD_VERSION, std::bind(&CK_Manager12A::ParseMsgVersion, this, std::placeholders::_1));       //需要研究
    pUDPServer->RegisterEvent(CK12A_CMD_SELF_CHECK, std::bind(&CK_Manager12A::ParseMsgSelfCheck, this, std::placeholders::_1));
    pUDPServer->RegisterEvent(CK12A_CMD_POWER_CONTROL, std::bind(&CK_Manager12A::ParseMsgPowerControl, this, std::placeholders::_1));
}

CK_Manager12A::~CK_Manager12A()
{
}
CK_Manager12A* CK_Manager12A::getInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CK_Manager12A(nullptr);
    }
    return m_pInstance;
}
//查看设备是否连接
int CK_Manager12A::ParseMsgHeartBeat(PMsgData pPacket)
{
    hearBeat_CK=1;
    qDebug() << "heart beat....";
    return 1;
}

int CK_Manager12A::ParseMsgVersion(PMsgData pPacket)
{
    //版本高位（1字节），版本低位（1字节）。 0x0100 V1.0
    qDebug() << "Version...";
    QString strVer = QString("%1.%2").arg(pPacket->msgBuf[0]).arg(pPacket->msgBuf[1]);
    qDebug() << strVer;
    return 1;
}

int CK_Manager12A::ParseMsgSelfCheck(PMsgData pPacket)
{
    qDebug() << "self check...";
    qDebug() << pPacket->msgBuf;

    return 1;
}

int CK_Manager12A::ParseMsgPowerControl(PMsgData pPacket)
{
    qDebug() << "PowerControl...";
    qDebug() << pPacket->msgBuf[0];
    qDebug() << pPacket->msgBuf[1];
    //收到下位机响应 获取电压值
    Sleep(500);
    RequestPowerStatus();
    return 1;
}

int CK_Manager12A::ParseMsgPowerStatus(PMsgData pPacket)
{
    qDebug() << "Power Status...";  
    return 1;
}

int CK_Manager12A::ParseMsgTestIO(PMsgData pPacket)
{
    qDebug() << "IO.....";
    //4个开关量
    for (int i = 0; i < 4; i++)
    {
        //qDebug() << i << "====" << pPacket->msgBuf[i];
    }
    return 1;
}

void CK_Manager12A::RequestVersion()
{
    pUDPServer->WriteData(CK12A_CMD_VERSION);
}

void CK_Manager12A::RequsetSelfCheck()
{
    pUDPServer->WriteData(CK12A_CMD_SELF_CHECK);
}

void CK_Manager12A::RequestPowerControl(char num, char control)
{
    char buf[2] = { 0 };
    buf[0] = num;
    buf[1] = control;
    pUDPServer->WriteData(CK12A_CMD_POWER_CONTROL, buf, 2,_ip, _port);
}
/*
void CK_Manager12A::RequestPowerControl()
{
    pUDPServer->WriteData(CK12A_CMD_POWER_CONTROL, _ip, _port);
}
*/
void CK_Manager12A::RequestPowerStatus()
{
    pUDPServer->WriteData( CK12A_CMD_POWER_CONTROL);
}

void CK_Manager12A::RequestTestIO()
{
    pUDPServer->WriteData(CK_CMD_TEST_IO);
}




bool CK_Manager12A::CheckLineConnected()
{
    //决定是否设备连接
    return true;
    bool bConnected = true;
    //目前第4位不检测
    for (int i = 2; i <=10;i++)
    {
        /*
        if (i != 4)
        {
            if (_lineState&(0x1 << i)) //没连接号
                bConnected = false;
        }
        */
    }
    return bConnected;
}
