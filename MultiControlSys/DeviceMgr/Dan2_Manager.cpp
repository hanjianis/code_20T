#include "Dan2_Manager.h"
#include "ZHDY_Manager.h"
Dan2_Manager*  Dan2_Manager::m_pInstance = nullptr;
Dan2_Manager::Dan2_Manager(QObject *parent)
	: DeviceBase(DEV_Dan2, parent)
{
	memset(&_gpsInfo, 0, sizeof(GPS_Info));

	pUDPServer->RegisterEvent(Dan2_CMD_VERSION, std::bind(&Dan2_Manager::ParseMsgVersion, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan2_CMD_SELF_CHECK, std::bind(&Dan2_Manager::ParseMsgSelfCheck, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan2_CMD_POWER_CONTROL, std::bind(&Dan2_Manager::ParseMsgPowerControl, this, std::placeholders::_1));
	pUDPServer->RegisterEvent(Dan2_CMD_POWER_STATUS, std::bind(&Dan2_Manager::ParseMsgPowerStatus, this, std::placeholders::_1));
}

Dan2_Manager::~Dan2_Manager()
{
}

Dan2_Manager* Dan2_Manager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Dan2_Manager(nullptr);
	}
	return m_pInstance;
}
int Dan2_Manager::ParseMsgPowerControl(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerControl";
	if (pPacket->MsgLen < 158)//���鳤�Ȳ���
		return 1;
	int index = 0;
	int tmp = 0;
	_gpsInfo.state = pPacket->msgBuf[index];
	index++;
	//UTC
	memcpy(&_gpsInfo.UTC.Year, &pPacket->msgBuf[index], 2);
	index += 2;
	memcpy(&_gpsInfo.UTC.Month, &pPacket->msgBuf[index], 5);
	index += 5;
	//EW
	_gpsInfo.EW = pPacket->msgBuf[index];
	index += 1;
	memcpy(&tmp, &pPacket->msgBuf[index], 4);
	index += 4;
	_gpsInfo.lon = tmp / 100000.0;
	//NS
	_gpsInfo.NS = pPacket->msgBuf[index];
	index += 1;
	memcpy(&tmp, &pPacket->msgBuf[index], 4);
	index += 4;
	_gpsInfo.lat = tmp / 100000.0;
	//���θ߶�
	memcpy(&tmp, &pPacket->msgBuf[index], 4);
	index += 4;
	_gpsInfo.height = tmp / 10.0;
	//GPS
	_gpsInfo.GpsCnt = pPacket->msgBuf[index];
	index += 1;
	//12��������Ϣ
	for (int i = 0; i < 12; i++)
	{
		_gpsInfo.gpsSate[i].Num = pPacket->msgBuf[index];
		index += 1;
		_gpsInfo.gpsSate[i].heading = pPacket->msgBuf[index];
		index += 1;
		memcpy(&_gpsInfo.gpsSate[i].pitch, &pPacket->msgBuf[index], 2);
		index += 2;
		_gpsInfo.gpsSate[i].ratio = pPacket->msgBuf[index];
		index += 1;
	}
	//����
	_gpsInfo.BeiDouCnt = pPacket->msgBuf[index];
	index += 1;
	//12��������Ϣ
	for (int i = 0; i < 12; i++)
	{
		_gpsInfo.BeiDouSate[i].Num = pPacket->msgBuf[index];
		index += 1;
		_gpsInfo.BeiDouSate[i].heading = pPacket->msgBuf[index];
		index += 1;
		memcpy(&_gpsInfo.BeiDouSate[i].pitch, &pPacket->msgBuf[index], 2);
		index += 2;
		_gpsInfo.BeiDouSate[i].ratio = pPacket->msgBuf[index];
		index += 1;
	}
	//���ڶ�λ��������Ϣ
	_gpsInfo.validSate = pPacket->msgBuf[index];
	index += 1;
	_gpsInfo.validSateCnt = pPacket->msgBuf[index];
	index += 1;
	memcpy(_gpsInfo.validSateNum, &pPacket->msgBuf[index], 12);

	//������Ϣ����Ϣ��label 
	//�ߵ���γ�ȡ�GPS��γ�� ������γ�� ����gpsinfo��ľ�γ��
	QString strLon = QString("%1").arg(_gpsInfo.lon);
	QString strLat = QString("%1").arg(_gpsInfo.lat);
	SetVal(88, strLon);
	SetVal(91, strLon);
	SetVal(93, strLon);
	SetVal(87, strLat);
	SetVal(90, strLat);
	SetVal(92, strLat);
	//GPS�ɼ�������
	SetVal(94, _gpsInfo.GpsCnt);
	//�����ɼ�������
	SetVal(116, _gpsInfo.BeiDouCnt);

	return 1;
}

int Dan2_Manager::ParseMsgPowerStatus(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerStatus";
	if (pPacket->MsgLen < 1)//���鳤�Ȳ���
		return 1;
	_imageFlag = pPacket->msgBuf[0];
	return 1;
}

void Dan2_Manager::RequestVersion()
{
	//��2Ҫ�ȸ��ۺϵ�Դ��4·����
	ZHDY_Manager::getInstance()->RequestPowerControl(4, 1);
	Sleep(200);//�ȴ��ϵ����
	pUDPServer->WriteData(Dan2_CMD_VERSION, _ip, _port);
}

void Dan2_Manager::RequsetSelfCheck()
{
	//��2Ҫ�ȸ��ۺϵ�Դ��4·����
	ZHDY_Manager::getInstance()->RequestPowerControl(4, 1);
	Sleep(200);//�ȴ��ϵ����
	pUDPServer->WriteData(Dan2_CMD_SELF_CHECK, _ip, _port);
}

void Dan2_Manager::RequestPowerControl()
{
	//��2Ҫ�ȸ��ۺϵ�Դ��4·����
	ZHDY_Manager::getInstance()->RequestPowerControl(4, 1);
	Sleep(200);//�ȴ��ϵ����
	pUDPServer->WriteData(Dan2_CMD_POWER_CONTROL, _ip, _port);
}

void Dan2_Manager::RequestPowerStatus()
{
	//��2Ҫ�ȸ��ۺϵ�Դ��4·����
	ZHDY_Manager::getInstance()->RequestPowerControl(4, 1);
	Sleep(10*1000);//�ȴ��ϵ����
	pUDPServer->WriteData(Dan2_CMD_POWER_STATUS, _ip, _port);
}