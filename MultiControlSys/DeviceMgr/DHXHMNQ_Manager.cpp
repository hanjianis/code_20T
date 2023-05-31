#include "DHXHMNQ_Manager.h"
DHXHMNQ_Manager*  DHXHMNQ_Manager::m_pInstance = nullptr;
DHXHMNQ_Manager::DHXHMNQ_Manager(QObject *parent)
	: DeviceBase(DEV_DHXHMNQ,parent)
{
	pUDPServer->RegisterEvent(DHXHMNQ_CMD_VERSION, std::bind(&DHXHMNQ_Manager::ParseMsgVersion, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(DHXHMNQ_CMD_SELF_CHECK, std::bind(&DHXHMNQ_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(DHXHMNQ_CMD_POWER_CONTROL, std::bind(&DHXHMNQ_Manager::ParseMsgPowerControl, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(DHXHMNQ_CMD_POWER_STATUS, std::bind(&DHXHMNQ_Manager::ParseMsgPowerStatus, this, std::placeholders::_1));
}

DHXHMNQ_Manager::~DHXHMNQ_Manager()
{
}

DHXHMNQ_Manager* DHXHMNQ_Manager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new DHXHMNQ_Manager(nullptr);
	}
	return m_pInstance;
}

int DHXHMNQ_Manager::ParseMsgPowerControl(PMsgData pPacket)
{
	//导航数据控制 2个字节 自定义 没有用
	return 1;
}

int DHXHMNQ_Manager::ParseMsgPowerStatus(PMsgData pPacket)
{
	//导航状态 2字节 未定义
	return 1;
}

void DHXHMNQ_Manager::RequestVersion()
{
	pUDPServer->WriteData(DHXHMNQ_CMD_VERSION, _ip, _port);
}

void DHXHMNQ_Manager::RequsetSelfCheck()
{
	pUDPServer->WriteData(DHXHMNQ_CMD_SELF_CHECK, _ip, _port);
}

void DHXHMNQ_Manager::RequestPowerControl(char num, char control)
{
	char buf[2] = { 0 };
	buf[0] = num;
	buf[1] = control;
	pUDPServer->WriteData(DHXHMNQ_CMD_POWER_CONTROL, buf, 2, _ip, _port);
}

void DHXHMNQ_Manager::RequestPowerStatus()
{
	pUDPServer->WriteData(DHXHMNQ_CMD_POWER_STATUS, _ip, _port);
}