#include "TCPClient.h"
#include <QHostAddress>
#include <QDebug>
TCPClient* TCPClient::m_pInstance = nullptr;

TCPClient* TCPClient::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new TCPClient(nullptr);
	}
	return m_pInstance;
}

TCPClient::TCPClient(QObject *parent)
	: QObject(parent)
{
	socket = new QTcpSocket();
	connect(socket, &QTcpSocket::connected, [=]() {
		qDebug() << "connect success";
		//ui.textEditRead->append("connect success");
	});
	connect(socket, SIGNAL(readyRead()), this, SLOT(socketRead()));
	connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
		this, SLOT(HandleStateChange(QAbstractSocket::SocketState)));
	RecvBuf = new char[MAX_BUFFER];
	memset(RecvBuf, 0, MAX_BUFFER);
	RecvLen = 0;
	bconnect = false;
	socket->connectToHost(QHostAddress("192.168.2.111"), M_PORT);
	m_Timer = new QTimer(this);
	connect(m_Timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
	m_Timer->start(3000);
}

TCPClient::~TCPClient()
{
}

void TCPClient::on_timeout()
{
	if(bconnect == false)
		socket->connectToHost(QHostAddress("192.168.2.111"), M_PORT);
	else
	{
		m_Timer->stop();
	}
}

void TCPClient::socketRead()
{
	QByteArray bytArr = socket->readAll();
	memcpy(RecvBuf + RecvLen, bytArr.begin(), bytArr.length());
	RecvLen += bytArr.length();

	int nDataLen = 0;
	unsigned short nVerifyCode = 0;
	int nMsgId = 0;
	int npos = 0;


	//	int RecvBufPos = RecvLen;//长度
	while (true)
	{
		if (RecvLen < npos + PACKET_HEADER_SIZE)//不够包头数据
		{
			//从npos截断 对RecvBuf赋值 
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
			//ParseMsg(nMsgId, nDataLen, nullptr);

		}
		else if (nDataLen > 0) //数据长度 > 0 且 剩下的数据不够数据内容
		{
			if (npos + nDataLen > RecvLen)
			{
				npos -= PACKET_HEADER_SIZE;
				//从npos截断 对RecvBuf赋值 
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
			//ParseMsg(nMsgId, nDataLen, m_msg.msgBuf);

			if (m_msg.msgBuf != nullptr)
			{
				delete[] m_msg.msgBuf;
				m_msg.msgBuf = nullptr;
			}
		}

	}
}


void TCPClient::HandleStateChange(QAbstractSocket::SocketState socketState)
{
	qDebug() << socketState;
	if (socketState == QAbstractSocket::ConnectedState)
	{
		//连接成功
		bconnect = true;
    //	SendMsgID(eMsg_T_OnAppStart);
	}
	if (socketState == QAbstractSocket::ClosingState)
	{
		//重新连接
		bconnect = false;
		socket->connectToHost(QHostAddress("192.168.2.111"), M_PORT);
		m_Timer->start(3000);
	}
}

void TCPClient::SendMsgID(int msgid)
{
	int npos = 0;
	int length = 0;
	long dataLen = 0;
	unsigned short nVerifyCode = 123;
	int nMsgId = 0;
	int ll = 0;
	char* buf = new char[MAX_BUFFER];
	memset(buf, 0, MAX_BUFFER);

	length = 0;
	dataLen = htonl(length);

	memcpy(buf, &dataLen, PACKET_HEADER_DATALENGTH_SIZE);
	npos += PACKET_HEADER_DATALENGTH_SIZE;

	nVerifyCode = htons(nVerifyCode);
	memcpy(buf + npos, &nVerifyCode, PACKET_HEADER_VERIFYCODE_SIZE);
	npos += PACKET_HEADER_VERIFYCODE_SIZE;
	nMsgId = msgid;
	nMsgId = htonl(nMsgId);
	memcpy(buf + npos, &nMsgId, PACKET_HEADER_MSGID_SIZE);
	npos += PACKET_HEADER_MSGID_SIZE;

	ll = socket->write(buf, length + PACKET_HEADER_SIZE);
	socket->flush();
	delete[]  buf;
}

void TCPClient::SendMsg(PMsgData pmsg)
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

	int ll = socket->write(buf, length + PACKET_HEADER_SIZE);

	socket->flush();
	if (buf != nullptr)
	{
		delete[] buf;
		buf = nullptr;
	}
}
