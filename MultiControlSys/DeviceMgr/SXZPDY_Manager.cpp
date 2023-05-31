#include "SXZPDY_Manager.h"
SXZPDY_Manager*  SXZPDY_Manager::m_pInstance = nullptr;
SXZPDY_Manager::SXZPDY_Manager(QObject *parent)
	: DeviceBase(DEV_SXZPDY,parent)
{
	pUDPServer->RegisterEvent(SXZPDY_CMD_VERSION, std::bind(&SXZPDY_Manager::ParseMsgVersion, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(SXZPDY_CMD_SELF_CHECK, std::bind(&SXZPDY_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(SXZPDY_CMD_POWER_STATUS, std::bind(&SXZPDY_Manager::ParseMsgPowerStatus, this, std::placeholders::_1));
}

SXZPDY_Manager::~SXZPDY_Manager()
{
}

SXZPDY_Manager* SXZPDY_Manager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SXZPDY_Manager(nullptr);
	}
	return m_pInstance;
}

void SXZPDY_Manager::ResetMap()
{
	//��ʼ��map 3·
	for (int i = 0; i < 8; i++)
	{
		SXZPDY_Data dt;
		memset(&dt, 0, sizeof(SXZPDY_Data));
		dt.nNum = i + 1;
		m_mapSXZPDY[i + 1] = dt;
	}
}

int SXZPDY_Manager::ParseMsgPowerStatus(PMsgData pPacket)
{
	qDebug() << "SXZPDY_Manager::ParseMsgPowerStatus";
	if (pPacket->MsgLen < 4 * 2 * 3)//���鳤�Ȳ���
		return 1;
	// ��ѹ(4�ֽڣ� ���� ��3· 
	for (int i = 0; i < 3; i++)
	{
		SXZPDY_Data &dt = m_mapSXZPDY[i + 1];
		int *cmd = (int*)&(pPacket->msgBuf[2*i * 4]);//��ѹ
		if (*cmd == 0xFFFFFFFF)//��ʾ��Դ�ر�
		{
			dt.fValueV = 0;
			dt.fValueA = 0;
		}
		else
		{
			dt.fValueV = (*cmd) / 65536.0;
			cmd = (int*)&(pPacket->msgBuf[(2*i+1) * 4]);//����
			dt.fValueA = (*cmd) / 65536.0;
		}
		//����ϵͳ�Լ�ʱ ������
		XLManager* pXL = XLManager::GetInstance();
		AutoTestData &atd = pXL->m_lstMNLTDJC[5][i];
		atd.val = QString("%1").arg(dt.fValueV);//��ѹ
	}


	return 1;
}

void SXZPDY_Manager::RequestVersion()
{
	pUDPServer->WriteData(SXZPDY_CMD_VERSION, _ip, _port);
}

void SXZPDY_Manager::RequsetSelfCheck()
{
	pUDPServer->WriteData(SXZPDY_CMD_SELF_CHECK, _ip, _port);
}

void SXZPDY_Manager::RequestPowerStatus()
{
	pUDPServer->WriteData(SXZPDY_CMD_POWER_STATUS, _ip, _port);
}
