#include "KJGXSMNQ_Manager.h"
#include "ZHDY_Manager.h"
KJGXSMNQ_Manager*  KJGXSMNQ_Manager::m_pInstance = nullptr;
KJGXSMNQ_Manager::KJGXSMNQ_Manager(QObject *parent)
	: DeviceBase(DEV_KJGXSMNQ, parent)
{
	pUDPServer->RegisterEvent(KJGXSMNQ_CMD_VERSION, std::bind(&KJGXSMNQ_Manager::ParseMsgVersion, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(KJGXSMNQ_CMD_SELF_CHECK, std::bind(&KJGXSMNQ_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(KJGXSMNQ_CMD_POWER_CONTROL, std::bind(&KJGXSMNQ_Manager::ParseMsgPowerControl, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(KJGXSMNQ_CMD_POWER_STATUS, std::bind(&KJGXSMNQ_Manager::ParseMsgPowerStatus, this, std::placeholders::_1));
}

KJGXSMNQ_Manager::~KJGXSMNQ_Manager()
{
}

KJGXSMNQ_Manager* KJGXSMNQ_Manager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new KJGXSMNQ_Manager(nullptr);
	}
	return m_pInstance;
}
int KJGXSMNQ_Manager::ParseMsgPowerControl(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerControl";
	if (pPacket->MsgLen < 1)//数组长度不够
		return 1;
	_imageNum = pPacket->msgBuf[0];

	return 1;
}

int KJGXSMNQ_Manager::ParseMsgPowerStatus(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerStatus";
	if (pPacket->MsgLen < 1)//数组长度不够
		return 1;
	_illLevel = pPacket->msgBuf[0];
	return 1;
}

void KJGXSMNQ_Manager::RequestVersion()
{

	pUDPServer->WriteData(KJGXSMNQ_CMD_VERSION, _ip, _port);
}

void KJGXSMNQ_Manager::RequsetSelfCheck()
{
	//先对综合电源 第7路供电 
	ZHDY_Manager::getInstance()->RequestPowerControl(7, 1);// *ck = new CK_Manager(nullptr);

	Sleep(10*1000);

	pUDPServer->WriteData(KJGXSMNQ_CMD_SELF_CHECK, _ip, _port);
}

void KJGXSMNQ_Manager::RequestPowerControl(char num)
{
	//先对程控管理器 第7路供电 
	ZHDY_Manager::getInstance()->RequestPowerControl(7, 1);
	
	Sleep(1*1000);//1s
	//需要找到1个地方 关闭程控管理器第7路电

	char buf[1] = { 0 };
	buf[0] = num;
	pUDPServer->WriteData(KJGXSMNQ_CMD_POWER_CONTROL, buf, 1, _ip, _port);
}

void KJGXSMNQ_Manager::RequestPowerStatus()
{
	pUDPServer->WriteData(KJGXSMNQ_CMD_POWER_STATUS, _ip, _port);
}
