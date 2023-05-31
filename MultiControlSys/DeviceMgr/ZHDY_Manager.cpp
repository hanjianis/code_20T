#include "ZHDY_Manager.h"
#include "../UDPServer.h"

#include <QDebug>
#include "../XLManager.h"
ZHDY_Manager*  ZHDY_Manager::m_pInstance = nullptr;

void ZHDY_Manager::ResetMap()
{
	//初始化map 8路
	for (int i = 0; i < 8; i++)
	{
		ZHDY_Data dt;
		memset(&dt, 0, sizeof(ZHDY_Data));
		dt.nNum = i + 1;
		m_mapZHDY[i + 1] = dt;
	}
}

ZHDY_Manager::ZHDY_Manager(QObject *parent)
	: DeviceBase(DEV_ZHDY,parent)
{
	//从数据库拿到ip 端口
	ResetMap();
	

	pUDPServer->RegisterEvent(ZHDY_CMD_VERSION, std::bind(&ZHDY_Manager::ParseMsgVersion, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(ZHDY_CMD_SELF_CHECK, std::bind(&ZHDY_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(ZHDY_CMD_POWER_CONTROL, std::bind(&ZHDY_Manager::ParseMsgPowerControl, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(ZHDY_CMD_POWER_STATUS, std::bind(&ZHDY_Manager::ParseMsgPowerStatus, this, std::placeholders::_1));
	
}

ZHDY_Manager::~ZHDY_Manager()
{
}
ZHDY_Manager* ZHDY_Manager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ZHDY_Manager(nullptr);
	}
	return m_pInstance;
}

int ZHDY_Manager::ParseMsgPowerControl(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerControl";
	if (pPacket->MsgLen < 2)//数组长度不够
		return 1;
	int num = pPacket->msgBuf[0];
	if (num > 8)
	{
		qDebug() << "ZHDY_Manager::ParseMsgPowerControl error";
		return 1;
	}
	ZHDY_Data &dt = m_mapZHDY[num];

	dt.nFlag = pPacket->msgBuf[1];//更新开关状态

	return 1;
}

int ZHDY_Manager::ParseMsgPowerStatus(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerStatus";
	if (pPacket->MsgLen < 4 * 2 * 8)//数组长度不够
		return 1;
	// 电压(4字节） 电流 共8路 
	for (int i = 0; i < 8; i++)
	{
		ZHDY_Data &dt = m_mapZHDY[i+1];
		int *cmd = (int*)&(pPacket->msgBuf[2*i * 4]);//电压
		if (*cmd == 0xFFFFFFFF)//表示电源关闭
		{
			dt.fValueV = 0;
			dt.fValueA = 0;
		}
		else
		{
			dt.fValueV = (*cmd) / 65536.0;
			cmd = (int*)&(pPacket->msgBuf[(2*+1)* 4]);//电流
			dt.fValueA = (*cmd) / 65536.0;
		}
		//更新自检的电压
		XLManager* pXL = XLManager::GetInstance();
		if (i < 6)
		{
			AutoTestData& atd = pXL->m_lstMNLTDJC[4][i];//不知道为什么界面上 只有 1 2 3 4 5 6 8路
			atd.val = QString("%1").arg(dt.fValueV);
		}
		else if(i == 7)
		{
			AutoTestData& atd = pXL->m_lstMNLTDJC[4][6];//不知道为什么界面上 只有 1 2 3 4 5 6 8路 更新第6 从0开始
			atd.val = QString("%1").arg(dt.fValueV);

		}
	}
	return 1;
}

void ZHDY_Manager::RequestVersion()
{
	pUDPServer->WriteData(ZHDY_CMD_VERSION, _ip, _port);
}

void ZHDY_Manager::RequsetSelfCheck()
{
	pUDPServer->WriteData(ZHDY_CMD_SELF_CHECK, _ip, _port);
}

void ZHDY_Manager::RequestPowerControl(char num, char control)
{
	char buf[2] = { 0 };
	buf[0] = num;
	buf[1] = control;
	pUDPServer->WriteData(ZHDY_CMD_POWER_CONTROL,buf,2, _ip, _port);
}

void ZHDY_Manager::RequestPowerStatus()
{
	pUDPServer->WriteData(ZHDY_CMD_POWER_STATUS, _ip, _port);
}
