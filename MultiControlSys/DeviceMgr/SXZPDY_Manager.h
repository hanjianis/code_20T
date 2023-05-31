#pragma once

#include <QObject>
#include "DeviceBase.h"
struct SXZPDY_Data
{
	int nNum;//编号
	int nFlag;//开关控制 1开 0关

	float fValueV;//电压值
	float fValueA;//电流值
};
class SXZPDY_Manager : public DeviceBase
{
	Q_OBJECT

public:
	SXZPDY_Manager(QObject *parent);
	~SXZPDY_Manager();
private:
	static SXZPDY_Manager* m_pInstance;
	QMap<int, SXZPDY_Data> m_mapSXZPDY;	//电源状态 3路 电压 电流  A B C
public:
	static SXZPDY_Manager* getInstance();

private:
	void ResetMap();
public:
	int ParseMsgPowerStatus(PMsgData pPacket);
public:// 请求方法
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerStatus();
};
