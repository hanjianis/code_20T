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
	if (pPacket->MsgLen < 158)//数组长度不够
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
	//海拔高度
	memcpy(&tmp, &pPacket->msgBuf[index], 4);
	index += 4;
	_gpsInfo.height = tmp / 10.0;
	//GPS
	_gpsInfo.GpsCnt = pPacket->msgBuf[index];
	index += 1;
	//12个卫星信息
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
	//北斗
	_gpsInfo.BeiDouCnt = pPacket->msgBuf[index];
	index += 1;
	//12个卫星信息
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
	//用于定位的卫星信息
	_gpsInfo.validSate = pPacket->msgBuf[index];
	index += 1;
	_gpsInfo.validSateCnt = pPacket->msgBuf[index];
	index += 1;
	memcpy(_gpsInfo.validSateNum, &pPacket->msgBuf[index], 12);

	//设置信息到信息栏label 
	//惯导经纬度、GPS经纬度 北斗经纬度 都是gpsinfo里的经纬度
	QString strLon = QString("%1").arg(_gpsInfo.lon);
	QString strLat = QString("%1").arg(_gpsInfo.lat);
	SetVal(88, strLon);
	SetVal(91, strLon);
	SetVal(93, strLon);
	SetVal(87, strLat);
	SetVal(90, strLat);
	SetVal(92, strLat);
	//GPS可见卫星数
	SetVal(94, _gpsInfo.GpsCnt);
	//北斗可见卫星数
	SetVal(116, _gpsInfo.BeiDouCnt);

	return 1;
}

int Dan2_Manager::ParseMsgPowerStatus(PMsgData pPacket)
{
	qDebug() << "ZHDY_Manager::ParseMsgPowerStatus";
	if (pPacket->MsgLen < 1)//数组长度不够
		return 1;
	_imageFlag = pPacket->msgBuf[0];
	return 1;
}

void Dan2_Manager::RequestVersion()
{
	//弹2要先给综合电源第4路供电
	ZHDY_Manager::getInstance()->RequestPowerControl(4, 1);
	Sleep(200);//等待上电完成
	pUDPServer->WriteData(Dan2_CMD_VERSION, _ip, _port);
}

void Dan2_Manager::RequsetSelfCheck()
{
	//弹2要先给综合电源第4路供电
	ZHDY_Manager::getInstance()->RequestPowerControl(4, 1);
	Sleep(200);//等待上电完成
	pUDPServer->WriteData(Dan2_CMD_SELF_CHECK, _ip, _port);
}

void Dan2_Manager::RequestPowerControl()
{
	//弹2要先给综合电源第4路供电
	ZHDY_Manager::getInstance()->RequestPowerControl(4, 1);
	Sleep(200);//等待上电完成
	pUDPServer->WriteData(Dan2_CMD_POWER_CONTROL, _ip, _port);
}

void Dan2_Manager::RequestPowerStatus()
{
	//弹2要先给综合电源第4路供电
	ZHDY_Manager::getInstance()->RequestPowerControl(4, 1);
	Sleep(10*1000);//等待上电完成
	pUDPServer->WriteData(Dan2_CMD_POWER_STATUS, _ip, _port);
}