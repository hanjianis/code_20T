#include "UDPServer.h"
#include "LogMgr.h"
#include "Packet.h"
UDPServer* UDPServer::m_pInstance = nullptr;
UDPServer::UDPServer(int port,QObject *parent)
	: QObject(parent)
{
	m_udpSocket = new QUdpSocket();
    bool bb = m_udpSocket->bind(QHostAddress::Any, port);
   // const QString address_text = "192.168.2.53";
   // const QHostAddress address = QHostAddress(address_text);
   //  port = 8089;
   // udpSocket->writeDatagram(QNetworkDatagram(send_data,address,port));
    //bool bb = m_udpSocket->bind(address,port);
	if (bb)
	{
		LogMgr::GetInstance()->AddLog(QString::fromLocal8Bit("绑定%1端口成功").arg(port));

	}
	else
	{
		LogMgr::GetInstance()->AddLog(QString::fromLocal8Bit("绑定%1端口失败").arg(port));
	}
	connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(udpRead()));    
}

UDPServer::~UDPServer()
{
}
UDPServer* UDPServer::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new UDPServer(8089,nullptr);
	}
	return m_pInstance;
}

void UDPServer::RegisterEvent(int msgid, function<int(PMsgData)> func)
{
    m_mapBusinessFunc[msgid] = func;       //隐式复制
}
//带数据
void UDPServer::WriteData(int msgid, char* buf, int buflen,QString strIp,int port)
{
	char* tmpBuf = new char[UDP_HEADER_LEN + buflen];
	memset(tmpBuf, 0, UDP_HEADER_LEN + buflen);
	memcpy(tmpBuf + UDP_HEADER_LEN, buf, buflen);
	memcpy(tmpBuf + UDP_HEADER_CMD_SIZE, &msgid, UDP_HEADER_CMD_SIZE);

	int len = m_udpSocket->writeDatagram(tmpBuf, UDP_HEADER_LEN+buflen, QHostAddress(strIp), port);

	delete[] tmpBuf;
}
//不带数据
void UDPServer::WriteData(int msgid, QString strIp, int port)
{
	char* tmpBuf = new char[UDP_HEADER_LEN];
	memset(tmpBuf, 0, UDP_HEADER_LEN);
	memcpy(tmpBuf + UDP_HEADER_CMD_SIZE, &msgid, UDP_HEADER_CMD_SIZE);

	int len = m_udpSocket->writeDatagram(tmpBuf, UDP_HEADER_LEN, QHostAddress(strIp), port);

	delete[] tmpBuf;
}

//udp读取数据
void UDPServer::udpRead()
{
	QByteArray bArr;
	while (m_udpSocket->hasPendingDatagrams())
	{
		int len = m_udpSocket->pendingDatagramSize();
		bArr.resize(len);
		m_udpSocket->readDatagram(bArr.data(), bArr.size());
		char* ch = bArr.data();
		int* cmd = (int*)&(ch[UDP_HEADER_CMD_SIZE]);
		if (len == (UDP_HEADER_LEN))
		{
			m_msg.MsgId = *cmd;
			m_msg.MsgLen = 0;
			auto it = m_mapBusinessFunc.find(m_msg.MsgId);
            if (it != m_mapBusinessFunc.end())
			{
				m_mapBusinessFunc[m_msg.MsgId](&m_msg);
			}
		}
		if (len > (UDP_HEADER_LEN))
		{
			m_msg.MsgId = *cmd;
			m_msg.MsgLen = len-UDP_HEADER_LEN;
			m_msg.msgBuf = new char[m_msg.MsgLen];
			memset(m_msg.msgBuf, 0, m_msg.MsgLen);
			memcpy(m_msg.msgBuf, ch + UDP_HEADER_LEN, m_msg.MsgLen);
			auto it = m_mapBusinessFunc.find(m_msg.MsgId);
			if (it != m_mapBusinessFunc.end())
			{
                m_mapBusinessFunc[m_msg.MsgId](&m_msg);
			}
			delete[] m_msg.msgBuf;
		}
	}
}
