#include "CK_Manager.h"
#include "../UDPServer.h"

#include <QDebug>
#include "../XLManager.h"
//CK_Manager* CK_Manager::m_pInstance = nullptr;
CK_Manager::CK_Manager(QObject *parent)
	: ISysCheckItem(SYS_CK,parent)
{

    pUDPServer->RegisterEvent(CK_CMD_VERSION, std::bind(&CK_Manager::ParseMsgVersion, this, std::placeholders::_1));       //需要研究
	pUDPServer->RegisterEvent(CK_CMD_SELF_CHECK, std::bind(&CK_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(CK_CMD_POWER_CONTROL, std::bind(&CK_Manager::ParseMsgPowerControl, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(CK_CMD_POWER_STATUS, std::bind(&CK_Manager::ParseMsgPowerStatus, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(CK_CMD_TEST_IO, std::bind(&CK_Manager::ParseMsgTestIO, this, std::placeholders::_1));
    //就是是和设备有关？
    for (int i = 0; i < 10; i++)
	{
		SYS_Data sys;
		sys.nNum =i+1;//编号 第几路
		sys.nFlag = 0x01;//打开
		m_lstSys.push_back(sys);
		//关闭
		sys.nFlag = 0x00;
		m_lstSys.push_back(sys);
	}
	connect(this, SIGNAL(UpdateCheckResultCKSignle(int,int, float)), parent, SLOT(UpdateCheckResultCK(int,int, float)));
	_bCheck = false;
	
}

CK_Manager::~CK_Manager()
{
}
//CK_Manager* CK_Manager::getInstance()
//{
//	if (m_pInstance == nullptr)
//	{
//		m_pInstance = new CK_Manager(nullptr);
//	}
//	return m_pInstance;
//}

int CK_Manager::ParseMsgHeartBeat(PMsgData pPacket)
{
	qDebug() << "heart beat....";
	return 1;
}

int CK_Manager::ParseMsgVersion(PMsgData pPacket)
{
	//版本高位（1字节），版本低位（1字节）。 0x0100 V1.0
	qDebug() << "Version...";
	QString strVer = QString("%1.%2").arg(pPacket->msgBuf[0]).arg(pPacket->msgBuf[1]);
	qDebug() << strVer;
	return 1;
}

int CK_Manager::ParseMsgSelfCheck(PMsgData pPacket)
{
	qDebug() << "self check...";
	qDebug() << pPacket->msgBuf;

	return 1;
}

int CK_Manager::ParseMsgPowerControl(PMsgData pPacket)
{
	qDebug() << "PowerControl...";
	qDebug() << pPacket->msgBuf[0];
	qDebug() << pPacket->msgBuf[1];
	//收到下位机响应 获取电压值
	Sleep(500);
	RequestPowerStatus();
	return 1;
}

int CK_Manager::ParseMsgPowerStatus(PMsgData pPacket)
{
	qDebug() << "Power Status...";
	//更新缓存
	//电压值 10个
	for (int i = 0; i < 10; i++)
	{
		int* cmd = (int*)&(pPacket->msgBuf[2*i * 4]);//只取了电压值
		m_lstSys[i].nValue = *cmd;
		if (*cmd == 0xFFFFFFFF)//表示电源关闭
		{
			m_lstSys[i].fValue = 0;//
			m_lstSys[2 * i + 1].fValue = 0;
		}
		else
		{
			m_lstSys[i].fValue = (*cmd) / 65536.0;
			m_lstSys[2 * i + 1].fValue = (*cmd) / 65536.0;
	
		}

	}
		
	//进行数据判断
	XLManager* pXL = XLManager::GetInstance();
	AutoTestData& atd = pXL->m_lstMNLTDJC[_datatype][_curIndex];
	atd.val = QString::number(m_lstSys[_curIndex/2].fValue, 'f', 1);;
	if (atd.num % 2 == 0)//流程是关闭电源
	{
		if (m_lstSys[_curIndex/2].nValue == 0xFFFFFFFF)//电源关闭
			atd.content = 1;
		else
			atd.content = 0;
	}
	else//流程是打开电源
	{
		if (m_lstSys[_curIndex/2].nValue == 0xFFFFFFFF)//电源关闭
			atd.content = 0;
		else
			atd.content = 1;
	}
	
	if (_bCheck)
	{
		//提交信号
		emit UpdateCheckResultCKSignle(_datatype,_curIndex, m_lstSys[_curIndex].fValue);
		//开始下一个检测
		_curIndex++;
		if (_curIndex < m_lstSys.size())
			RequestPowerControl(m_lstSys[_curIndex].nNum, m_lstSys[_curIndex].nFlag);
		else
		{
			_bCheck = false;
			_stop = true;
		}
	}
	return 1;
}

int CK_Manager::ParseMsgTestIO(PMsgData pPacket)
{
	qDebug() << "IO.....";
	//4个开关量
	for (int i = 0; i < 4; i++)
	{
		//qDebug() << i << "====" << pPacket->msgBuf[i];
	}
	return 1;
}

void CK_Manager::RequestVersion()
{
	pUDPServer->WriteData(CK_CMD_VERSION);
}

void CK_Manager::RequsetSelfCheck()
{
	pUDPServer->WriteData(CK_CMD_SELF_CHECK);
}

void CK_Manager::RequestPowerControl(char num, char control)
{
	char buf[2] = { 0 };
	buf[0] = num;
	buf[1] = control;
	pUDPServer->WriteData(CK_CMD_POWER_CONTROL, buf, 2);
}

void CK_Manager::RequestPowerStatus()
{
	pUDPServer->WriteData(CK_CMD_POWER_STATUS);
}

void CK_Manager::RequestTestIO()
{
	pUDPServer->WriteData(CK_CMD_TEST_IO);
}

void CK_Manager::StartCheck()
{
	//从list里 取出 第一个 进行请求
	_curIndex = 0;
	SYS_Data sys = m_lstSys.front();
	RequestPowerControl(sys.nNum, sys.nFlag);
	_bCheck = true;
}

