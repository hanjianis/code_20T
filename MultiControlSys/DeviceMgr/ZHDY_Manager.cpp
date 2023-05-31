#include "ZHDY_Manager.h"
#include "../UDPServer.h"

#include <QDebug>
#include "../XLManager.h"
ZHDY_Manager*  ZHDY_Manager::m_pInstance = nullptr;

void ZHDY_Manager::ResetMap()
{
	//��ʼ��map 8·
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
	//�����ݿ��õ�ip �˿�
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
	if (pPacket->MsgLen < 2)//���鳤�Ȳ���
		return 1;
	int num = pPacket->msgBuf[0];
	if (num > 8)
	{
		qDebug() << "ZHDY_Manager::ParseMsgPowerControl error";
		return 1;
	}
	ZHDY_Data &dt = m_mapZHDY[num];

	dt.nFlag = pPacket->msgBuf[1];//���¿���״̬

	return 1;
}

int ZHDY_Manager::ParseMsgPowerStatus(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerStatus";
	if (pPacket->MsgLen < 4 * 2 * 8)//���鳤�Ȳ���
		return 1;
	// ��ѹ(4�ֽڣ� ���� ��8· 
	for (int i = 0; i < 8; i++)
	{
		ZHDY_Data &dt = m_mapZHDY[i+1];
		int *cmd = (int*)&(pPacket->msgBuf[2*i * 4]);//��ѹ
		if (*cmd == 0xFFFFFFFF)//��ʾ��Դ�ر�
		{
			dt.fValueV = 0;
			dt.fValueA = 0;
		}
		else
		{
			dt.fValueV = (*cmd) / 65536.0;
			cmd = (int*)&(pPacket->msgBuf[(2*+1)* 4]);//����
			dt.fValueA = (*cmd) / 65536.0;
		}
		//�����Լ�ĵ�ѹ
		XLManager* pXL = XLManager::GetInstance();
		if (i < 6)
		{
			AutoTestData& atd = pXL->m_lstMNLTDJC[4][i];//��֪��Ϊʲô������ ֻ�� 1 2 3 4 5 6 8·
			atd.val = QString("%1").arg(dt.fValueV);
		}
		else if(i == 7)
		{
			AutoTestData& atd = pXL->m_lstMNLTDJC[4][6];//��֪��Ϊʲô������ ֻ�� 1 2 3 4 5 6 8· ���µ�6 ��0��ʼ
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
