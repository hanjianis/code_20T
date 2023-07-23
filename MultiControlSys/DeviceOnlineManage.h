
#ifndef _DEVICE_ONLINE_MANAGE_H
#define _DEVICE_ONLINE_MANAGE_H

#pragma once

#include <QObject>
#include "Packet.h"
#include <QTimer>
//设备在线状态的管理 udp设备 用于监听所有udp设备的心跳 并上报给导调使用的
//逻辑是 根据心跳的UDP命令 从数据库找到相应的在线标识 发送给导调 导调根据在线标识区分设备
//在线标识 各设备是不同的 是按照各占bit位定义的 按照&运算就可以进行区分

class DeviceOnlineManage : public QObject
{
	Q_OBJECT

public:
	DeviceOnlineManage(QObject *parent);
	~DeviceOnlineManage();
public:
	int m_nDeviceOnlineFlag;//在线标识 各个设备在线标识的|运算的结果
	int m_nPreDeviceOnlineFlag = 0;//上一状态 因为udp设备是根据心跳判断是否在线的 所以保存上一个状态 当状态不一致时 才上报给导调
	QTimer* m_Timer;//用于重置在线状态的定时器
private:
	static DeviceOnlineManage* m_pInstance;//静态变量
public:
	static DeviceOnlineManage* getInstance();//获取单体实例
public:
	int ParseMsgHeartBeat(PMsgData pPacket);//解析心跳
public slots:
	void on_timeout();//定时器回调
};
#endif