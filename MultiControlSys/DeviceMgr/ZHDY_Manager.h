#pragma once

#include <QObject>
#include "DeviceBase.h"
//综合电源
struct ZHDY_Data
{
	int nNum;//编号
	int nFlag;//开关控制 1开 0关

	float fValueV;//电压值
	float fValueA;//电流值
};
class ZHDY_Manager : public DeviceBase
{
	Q_OBJECT

public:
	ZHDY_Manager(QObject *parent);
	~ZHDY_Manager();
private:
	static ZHDY_Manager* m_pInstance;
	

	QMap<int, ZHDY_Data> m_mapZHDY;	//电源状态 8路 电压 电流 

private:
	void ResetMap();
public:
	static ZHDY_Manager* getInstance();
public:

	int ParseMsgPowerControl(PMsgData pPacket);
	int ParseMsgPowerStatus(PMsgData pPacket);
public:// 请求方法
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl(char num, char control);//num 编号 control 开关控制
	void RequestPowerStatus();
};
