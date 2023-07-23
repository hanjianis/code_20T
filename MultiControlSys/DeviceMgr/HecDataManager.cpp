#include "HecDataManager.h"
#include <QDebug>
#include "../UDPServer.h"
#include "../XLManager.h"
 HecDataManager*  HecDataManager::m_pInstance = nullptr;
HecDataManager::HecDataManager(QObject *parent)
	: QObject(parent)
{
	UDPServer* pUDPServer = UDPServer::getInstance();
	pUDPServer->RegisterEvent(HEC_CMD_POWER_CONTROL, std::bind(&HecDataManager::ParseHecData, this, std::placeholders::_1));
}

HecDataManager::~HecDataManager()
{
}

HecDataManager* HecDataManager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new HecDataManager(nullptr);
	}
	return m_pInstance;
}

void HecDataManager::GetHecData(int tm)
{
	UDPServer* pUDPServer = UDPServer::getInstance();
	char buf[2] = { 0 };
	memcpy(buf, &tm, 2);
    pUDPServer->WriteData(0x1803, buf, 2,QString("192.168.2.70"));
}
void HecDataManager::SetVal(int lableid, double val)
{
	QLabel* lab = XLManager::GetInstance()->m_mapAutoTestList[lableid].val;
	if (lab != nullptr)
		lab->setText(QString("%1").arg(val));
}
int HecDataManager::ParseHecData(PMsgData pPacket)
{
	short tmp = 0;
	double val = 0;
	qDebug() << "ParseHecData ...............";
	//������
	memcpy(&tmp, &pPacket->msgBuf[2], 2);
	val = tmp / 10.0 ;//-90-90 ������+90����
	SetVal(52, val);
	SetVal(102, val);
	SetVal(133, val);
	//������
	memcpy(&tmp, &pPacket->msgBuf[4], 2);
	val = tmp / 10.0;
	SetVal(53, val);
	SetVal(103, val);
	SetVal(134, val);
	//�����
	memcpy(&tmp, &pPacket->msgBuf[6], 2);
	val = tmp / 10.0;
	SetVal(54, val);
	SetVal(104, val);
	SetVal(135, val);

	return 1;
}
