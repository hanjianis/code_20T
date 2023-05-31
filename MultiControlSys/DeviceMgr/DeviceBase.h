#pragma once

#include <QObject>
#include "../Packet.h"
#include "../ISysCheckItem.h"
class DeviceBase : public QObject
{
	Q_OBJECT

public:
	DeviceBase(int devinfoid,QObject *parent);
	~DeviceBase();

public:
	UDPServer* pUDPServer = nullptr;
	QString _ip = "127.0.0.1";// "192.168.2.53";
	int _port = 8090;//8089

	QString _version = "";//�汾
	int _checkState = 0;//�Լ�״̬
	
public:
	int ParseMsgVersion(PMsgData pPacket);
	int ParseMsgSelfCheck(PMsgData pPacket);
	void SetVal(int lableid, double val);
	void SetVal(int lableid, int val);
	void SetVal(int lableid, QString val);
};
