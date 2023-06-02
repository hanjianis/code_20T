#include "ETCPServer.h"
#include "LogMgr.h"

#include <QDebug>
ETCPServer::ETCPServer(QObject *parent, int PORT)
	: QObject(parent)
{
	m_pTcpServer = new QTcpServer();
	m_port = PORT;
	m_pTcpServer->listen(QHostAddress::Any, m_port);
	connect(m_pTcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));


	connect(this, SIGNAL(ConnectSignal(int)), parent, SLOT(ConnectSvrSlot(int)));
	connect(this, SIGNAL(DisconnectSignal(int)), parent, SLOT(DisConnectSvrSlot(int)));


	m_bufTmp = nullptr;// = RecvBuf;// �յ�������

}

ETCPServer::~ETCPServer()
{
}

void ETCPServer::newConnection()
{
	m_TcpSocket = m_pTcpServer->nextPendingConnection();
//	QTcpSocket* client = new QTcpSocket(socket);
//	client->setReadBufferSize(MAX_BUFFER);
	QString ip = m_TcpSocket->peerAddress().toString();
	quint16 port = m_TcpSocket->peerPort();
	QString key = QString("%1").arg(ip.mid(7));
	//LogMgr::GetInstance()->AddLog(key);
	
	connect(m_TcpSocket, SIGNAL(readyRead()), this, SLOT(socketRead()));
	connect(m_TcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SocketError(QAbstractSocket::SocketError)));

	 m_RecvBuf = new char[MAX_BUFFER];
	memset(m_RecvBuf, 0, MAX_BUFFER * sizeof(char));
	m_RecvLen = 0;
	emit ConnectSignal(m_port);

}

void ETCPServer::socketRead()
{
	QTcpSocket *mysock = (QTcpSocket*)sender();//����
	QString key = QString("%1").arg(mysock->peerAddress().toString().mid(7));

	PareseRecvBuf(m_TcpSocket, m_RecvBuf, m_RecvLen);

}

void ETCPServer::SocketError(QAbstractSocket::SocketError err)
{
	QTcpSocket *socket = (QTcpSocket*)sender();//���߶���
	QString key = QString("%1").arg(socket->peerAddress().toString().mid(7));
	int error = socket->error();
	switch (error)
	{
	case QAbstractSocket::RemoteHostClosedError://�ͻ��˶Ͽ�
	{
		QString hostAddress = socket->QAbstractSocket::peerAddress().toString();
		emit DisconnectSignal(m_port);
		qDebug() << socket->errorString();
		break;
	}
	default:
	{
		error = -1;
		break; 
	}
	}
}


void ETCPServer::RegisterEvent(int msgid, function<int(PMsgData)> func)
{
	m_mapBusinessFunc[msgid] = func;
}



