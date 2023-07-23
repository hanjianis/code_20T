#pragma once

#include <QObject>
#include "DeviceBase.h"
class DHXHMNQ_Manager : public DeviceBase
{
	Q_OBJECT

public:
	DHXHMNQ_Manager(QObject *parent);
	~DHXHMNQ_Manager();
private:
	static DHXHMNQ_Manager* m_pInstance;//aaaaaa
	//导航数据控制
public:
	static DHXHMNQ_Manager* getInstance();
public:
	int ParseMsgPowerControl(PMsgData pPacket);//导航数据控制
	int ParseMsgPowerStatus(PMsgData pPacket);//导航状态
public:// 请求方法
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl(char num, char control);//n导航数据控制 自定义
	void RequestPowerStatus();
};
