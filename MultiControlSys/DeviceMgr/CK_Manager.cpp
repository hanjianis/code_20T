#include "CK_Manager.h"
#include "../UDPServer.h"

#include <QDebug>
#include "../XLManager.h"
//CK_Manager* CK_Manager::m_pInstance = nullptr;
CK_Manager::CK_Manager(QObject *parent)
	: ISysCheckItem(SYS_CK,parent)
{

    pUDPServer->RegisterEvent(CK_CMD_VERSION, std::bind(&CK_Manager::ParseMsgVersion, this, std::placeholders::_1));       //��Ҫ�о�
	pUDPServer->RegisterEvent(CK_CMD_SELF_CHECK, std::bind(&CK_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(CK_CMD_POWER_CONTROL, std::bind(&CK_Manager::ParseMsgPowerControl, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(CK_CMD_POWER_STATUS, std::bind(&CK_Manager::ParseMsgPowerStatus, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(CK_CMD_TEST_IO, std::bind(&CK_Manager::ParseMsgTestIO, this, std::placeholders::_1));
    //�����Ǻ��豸�йأ�
    for (int i = 0; i < 10; i++)
	{
		SYS_Data sys;
		sys.nNum =i+1;//��� �ڼ�·
		sys.nFlag = 0x01;//��
		m_lstSys.push_back(sys);
		//�ر�
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
	//�汾��λ��1�ֽڣ����汾��λ��1�ֽڣ��� 0x0100 V1.0
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
	//�յ���λ����Ӧ ��ȡ��ѹֵ
	Sleep(500);
	RequestPowerStatus();
	return 1;
}

int CK_Manager::ParseMsgPowerStatus(PMsgData pPacket)
{
	qDebug() << "Power Status...";
	//���»���
	//��ѹֵ 10��
	for (int i = 0; i < 10; i++)
	{
		int* cmd = (int*)&(pPacket->msgBuf[2*i * 4]);//ֻȡ�˵�ѹֵ
		m_lstSys[i].nValue = *cmd;
		if (*cmd == 0xFFFFFFFF)//��ʾ��Դ�ر�
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
		
	//���������ж�
	XLManager* pXL = XLManager::GetInstance();
	AutoTestData& atd = pXL->m_lstMNLTDJC[_datatype][_curIndex];
	atd.val = QString::number(m_lstSys[_curIndex/2].fValue, 'f', 1);;
	if (atd.num % 2 == 0)//�����ǹرյ�Դ
	{
		if (m_lstSys[_curIndex/2].nValue == 0xFFFFFFFF)//��Դ�ر�
			atd.content = 1;
		else
			atd.content = 0;
	}
	else//�����Ǵ򿪵�Դ
	{
		if (m_lstSys[_curIndex/2].nValue == 0xFFFFFFFF)//��Դ�ر�
			atd.content = 0;
		else
			atd.content = 1;
	}
	
	if (_bCheck)
	{
		//�ύ�ź�
		emit UpdateCheckResultCKSignle(_datatype,_curIndex, m_lstSys[_curIndex].fValue);
		//��ʼ��һ�����
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
	//4��������
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
	//��list�� ȡ�� ��һ�� ��������
	_curIndex = 0;
	SYS_Data sys = m_lstSys.front();
	RequestPowerControl(sys.nNum, sys.nFlag);
	_bCheck = true;
}

