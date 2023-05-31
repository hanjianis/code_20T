#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#pragma once
#include "Packet.h"
#include <QObject>
#include <QTimer>
#include <qtcpsocket.h>
//tcpͨ�� 
class TCPClient : public QObject
{
	Q_OBJECT

public:
	TCPClient(QObject *parent);
	~TCPClient();
	static TCPClient* m_pInstance;
public:
	//����ʵ����ȡ���� Ψһ�Ķ���ָ��
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
	void SendMsgID(int msgid);//������Ϣid û����Ϣ����
	void SendMsg(PMsgData msg);//������Ϣ
public slots:
	void on_timeout();
	void socketRead();//���ݽ��ղۺ��� Ŀǰ��socket��Ҫ���ڷ���
	void HandleStateChange(QAbstractSocket::SocketState socketState);
};
#endif