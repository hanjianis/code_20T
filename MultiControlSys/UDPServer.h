#pragma once

#include <QObject>
#include <QUdpSocket>
#include "Packet.h"
//udp server 单体实例
class UDPServer : public QObject
{
	Q_OBJECT

public:
	UDPServer(int port, QObject *parent);
	~UDPServer();
private:
	static UDPServer* m_pInstance;
public:
	static UDPServer* getInstance();
private:
	MsgData m_msg;
	QUdpSocket* m_udpSocket;
	map<int, function<int(PMsgData)>> m_mapBusinessFunc;
public:
	void RegisterEvent(int msgid, function<int(PMsgData)> func);//注册回调
	void WriteData(int msgid, char* buf,int buflen, QString strIp=QString("192.168.2.54"), int port=8089);//发送消息 默认是54 各个设备发送udp消息时 是根据数据库中的ip决定的
	void WriteData(int msgid, QString strIp = QString("192.168.2.54"), int port=8089);
public slots:
	void udpRead();//udp 读取数据
};
