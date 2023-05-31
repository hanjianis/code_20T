#pragma once

#include <QObject>
#include "DeviceBase.h"
class KJGXSMNQ_Manager : public DeviceBase
{
	Q_OBJECT

public:
	KJGXSMNQ_Manager(QObject *parent);
	~KJGXSMNQ_Manager();
private:
	static KJGXSMNQ_Manager* m_pInstance;
public:
	int _imageNum = 0;//图片编号 1-5控制显示5张图片
	int _illLevel = 0;//照度档位状态 0低档位 1高档位
public:
	static KJGXSMNQ_Manager* getInstance();
public:

	int ParseMsgPowerControl(PMsgData pPacket);//景象图片控制
	int ParseMsgPowerStatus(PMsgData pPacket);//获取照度档位状态
public:// 请求方法
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl(char num);//num 编号 景象图片控制
	void RequestPowerStatus();

};
