#pragma once
//雷达高度表
#include <QObject>
#include "DeviceBase.h"
class LDGDB_Manager : public DeviceBase
{
	Q_OBJECT

public:
	LDGDB_Manager(QObject *parent);
	~LDGDB_Manager();
private:
	static LDGDB_Manager* m_pInstance;

public:
	static LDGDB_Manager* getInstance();
public:
	int ParseMsgVersion(PMsgData pPacket);
	int ParseMsgSelfCheck(PMsgData pPacket);
	int ParseMsgPowerControl(PMsgData pPacket);//雷达数据控制
	int ParseMsgPowerStatus(PMsgData pPacket);//雷达状态
public:// 请求方法
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl(int  height,int shuaijian);//height 高度 雷达数据控制
	void RequestPowerStatus();
	bool CheckConneced();//20210604 _lineState 连接线路连接状态
public:
	int _height = 0;//雷达高度 2字节 单位米
	int _shuaijian = 0;//衰减值
	char _lineState = 0;//雷达状态 位0：1时发射已连接 位1：1时接收已连接
	bool _bConnectSuccess = false;//上电是否成功的标识 等待心跳
};
