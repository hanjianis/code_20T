#include "SPQ_Manager12A.h"

SPQ_Manager12A*  SPQ_Manager12A::m_pInstance = nullptr;
SPQ_Manager12A::SPQ_Manager12A(QObject *parent)
    : DeviceBase(DEV_SPQ12A,parent)
{
    pUDPServer->RegisterEvent(SPQ12A_CMD_HEARD_BEAT, std::bind(&SPQ_Manager12A::ParseMsgHeartBeat, this, std::placeholders::_1));
    pUDPServer->RegisterEvent(SPQ12A_CMD_VERSION, std::bind(&SPQ_Manager12A::ParseMsgVersion, this, std::placeholders::_1));
    pUDPServer->RegisterEvent(SPQ12A_CMD_SELF_CHECK, std::bind(&SPQ_Manager12A::ParseMsgSelfCheck, this, std::placeholders::_1));
    pUDPServer->RegisterEvent(SPQ12A_CMD_POWER_CONTROL, std::bind(&SPQ_Manager12A::ParseMsgPowerControl, this, std::placeholders::_1));
}

SPQ_Manager12A::~SPQ_Manager12A()
{
}

SPQ_Manager12A* SPQ_Manager12A::getInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new SPQ_Manager12A(nullptr);
    }
    return m_pInstance;
}
//查看设备是否连接
int SPQ_Manager12A::ParseMsgHeartBeat(PMsgData pPacket)
{
    hearBeat_SPQ=1;
    qDebug() << "heart beat....";
    return 1;
}
int SPQ_Manager12A::ParseMsgVersion(PMsgData pPacket)
{
    //版本高位（1字节），版本低位（1字节）。 0x0100 V1.0
    qDebug() << "Version...";
    QString strVer = QString("%1.%2").arg(pPacket->msgBuf[0]).arg(pPacket->msgBuf[1]);
    qDebug() << strVer;
    return 1;
}

int SPQ_Manager12A::ParseMsgPowerControl(PMsgData pPacket)
{
    qDebug() << "SPQ_Manager::ParseMsgPowerStatus";
    if (pPacket->MsgLen < 4)//数组长度不够
        return 1;
    //4字节 0-31位
    int *cmd = (int*)&(pPacket->msgBuf[0]);//电压
    _lineState = *cmd;
    //使用了2-10位 0连接好 1没连接好   2---- X151   3---- X152
    //4---- 13X3
    //5---- X154
    //6---- X119
    //7---- X145
    //8---- X100-3X3
    //9---- X100-3X5
    //10---- X100-3X6
    return 1;
}

bool SPQ_Manager12A::CheckLineConnected()
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
void SPQ_Manager12A::RequestVersion()
{
    pUDPServer->WriteData(SPQ_CMD_VERSION, _ip, _port);
}

void SPQ_Manager12A::RequsetSelfCheck()
{
    pUDPServer->WriteData(SPQ_CMD_SELF_CHECK, _ip, _port);
}
/*
void SPQ_Manager12A::RequestPowerControl()
{
    pUDPServer->WriteData(SPQ12A_CMD_POWER_CONTROL, _ip, _port);
}

void SPQ_Manager12A::RequestPowerControl(char num, char control)
{
    char buf[2] = { 0 };
    buf[0] = num;
    buf[1] = control;
    pUDPServer->WriteData(CK_CMD_POWER_CONTROL, buf, 2);
}
*/
