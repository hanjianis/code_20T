#include "LDGDB_Manager.h"
#include "CK_Manager.h"
LDGDB_Manager*  LDGDB_Manager::m_pInstance = nullptr;
LDGDB_Manager::LDGDB_Manager(QObject *parent)
	: DeviceBase(DEV_LDGDB,parent)
{
	pUDPServer->RegisterEvent(LDGDB_CMD_VERSION, std::bind(&LDGDB_Manager::ParseMsgVersion, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(LDGDB_CMD_SELF_CHECK, std::bind(&LDGDB_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(LDGDB_CMD_POWER_CONTROL, std::bind(&LDGDB_Manager::ParseMsgPowerControl, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(LDGDB_CMD_POWER_STATUS, std::bind(&LDGDB_Manager::ParseMsgPowerStatus, this, std::placeholders::_1));
}

LDGDB_Manager::~LDGDB_Manager()
{
}

LDGDB_Manager* LDGDB_Manager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new LDGDB_Manager(nullptr);
	}
	return m_pInstance;
}

int LDGDB_Manager::ParseMsgVersion(PMsgData pPacket)
{
	DeviceBase::ParseMsgVersion(pPacket);
	int version;
	int low = pPacket->msgBuf[1];
	int high = pPacket->msgBuf[0];
	version = high * 10 + low;
	SetVal(22, version);
	return 1;
}

int LDGDB_Manager::ParseMsgSelfCheck(PMsgData pPacket)
{
	DeviceBase::ParseMsgSelfCheck(pPacket);
	SetVal(21, _checkState);
	return 1;
}

int LDGDB_Manager::ParseMsgPowerControl(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerControl";
	if (pPacket->MsgLen < 4)//数组长度不够
		return 1;

	//雷达高度
	memcpy(&_height, &pPacket->msgBuf[0], 2);
	SetVal(30, _height);
	SetVal(55, _height);
	//衰减值 目前单片机还没有做
	memcpy(&_shuaijian, &pPacket->msgBuf[2], 2);

	//收到高度后 修改自检数据
			
	XLManager* pXL = XLManager::GetInstance();
	AutoTestData &atd = pXL->m_lstMNLTDJC[7][3];//从0开始 第3个是高度
	atd.val = QString("%1").arg(_height);//电压

	AutoTestData &atd2 = pXL->m_lstMNLTDJC[7][4];//从0开始 第4个是衰减值
	atd2.val = QString("%1").arg(_shuaijian);//电压
	return 1;
}

int LDGDB_Manager::ParseMsgPowerStatus(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerStatus";
	if (pPacket->MsgLen < 1)//数组长度不够
		return 1;
	_lineState = pPacket->msgBuf[0];

	if ((_lineState & 0x1) != 0)
		qDebug() << "fa she yi lian jie!";
	if (((_lineState >> 1) & 0x1) != 0)
		qDebug() << "jie shou yi lian jie!";

	return 1;
}

void LDGDB_Manager::RequestVersion()
{
	pUDPServer->WriteData(LDGDB_CMD_VERSION, _ip, _port);
}

void LDGDB_Manager::RequsetSelfCheck()
{
	//先对程控管理器 第10路供电 
	CK_Manager* ck = new CK_Manager(nullptr);
	ck->RequestPowerControl(10, 1);
	//Sleep(10*000);//等待供电完成

	pUDPServer->WriteData(LDGDB_CMD_SELF_CHECK, _ip, _port);
}

void LDGDB_Manager::RequestPowerControl(int height,int shuaijian)
{
	//先对程控管理器 第10路供电 
	CK_Manager* ck = new CK_Manager(nullptr);
	ck->RequestPowerControl(10, 1);
	Sleep(10*1000);//等待1s

	char buf[4] = { 0 };
	memcpy(buf, &height, 2);
	memcpy(buf+2, &shuaijian, 2);
	pUDPServer->WriteData(LDGDB_CMD_POWER_CONTROL, buf, 4, _ip, _port);
	Sleep(200);//等待200ms 等待网络返回 更新内存
}

void LDGDB_Manager::RequestPowerStatus()
{
	//先对程控管理器 第10路供电 
	CK_Manager* ck = new CK_Manager(nullptr);
	ck->RequestPowerControl(10, 1);
	Sleep(1000);//20210604
	pUDPServer->WriteData(LDGDB_CMD_POWER_STATUS, _ip, _port);
	Sleep(200);//等待200ms 等待网络返回 更新内存
}

bool LDGDB_Manager::CheckConneced()
{
    return true;
	//20210604 雷达状态 位0：1时发射已连接 位1：1时接收已连接 两个都正确
	if (((_lineState >> 1) & 0x1) != 0  &&
		((_lineState >> 0) & 0x1) != 0)
		return true;
	return false;
}
