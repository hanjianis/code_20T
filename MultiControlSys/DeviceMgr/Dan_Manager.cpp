#include "Dan_Manager.h"
#include "ZHDY_Manager.h"
Dan_Manager*  Dan_Manager::m_pInstance = nullptr;
Dan_Manager::Dan_Manager(QObject *parent)
	: DeviceBase(DEV_Dan, parent)
{
	pUDPServer->RegisterEvent(Dan_CMD_VERSION, std::bind(&Dan_Manager::ParseMsgVersion, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan_CMD_SELF_CHECK, std::bind(&Dan_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan_CMD_POWER_CONTROL, std::bind(&Dan_Manager::ParseMsgPowerControl, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan_CMD_POWER_STATUS, std::bind(&Dan_Manager::ParseMsgPowerStatus, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan_CMD_LAMP_CONTROL, std::bind(&Dan_Manager::ParseMsgLampControl, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan_CMD_SOUND_CONTROL, std::bind(&Dan_Manager::ParseMsgSoundControl, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan_CMD_TAIL_CONTROL, std::bind(&Dan_Manager::ParseMsgTailControl, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan_CMD_LINE_INFO, std::bind(&Dan_Manager::ParseMsgLineInfo, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan_CMD_EED_INFO, std::bind(&Dan_Manager::ParseMsgEedInfo, this, std::placeholders::_1));
}

Dan_Manager::~Dan_Manager()
{
}

Dan_Manager* Dan_Manager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Dan_Manager(nullptr);
	}
	return m_pInstance;
}
int Dan_Manager::ParseMsgPowerControl(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerControl";
	if (pPacket->MsgLen < 3)//数组长度不够
		return 1;
	int tmp = 1;
	if (pPacket->msgBuf[0] == 1)
		tmp = -1;
	int val = 0;
	memcpy(&val, &pPacket->msgBuf[1], 2);
	_temp = val * tmp / 10.0;
	return 1;
}

int Dan_Manager::ParseMsgPowerStatus(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerStatus";
	if (pPacket->MsgLen < 6)//数组长度不够
		return 1;
	int val = 0;
	memcpy(&val, &pPacket->msgBuf[0], 2);
	_atmosInfo.staticPressure = val  / 10.0;
	memcpy(&val, &pPacket->msgBuf[2], 2);
	_atmosInfo.dynamicPressure1 = val / 10.0;
	memcpy(&val, &pPacket->msgBuf[4], 2);
	_atmosInfo.dynamicPressure2 = val / 10.0;
	return 1;
}

int Dan_Manager::ParseMsgLampControl(PMsgData pPacket)
{
	qDebug() << "Dan_Manager::ParseMsgLampControl";
	if (pPacket->MsgLen < 1)//数组长度不够
		return 1;
	_lamp = pPacket->msgBuf[0];
	return 1;
}

int Dan_Manager::ParseMsgSoundControl(PMsgData pPacket)
{
	qDebug() << "Dan_Manager::ParseMsgLampControl";
	if (pPacket->MsgLen < 1)//数组长度不够
		return 1;
	_sound = pPacket->msgBuf[0];
	return 1;
}

int Dan_Manager::ParseMsgTailControl(PMsgData pPacket)
{
	qDebug() << "Dan_Manager::ParseMsgLampControl";
	if (pPacket->MsgLen < 1)//数组长度不够
		return 1;
	_tailState = pPacket->msgBuf[0];
	return 1;

}

int Dan_Manager::ParseMsgLineInfo(PMsgData pPacket)
{
	qDebug() << "Dan_Manager::ParseMsgLampControl";
	if (pPacket->MsgLen < 4)//数组长度不够
		return 1;
	//20210604
	//前两个字节是光敏电阻的信息， 表示雷达的
	memcpy(&_guanminDianZu, &pPacket->msgBuf[2], 2);
	//bit0-bit13 是连接状态  bit14 bit15表示雷达的
	//后两个字节作为线路连接状态 1个bit位 是1个线路 目前用的14个bit位  后两个bit位 是用于雷达的 也可以通过光敏电阻的值判断 
	memcpy(&_lineState, &pPacket->msgBuf[0], 2);
	return 1;
}

int Dan_Manager::ParseMsgEedInfo(PMsgData pPacket)
{
	//火工品数据 自定义 n 不确定
	qDebug() << "Dan_Manager::ParseMsgEedInfo huo gong pin";
	return 1;
}

bool Dan_Manager::CheckLineConnected()
{
	//检测14个bit位 
	//20210604 判断_lineState的0-13个bit位 全部为0是true 否则为false 不具体到哪条线路
	//bool bConnected = true;
	//
	for (int i = 0; i <= 13; i++)
	{

		if (((_lineState >> i)&(0x1)) == 1) //没连接号
			return false;

	}
	return true;

}

bool Dan_Manager::CheckLeiDaGaoDu()
{
    return true;
	//20210604 判断_lineState的14 15位 两个都是1 如果该值判断不正确 就改用光敏电阻
	if (((_lineState >> 14) & 0x1) != 0 ||
		((_lineState >> 15) & 0x1) != 0)
		return false;
	return true;
}

void Dan_Manager::RequestVersion()
{
	pUDPServer->WriteData(Dan_CMD_VERSION, _ip, _port);
}

void Dan_Manager::RequsetSelfCheck()
{
	pUDPServer->WriteData(Dan_CMD_SELF_CHECK, _ip, _port);
}

void Dan_Manager::RequestPowerControl()
{

	pUDPServer->WriteData(Dan_CMD_POWER_CONTROL, _ip, _port);
}

void Dan_Manager::RequestPowerStatus()
{
	pUDPServer->WriteData(Dan_CMD_POWER_STATUS, _ip, _port);
}

void Dan_Manager::RequestSound(int val)
{
	ZHDY_Manager::getInstance()->RequestPowerControl(1, 1);
	Sleep(200);//等待上电完成
	char buf[1] = { 0 };
	buf[0] = val;
	pUDPServer->WriteData(Dan_CMD_SOUND_CONTROL, buf, 1, _ip, _port);
}

void Dan_Manager::RequestLineInfo()
{
	ZHDY_Manager::getInstance()->RequestPowerControl(1, 1);
	Sleep(1000);//等待上电完成

	pUDPServer->WriteData(Dan_CMD_LINE_INFO, _ip, _port);
}

void Dan_Manager::RequsetLamControl(int val)//未来需要修改
{
	ZHDY_Manager::getInstance()->RequestPowerControl(1, 1);
	Sleep(200);//等待上电完成
	char buf[2] = { 0 };
	buf[0] = 1;
 	buf[1] = val;
	pUDPServer->WriteData(Dan_CMD_LAMP_CONTROL, buf, 2, _ip, _port);
	//pUDPServer->WriteData(Dan_CMD_LAMP_CONTROL, _ip, _port);
}
