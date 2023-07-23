#include "SPQ_Manager.h"
SPQ_Manager*  SPQ_Manager::m_pInstance = nullptr;
SPQ_Manager::SPQ_Manager(QObject *parent)
	: DeviceBase(DEV_SPQ,parent)
{

	pUDPServer->RegisterEvent(SPQ_CMD_VERSION, std::bind(&SPQ_Manager::ParseMsgVersion, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(SPQ_CMD_SELF_CHECK, std::bind(&SPQ_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(SPQ_CMD_POWER_CONTROL, std::bind(&SPQ_Manager::ParseMsgPowerControl, this, std::placeholders::_1));
}

SPQ_Manager::~SPQ_Manager()
{
}

SPQ_Manager* SPQ_Manager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SPQ_Manager(nullptr);
	}
	return m_pInstance;
}

int SPQ_Manager::ParseMsgPowerControl(PMsgData pPacket)
{
	qDebug() << "SPQ_Manager::ParseMsgPowerStatus";
	if (pPacket->MsgLen < 4)//���鳤�Ȳ���
		return 1;
	//4�ֽ� 0-31λ
	int *cmd = (int*)&(pPacket->msgBuf[0]);//��ѹ
	_lineState = *cmd;
	//ʹ����2-10λ 0���Ӻ� 1û���Ӻ�   2---- X151   3---- X152
	//4---- 13X3
	//5---- X154
	//6---- X119
	//7---- X145
	//8---- X100-3X3
	//9---- X100-3X5
	//10---- X100-3X6
	return 1;
}

bool SPQ_Manager::CheckLineConnected()
{
	bool bConnected = true;
	//Ŀǰ��4λ�����
	for (int i = 2; i <=10;i++)
	{
		if (i != 4)
		{
			if (_lineState&(0x1 << i)) //û���Ӻ�
				bConnected = false;
		}
	}
	return bConnected;
}

#pragma region ����
void SPQ_Manager::RequestVersion()
{
	pUDPServer->WriteData(SPQ_CMD_VERSION, _ip, _port);
}

void SPQ_Manager::RequsetSelfCheck()
{
	pUDPServer->WriteData(SPQ_CMD_SELF_CHECK, _ip, _port);
}

void SPQ_Manager::RequestPowerControl()
{
	pUDPServer->WriteData(SPQ_CMD_POWER_CONTROL, _ip, _port);
}
#pragma endregion

