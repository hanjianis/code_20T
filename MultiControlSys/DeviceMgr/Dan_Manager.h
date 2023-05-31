#pragma once

#include <QObject>
#include "DeviceBase.h"
struct AtmosInfo//大气信息
{
	float staticPressure;//静压
	float dynamicPressure1;//动压1
	float dynamicPressure2;//动压1
};
class Dan_Manager : public DeviceBase
{
	Q_OBJECT

public:
	Dan_Manager(QObject *parent);
	~Dan_Manager();
private:
	static Dan_Manager* m_pInstance;

public:
	static Dan_Manager* getInstance();
public:
	int ParseMsgPowerControl(PMsgData pPacket);//温度信息
	int ParseMsgPowerStatus(PMsgData pPacket);//大气信息
	int ParseMsgLampControl(PMsgData pPacket); //闪光灯信息
	int ParseMsgSoundControl(PMsgData pPacket);//声音控制;
	int ParseMsgTailControl(PMsgData pPacket); //尾翼控制
	int ParseMsgLineInfo(PMsgData pPacket);//线路连接状态
	int ParseMsgEedInfo(PMsgData pPacket);	  //火工品数据
	bool CheckLineConnected();//判断线路连接状态
	bool CheckLeiDaGaoDu();//20210604判断雷达高度表的连接状态
public:// 请求方法
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl();//
	void RequestPowerStatus();
	void RequestSound(int val);//声音 1或者2 两种声音
	void RequestLineInfo();//获取线路连接状态
	void RequsetLamControl(int val);//控制闪光灯打开和关闭 val：1 打开 0：关闭 现在2字节 未来单片机改成1字节 要改成1字节
public:
	float _temp = 0;//温度
	AtmosInfo _atmosInfo;//大气信息
	int _lamp;//闪光灯 1开
	int _sound;//声音标识
	int _tailState;//尾翼
	int _guanminDianZu;//光敏电阻信息 用于判断雷达的连接状态
	unsigned short _lineState = 0;//线路状态 0-31位
	//火工品数据 自定义 n 不确定
};
