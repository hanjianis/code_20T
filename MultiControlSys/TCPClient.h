#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#pragma once
#include "Packet.h"
#include <QObject>
#include <QTimer>
#include <qtcpsocket.h>
//tcp通信 
class TCPClient : public QObject
{
	Q_OBJECT

public:
	TCPClient(QObject *parent);
	~TCPClient();
	static TCPClient* m_pInstance;
public:
	//单体实例获取方法 唯一的对象指针
	static TCPClient* GetInstance();
private:
	QTcpSocket* socket;
	char* RecvBuf;
	int RecvLen;
	char* m_bufTmp;
	MsgData m_msg;
	bool bconnect;
	QAbstractSocket::SocketState _socketState;
	QTimer* m_Timer;
public:
	void SendMsgID(int msgid);//发送消息id 没有消息内容
	void SendMsg(PMsgData msg);//发送消息
public slots:
	void on_timeout();
	void socketRead();//数据接收槽函数 目前该socket主要用于发送
	void HandleStateChange(QAbstractSocket::SocketState socketState);
};
#endif