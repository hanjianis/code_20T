#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "Packet.h"
#include <map>
#include <functional>
using namespace std;
class ETCPServer : public QObject
{
	Q_OBJECT

public:
	ETCPServer(QObject *parent,int PORT);
	~ETCPServer();

private:
	int m_port;
	 QTcpSocket* m_TcpSocket;
	char* m_RecvBuf;
	int m_RecvLen;

	QTcpServer* m_pTcpServer;
	map<int, function<int(PMsgData)>> m_mapBusinessFunc;

	char* m_bufTmp;

	MsgData m_msg;
public slots:
	void newConnection();
	void socketRead();
	void SocketError(QAbstractSocket::SocketError err);
	//
//	void SendGuideInfoSlot();
public:
	void RegisterEvent(int msgid,function<int(PMsgData)> func);

	void SendMsg(PMsgData msg);


	

	signals:
	void ConnectSignal(int);//连接信号 端口号
	void DisconnectSignal(int);//断开信号
private:
	void PareseRecvBuf(QTcpSocket* socket, char* RecvBuf, int& RecvLen);

};
