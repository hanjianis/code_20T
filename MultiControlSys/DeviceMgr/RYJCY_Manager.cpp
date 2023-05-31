#include "RYJCY_Manager.h"
RYJCY_Manager*  RYJCY_Manager::m_pInstance = nullptr;
RYJCY_Manager::RYJCY_Manager(QObject *parent)
	: DeviceBase(DEV_RYJCY,parent)
{

	pUDPServer->RegisterEvent(RYJCY_CMD_VERSION, std::bind(&RYJCY_Manager::ParseMsgVersion, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(RYJCY_CMD_SELF_CHECK, std::bind(&RYJCY_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(RYJCY_CMD_POWER_CONTROL, std::bind(&RYJCY_Manager::ParseMsgPowerControl, this, std::placeholders::_1));
	//pUDPServer->RegisterEvent(ZHDY_CMD_POWER_STATUS, std::bind(&RYJCY_Manager::ParseMsgPowerStatus, this, std::placeholders::_1));
}

RYJCY_Manager::~RYJCY_Manager()
{
}

RYJCY_Manager* RYJCY_Manager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new RYJCY_Manager(nullptr);
	}
	return m_pInstance;
}

int RYJCY_Manager::ParseMsgPowerControl(PMsgData pPacket)
{
	qDebug() << "";
	if (pPacket->MsgLen < 5)//数组长度不够
		return 1;
	int index = 0;
	_MYFlag = pPacket->msgBuf[index++];
	_KYFlag = pPacket->msgBuf[index++];
	_GBGDFlag = pPacket->msgBuf[index++];
	_DKDSFlag = pPacket->msgBuf[index++];
	_CJFlag = pPacket->msgBuf[index++];
	return 1;
}

void RYJCY_Manager::RequestVersion()
{
	pUDPServer->WriteData(RYJCY_CMD_VERSION, _ip, _port);
}

void RYJCY_Manager::RequsetSelfCheck()
{
	pUDPServer->WriteData(RYJCY_CMD_SELF_CHECK, _ip, _port);
}

void RYJCY_Manager::RequsetPowerControl()
{
	pUDPServer->WriteData(RYJCY_CMD_POWER_CONTROL, _ip, _port); 
}
