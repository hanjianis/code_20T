#pragma once

#include <QObject>
#include "../Packet.h"
#include "../ISysCheckItem.h"
struct SYS_Data
{
	int nNum;//编号
	int nFlag;//开关控制 1开 0关
	int nValue;//int 型值
	float fValue;//电压值
};
class CK_Manager : public ISysCheckItem
{
	Q_OBJECT

public:
    CK_Manager(QObject *parent);
	~CK_Manager();
private:
	//static CK_Manager* m_pInstance;
	//UDPServer* pUDPServer;
	//程控管理设备 系统自检流程 list
	QList<SYS_Data> m_lstSys;
	int _curIndex = 0;//当前流程id 在m_lstSys中的位置
	//int _datatype = 3;
	bool _bCheck;
	
public:
	//static CK_Manager* getInstance();
public:
	int ParseMsgHeartBeat(PMsgData pPacket);
	int ParseMsgVersion(PMsgData pPacket);
	int ParseMsgSelfCheck(PMsgData pPacket);
	int ParseMsgPowerControl(PMsgData pPacket);
	int ParseMsgPowerStatus(PMsgData pPacket);
	int ParseMsgTestIO(PMsgData pPacket);
	//请求消息
	//void RequestHeartBeat();
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl(char num, char control);//num 编号 control 开关控制
	void RequestPowerStatus();
	void RequestTestIO();
	//开始检测
	void StartCheck();
signals:
	void UpdateCheckResultCKSignle(int datatype,int nId, float fVal);
};
