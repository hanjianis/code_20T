#include "VRSimulation.h"
#include <QHostAddress>
#include <QDebug>
#include "Packet.h"
#include <QDateTime>
#include "LogMgr.h"

VRSimulation::VRSimulation(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	socket = new QTcpSocket();
	connect(socket, &QTcpSocket::connected, [=]() {
		qDebug() << "connect success";
		//ui.textEditRead->append("connect success");
	});
	RecvBuf = new char[MAX_BUFFER];
	memset(RecvBuf, 0, MAX_BUFFER);
	RecvLen = 0;

	m_timer = new QTimer();
	connect(m_timer, SIGNAL(timeout()), this, SLOT(on_time_out()));
	m_timer2 = new QTimer();
	connect(m_timer2, SIGNAL(timeout()), this, SLOT(on_time2_out()));

	connect(socket, SIGNAL(readyRead()), this, SLOT(socketRead()));
	//connect(socket, &QTcpSocket::readyRead, [=]() {
	//	QByteArray bytArr = socket->readAll();

	//	char* buf = bytArr.begin();
	//	int nMsgId = 0;
	//	int nDataLen = 0;
	//	QString str;
	//	memcpy(&nDataLen, buf, PACKET_HEADER_DATALENGTH_SIZE);
	//	nDataLen = ntohl(nDataLen);
	//	memcpy(&nMsgId, buf + 6, PACKET_HEADER_MSGID_SIZE);
	//	nMsgId = ntohl(nMsgId);
	//	if (nMsgId == eMsg_MsgStartScene)
	//	{
	//		ui.textBrowser->append(QString::fromLocal8Bit("启动场景"));
	//		MsgStartScene start;
	//		if (start.ParseFromArray(buf + PACKET_HEADER_SIZE, nDataLen))
	//		{
	//			m_playerid = start.playerid();
	//		}

	//		Sleep(100);
	//		//启动场景成功
	//		SendMsgLoadedScene();
	//	
	//		//
	//	}
	//	if (nMsgId == eMsg_MsgStartTrain)
	//	{
	//		//实时发送 目标和训练单元的6自由度信息
	//		m_timer->start(20);
	//		m_timer2->start(21);
	//		ui.textBrowser->append(QString::fromLocal8Bit("开始训练"));
	//	}
	//	if (nMsgId == eMsg_MsgRunGuideInfo)
	//	{
	//		MsgRunGuideInfo msg;
	//		if (msg.ParseFromArray(buf + PACKET_HEADER_SIZE, nDataLen))
	//		{
	//		//	QString str = QString("%1%2").arg(msg.tmtag().c_str()).arg(GetTime().toLocal8Bit());
	//		//	LogMgr::GetInstance()->AddLog(str);
	//			qDebug() << "+++++" << msg.tmtag().c_str() << GetTime().toLocal8Bit();
	//		}
	//	}
	//	if (nMsgId == eMsg_MsgLockedTarget)
	//	{
	//		ui.textBrowser->append(QString::fromLocal8Bit("锁定目标..."));
	//	}
	//	if (nMsgId == eMsg_MsgResultScore)
	//	{
	//		MsgResultScore score;
	//		if (score.ParseFromArray(buf + PACKET_HEADER_SIZE, nDataLen))
	//		{
	//			str = QString::fromLocal8Bit("成绩：：%1").arg(score.score());
	//			ui.textBrowser->append(str);
	//		}

	//		m_timer->stop();
	//		m_timer2->stop();

	//	}
	//	if (nMsgId == eMsg_MsgReplay)
	//	{
	//		ui.textBrowser->append(QString::fromLocal8Bit("复演。。。"));
	//	}
	//	if (nMsgId == eMsg_MsgEndTrain)
	//	{
	//		ui.textBrowser->append(QString::fromLocal8Bit("结束训练..."));
	//	}
	//	if (nMsgId == eMsg_MsgRunVRInfo)
	//	{
	//		ui.textBrowser->append(QString::fromLocal8Bit("战位操作..."));
	//		MsgRunVRInfo msg;
	//		if (msg.ParseFromArray(buf + PACKET_HEADER_SIZE, nDataLen))
	//		{
	//			switch (msg.launcher_operate())
	//			{
	//				
	//			case eSAc_SupplyPower:
	//				str = QString::fromLocal8Bit("战位供电");
	//				break;
	//			//case eSAc_InterceptTarget:
	//			//	str = QString::fromLocal8Bit("截获目标");
	//			//	break;
	//			case eSAc_UnLock:
	//				str = QString::fromLocal8Bit("战位解锁");
	//				break;
	//			//case eSAc_ChooseAttackMode:
	//			//	str = QString::fromLocal8Bit("选择攻击方式");
	//			//	break;
	//			case eSAc_Launch:
	//				str = QString::fromLocal8Bit("战位发射");
	//				break;
	//			}
	//			ui.textBrowser->append(str);
	//		}
	//	}
	//});
}

VRSimulation::~VRSimulation()
{
}
void VRSimulation::on_connect_clicked()
{
	socket->connectToHost(QHostAddress("127.0.0.1"), E_PORT);
	//m_timer->start(500);
}
void VRSimulation::on_close_clicked()
{
	socket->disconnectFromHost();
	socket->close();
	m_timer->stop();
}

void VRSimulation::on_time_out()
{
	
	on_pushButton_clicked();
	
}

void VRSimulation::on_time2_out()
{
	
}

void VRSimulation::socketRead()
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
			ParseMsg(nMsgId, nDataLen, nullptr);
			
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
			ParseMsg(nMsgId, nDataLen, m_msg.msgBuf);
			
			if (m_msg.msgBuf != nullptr)
			{
				delete[] m_msg.msgBuf;
				m_msg.msgBuf = nullptr;
			}
		}

	}
}



void VRSimulation::on_pushButton_clicked()
{
	SendMsgID(eMsg_E_GetSysTime);
}

void VRSimulation::on_pushButton_2_clicked()
{
	SendMsgID(eMsg_E_OnEnterSelfTest);
}

void VRSimulation::on_pushButton_3_clicked()
{
	SendMsgID(eMsg_E_TestFinished);
}

QString VRSimulation::GetTime()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString(":: hh:mm::ss.zzz");
	return current_date;
}

void VRSimulation::ParseMsg(int nMsgId, int nDataLen, char* buf)
{
	QString str;

}

void VRSimulation::SendMsgID(int msgid)
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
	delete[]  buf;
}
