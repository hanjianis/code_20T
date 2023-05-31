#pragma once

#include <QObject>

#include "DeviceBase.h"
//燃油检测仪
class RYJCY_Manager : public DeviceBase
{
	Q_OBJECT

public:
	RYJCY_Manager(QObject *parent);
	~RYJCY_Manager();
private:
	static RYJCY_Manager* m_pInstance;
	
public:
	//开关状态 0：关 1：开
	int _MYFlag=0;//满油开关
	int _KYFlag=0;//空油开关
	int _GBGDFlag = 0;//给泵供电开关
	int _DKDSFlag = 0;//断开弹上开关
	int _CJFlag = 0;//插件开关
public:
	static RYJCY_Manager* getInstance();
public:
	int ParseMsgPowerControl(PMsgData pPacket);
public:// 请求方法
	void RequestVersion();
	void RequsetSelfCheck();
	void RequsetPowerControl();
};
