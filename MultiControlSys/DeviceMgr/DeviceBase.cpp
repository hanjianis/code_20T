#include "DeviceBase.h"

DeviceBase::DeviceBase(int devInfoId,QObject *parent)
	: QObject(parent)
{
	pUDPServer = UDPServer::getInstance();
	//�����ݿ� ����devInfoId ��ȡip port
	//��ʱ����
	XLManager* pXL = XLManager::GetInstance();
	if (pXL != nullptr)
	{
		_ip = pXL->m_mapDevice[devInfoId].ip;
		_port = pXL->m_mapDevice[devInfoId].port;
	}
}

DeviceBase::~DeviceBase()
{
}
void DeviceBase::SetVal(int lableid, double val)
{
	QLabel* lab = XLManager::GetInstance()->m_mapAutoTestList[lableid].val;
	if (lab != nullptr)
		lab->setText(QString("%1").arg(val));
}

void DeviceBase::SetVal(int lableid, int val)
{
	QLabel* lab = XLManager::GetInstance()->m_mapAutoTestList[lableid].val;
	if (lab != nullptr)
		lab->setText(QString("%1").arg(val));
}

void DeviceBase::SetVal(int lableid, QString val)
{
	QLabel* lab = XLManager::GetInstance()->m_mapAutoTestList[lableid].val;
	if (lab != nullptr)
		lab->setText(val);
}

int DeviceBase::ParseMsgVersion(PMsgData pPacket)
{
	qDebug() << "RYJCY_Manager::ParseMsgVersion";
	if (pPacket->MsgLen < 2)//���鳤�Ȳ���
		return 1;
	int low = pPacket->msgBuf[1];
	int high = pPacket->msgBuf[0];
	_version = QString("%1.%2").arg(high).arg(low);
	return 1;
}

int DeviceBase::ParseMsgSelfCheck(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgSelfCheck";
	if (pPacket->MsgLen < 1)//���鳤�Ȳ���
		return 1;
	_checkState = pPacket->msgBuf[0];//�Լ�״̬
	return 1;
}