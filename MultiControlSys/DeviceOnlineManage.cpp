#include "DeviceOnlineManage.h"
#include "UDPServer.h"
#include "TCPClient.h"
#include "XLManager.h"
DeviceOnlineManage* DeviceOnlineManage::m_pInstance = nullptr;
DeviceOnlineManage::DeviceOnlineManage(QObject *parent)
	: QObject(parent)
{
	m_nDeviceOnlineFlag = 0;
	UDPServer* pUDPServer = UDPServer::getInstance();
	//ע����������ķ���
	pUDPServer->RegisterEvent(HEC_CMD_HEARD_BEAT, std::bind(&DeviceOnlineManage::ParseMsgHeartBeat, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(CK_CMD_HEARD_BEAT, std::bind(&DeviceOnlineManage::ParseMsgHeartBeat, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(ZHDY_CMD_HEARD_BEAT, std::bind(&DeviceOnlineManage::ParseMsgHeartBeat, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(RYJCY_CMD_HEARD_BEAT, std::bind(&DeviceOnlineManage::ParseMsgHeartBeat, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(SXZPDY_CMD_HEARD_BEAT, std::bind(&DeviceOnlineManage::ParseMsgHeartBeat, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(SPQ_CMD_HEARD_BEAT, std::bind(&DeviceOnlineManage::ParseMsgHeartBeat, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(DHXHMNQ_CMD_HEARD_BEAT, std::bind(&DeviceOnlineManage::ParseMsgHeartBeat, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(KJGXSMNQ_CMD_HEARD_BEAT, std::bind(&DeviceOnlineManage::ParseMsgHeartBeat, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(LDGDB_CMD_HEARD_BEAT, std::bind(&DeviceOnlineManage::ParseMsgHeartBeat, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan2_CMD_HEARD_BEAT, std::bind(&DeviceOnlineManage::ParseMsgHeartBeat, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan_CMD_HEARD_BEAT, std::bind(&DeviceOnlineManage::ParseMsgHeartBeat, this, std::placeholders::_1));
	m_Timer = new QTimer();
	connect(m_Timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
	m_Timer->start(3000);
}

DeviceOnlineManage::~DeviceOnlineManage()
{
}

DeviceOnlineManage* DeviceOnlineManage::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new DeviceOnlineManage(nullptr);
	}
	return m_pInstance;
}

int DeviceOnlineManage::ParseMsgHeartBeat(PMsgData pPacket)
{
	if (pPacket->MsgId == CK_CMD_HEARD_BEAT)//�̿ع�����
	{

	}
	if (pPacket->MsgId == ZHDY_CMD_HEARD_BEAT)//�ۺϵ�Դ
	{

	}
	//������������ �ҵ���Ӧ�豸��onlineflag ��sqlite�ﶨ��� 
	XLManager* pXL = XLManager::GetInstance();
	DeviceInfo& dev = pXL->m_mapDevice[pPacket->MsgId];
	if((&dev) !=nullptr)
		m_nDeviceOnlineFlag |= dev.onlineflag;//
	//�ϱ�������

	return 1;
}

void DeviceOnlineManage::on_timeout()
{
	//û�иı�ʱ ������
	if (m_nPreDeviceOnlineFlag == m_nDeviceOnlineFlag)
		return;

	m_nPreDeviceOnlineFlag = m_nDeviceOnlineFlag;
	TCPClient* pTcp = TCPClient::GetInstance();

//	Msg_T_Online_Device msg;
//	msg.set_onlineflag(m_nDeviceOnlineFlag);
//	MsgData pMsg;
//	pMsg.MsgId = eMsg_T_OnLine_Device;
//	pMsg.MsgLen = msg.ByteSize();
//	pMsg.msgBuf = new char[pMsg.MsgLen];
//	if (msg.SerializeToArray(pMsg.msgBuf, pMsg.MsgLen))
//	{
//		pTcp->SendMsg(&pMsg);
//	}
	//m_nDeviceOnlineFlag = 0;
	//δ��Ҫ���� �����ߵ�ʱ�����ĳ���豸
}