void ETCPServer::SendMsg(PMsgData pmsg)
{

	int npos = 0;
	int length = pmsg->MsgLen;
	char* buf = new char[length + PACKET_HEADER_SIZE];
	memset(buf, 0, length + PACKET_HEADER_SIZE);

	long dataLen = htonl(length);
	memcpy(buf, &dataLen, PACKET_HEADER_DATALENGTH_SIZE);
	npos += PACKET_HEADER_DATALENGTH_SIZE;
	unsigned short nVerifyCode = 123;
	nVerifyCode = htons(nVerifyCode);
	memcpy(buf + npos, &nVerifyCode, PACKET_HEADER_VERIFYCODE_SIZE);
	npos += PACKET_HEADER_VERIFYCODE_SIZE;
	int nMsgId = pmsg->MsgId;
	nMsgId = htonl(nMsgId);
	memcpy(buf + npos, &nMsgId, PACKET_HEADER_MSGID_SIZE);
	npos += PACKET_HEADER_MSGID_SIZE;
	memcpy(buf + npos, pmsg->msgBuf, pmsg->MsgLen);

	int ll = m_TcpSocket->write(buf, length + PACKET_HEADER_SIZE);

	m_TcpSocket->flush();
	if (buf != nullptr)
	{
		delete[] buf;
		buf = nullptr;
	}
}
void ETCPServer::PareseRecvBuf(QTcpSocket* socket, char* RecvBuf, int& RecvLen)
{
	QByteArray bytArr = socket->readAll();
	memcpy(RecvBuf + RecvLen, bytArr.begin(), bytArr.length());
	RecvLen += bytArr.length();

	int nDataLen = 0;
	unsigned short nVerifyCode = 0;
	int nMsgId = 0;
	int npos = 0;

	
//	int RecvBufPos = RecvLen;//����
	while (true)
	{
		if (RecvLen < npos + PACKET_HEADER_SIZE)//������ͷ����
		{
			//��npos�ض� ��RecvBuf��ֵ 
			m_bufTmp = new char[RecvLen - npos];
			memset(m_bufTmp, 0, RecvLen - npos);
			memcpy(m_bufTmp, RecvBuf + npos, RecvLen - npos);
			memset(RecvBuf, 0, MAX_BUFFER);
			memcpy(RecvBuf, m_bufTmp, RecvLen - npos);
			RecvLen -= npos;

			if (m_bufTmp != nullptr)
			{
				delete[] m_bufTmp;
				m_bufTmp = nullptr;
			}
			break;
		}
		memcpy(&nDataLen, RecvBuf + npos, PACKET_HEADER_DATALENGTH_SIZE);
		nDataLen = ntohl(nDataLen);
		npos += PACKET_HEADER_DATALENGTH_SIZE;
		memcpy(&nVerifyCode, RecvBuf + npos, PACKET_HEADER_VERIFYCODE_SIZE);
		nVerifyCode = ntohs(nVerifyCode);
		npos += PACKET_HEADER_VERIFYCODE_SIZE;
		memcpy(&nMsgId, RecvBuf + npos, PACKET_HEADER_MSGID_SIZE);
		nMsgId = ntohl(nMsgId);
		npos += PACKET_HEADER_MSGID_SIZE;
		if (nDataLen == 0)
		{
			m_msg.MsgId = nMsgId;
			m_msg.MsgLen = 0;
			auto it = m_mapBusinessFunc.find(nMsgId);
			if (it != m_mapBusinessFunc.end())
			{
				m_mapBusinessFunc[nMsgId](&m_msg);
			}
		}
		else if( nDataLen > 0) //���ݳ��� > 0 �� ʣ�µ����ݲ�����������
		{
			if (npos + nDataLen > RecvLen)
			{
				npos -= PACKET_HEADER_SIZE;
				//��npos�ض� ��RecvBuf��ֵ 
				m_bufTmp = new char[RecvLen - npos];
				memset(m_bufTmp, 0, RecvLen - npos);
				memcpy(m_bufTmp, RecvBuf + npos, RecvLen - npos);
				memset(RecvBuf, 0, MAX_BUFFER);
				memcpy(RecvBuf, m_bufTmp, RecvLen - npos);
				RecvLen -= npos;
				if (m_bufTmp != nullptr)
				{
					delete[] m_bufTmp;
					m_bufTmp = nullptr;
				}
				break;
			}
		
			m_msg.MsgId = nMsgId;
			m_msg.MsgLen = nDataLen;
			m_msg.msgBuf = new char[nDataLen];

			memcpy(m_msg.msgBuf, RecvBuf + npos, nDataLen);
			npos += nDataLen;
			auto it = m_mapBusinessFunc.find(m_msg.MsgId);
			if (it != m_mapBusinessFunc.end())
			{
				m_mapBusinessFunc[m_msg.MsgId](&m_msg);
			}
			if (m_msg.msgBuf != nullptr)
			{
				delete[] m_msg.msgBuf;
				m_msg.msgBuf = nullptr;
			}
		}

	}

}

