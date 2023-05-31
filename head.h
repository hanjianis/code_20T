#pragma once
//注册动作列表
/*************/
m_MTcpSver = new ETCPServer(this, M_PORT);
for (int i = eMsg_T_OnAppStart; i < eMsg_T_OnAppStart + 99; i++)
{
	m_MTcpSver->RegisterEvent(i, std::bind(&EControlSys::ParseMsgM, this, std::placeholders::_1));
}
LogMgr::GetInstance()->AddLog(strLog);
/*************/
m_ETcpSver = new ETCPServer(this, E_PORT);
for (int i = eMsg_E_GetSysTime; i < eMsg_E_GetSysTime + 99; i++)
{
	m_ETcpSver->RegisterEvent(i, std::bind(&EControlSys::ParseMsgE, this, std::placeholders::_1));
}
LogMgr::GetInstance()->AddLog(strLog);
/*************/
m_InsTcpServer = new ETCPServer(this, INS_PORT);
for (int i = eMsg_K_OnAppStart; i < eMsg_K_OnAppStart + 999; i++)
{
	m_InsTcpServer->RegisterEvent(i, std::bind(&EControlSys::ParseMsgIns, this, std::placeholders::_1));
}

LogMgr::GetInstance()->AddLog(strLog);
/*************/
/************************************************************************/
m_FuseTcpServer = new ETCPServer(this, FUSE_PORT);
for (int i = eMsg_F_OnAppStart; i < eMsg_F_OnAppStart + 999; i++)
{
	m_FuseTcpServer->RegisterEvent(i, std::bind(&EControlSys::ParseMsgFuse, this, std::placeholders::_1));
}
LogMgr::GetInstance()->AddLog(strLog);
/************************************************************************/

//分析动作
int EControlSys::ParseMsgE(PMsgData pPacket)
{
	int msgid = pPacket->MsgId;

	AddTableWidget(msgid);
	if (msgid == eMsg_E_GetSysTime)
	{
		//fanhui xiaoxi 
		Msg_E msgE;
		QDateTime dt = QDateTime::currentDateTime();
		msgE.set_year(dt.date().year());
		msgE.set_month(dt.date().month());
		msgE.set_day(dt.date().day());
		msgE.set_hour(dt.time().hour());
		msgE.set_min(dt.time().minute());
		msgE.set_sec(dt.time().second());
		msgE.set_shellnum("");
		MsgData pMsg;
		pMsg.MsgId = eMsg_E_SysTime;
		pMsg.MsgLen = msgE.ByteSize();
		pMsg.msgBuf = new char[pMsg.MsgLen];
		if (msgE.SerializeToArray(pMsg.msgBuf, pMsg.MsgLen))
		{
			m_ETcpSver->SendMsg(&pMsg);
		}
		delete[] pMsg.msgBuf;
	}
	return 1;
}
//分析动作
int EControlSys::ParseMsgM(PMsgData pPacket)
{
	int msgid = pPacket->MsgId;
	if (msgid == eMsg_T_OnLine_Device)//
	{
		Msg_T_Online_Device msg;
		if (msg.ParseFromArray(pPacket->msgBuf, pPacket->MsgLen))
		{
			GlobalManager::getInstance()->SetUDPOnline(msg.onlineflag());
		}
	}
	else
		AddTableWidget(msgid);
	return 1;
}

int EControlSys::ParseMsgIns(PMsgData pPacket)
{
	int msgid = pPacket->MsgId;
	AddTableWidget(msgid);
	return 1;
}

int EControlSys::ParseMsgFuse(PMsgData pPacket)
{
	int msgid = pPacket->MsgId;
	AddTableWidget(msgid);
	return 1;
}

//接收网络包 并解析
void PareseRecvBuf(QTcpSocket* socket, char* RecvBuf, int& RecvLen)
{
	QByteArray bytArr = socket->readAll();
	memcpy(RecvBuf + RecvLen, bytArr.begin(), bytArr.length());
	RecvLen += bytArr.length();

	int nDataLen = 0;
	unsigned short nVerifyCode = 0;
	int nMsgId = 0;
	int npos = 0;
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
			m_msg.MsgId = nMsgId;
			m_msg.MsgLen = 0;
			auto it = m_mapBusinessFunc.find(nMsgId);
			if (it != m_mapBusinessFunc.end())
			{
				m_mapBusinessFunc[nMsgId](&m_msg);
			}
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
//记忆动作任务，进行写入数据库
bool AddTaskToDB(TaskInfo& tsinfo)
{
	QString str = QString("TASK_%1").arg(tsinfo.id, 3, 10, QLatin1Char('0'));
	tsinfo.task_id = str;

	int paramindex = 0;
	QSqlQuery query;
	query.prepare("exec [dbo].[AddTask] ?,?, ?, ?, ?, ?, ?, ?, ?,?,?,? output");

	query.bindValue(paramindex++, tsinfo.task_id);//
	query.bindValue(paramindex++, tsinfo.plan_id);
	query.bindValue(paramindex++, tsinfo.task_name);//
	query.bindValue(paramindex++, tsinfo.mode);
	query.bindValue(paramindex++, tsinfo.type);// 
	query.bindValue(paramindex++, tsinfo.state);//
	query.bindValue(paramindex++, tsinfo.subject);//
	query.bindValue(paramindex++, tsinfo.user_login_name);//
	query.bindValue(paramindex++, tsinfo.startTm1);//
	query.bindValue(paramindex++, tsinfo.startTm2);//
	//query.bindValue(paramindex++, ui.lineEdit_3->text());
	query.bindValue(paramindex++, tsinfo.note);
	query.bindValue(paramindex, 0, QSql::Out);
	bool bFlag = query.exec();
	if (bFlag)
	{
		int taskid = query.boundValue(paramindex).toInt();
		if (taskid < 0)
			bFlag = false;
		else
		{
			GlobalManager::getInstance()->_task_id = taskid + 1;
		}
	}
	return bFlag;
}

//摄像头捕捉
import cv2

cap = cv2.VideoCapture(0)

while True:
success, img = cap.read()
imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
cv2.imshow("HandsImage", img)
cv2.waitKey(1)

//帧率计算	
import time

#帧率时间计算
pTime = 0
cTime = 0

while True
cTime = time.time()
fps = 1 / (cTime - pTime)
pTime = cTime

cv2.putText(img, str(int(fps)), (10, 70), cv2.FONT_HERSHEY_PLAIN, 3,
(255, 0, 255), 3)       #FPS的字号，颜色等设置

//手势动作捕捉：
if hands:
# Hand 1
hand = hands[0]
lmList = hand["lmList"]
for lm in lmList :
data.extend([lm[0], h - lm[1], lm[2]])


//手势识别
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LineCode : MonoBehaviour
{

	LineRenderer lineRenderer;

	public Transform origin;
	public Transform destination;

	void Start()
	{
		lineRenderer = GetComponent<LineRenderer>();
		lineRenderer.startWidth = 0.1f;
		lineRenderer.endWidth = 0.1f;
	}
	// 连接两个点
	void Update()
	{
		lineRenderer.SetPosition(0, origin.position);
		lineRenderer.SetPosition(1, destination.position);
	}
}

//手势识别
public class HandTracking : MonoBehaviour
{
	public UDPReceive udpReceive;
	public GameObject[] handPoints;
	void Start()
	{

	}
	void Update()
	{
		string data = udpReceive.data;

		data = data.Remove(0, 1);
		data = data.Remove(data.Length - 1, 1);
		print(data);
		string[] points = data.Split(',');
		print(points[0]);

		for (int i = 0; i < 21; i++)
		{

			float x = 7 - float.Parse(points[i * 3]) / 100;
			float y = float.Parse(points[i * 3 + 1]) / 100;
			float z = float.Parse(points[i * 3 + 2]) / 100;

			handPoints[i].transform.localPosition = new Vector3(x, y, z);

		}

	}
}
//接收动作数据
from cvzone.HandTrackingModule import HandDetector
import cv2
import socket

cap = cv2.VideoCapture(0)
cap.set(3, 1280)
cap.set(4, 720)
success, img = cap.read()
h, w, _ = img.shape
detector = HandDetector(detectionCon = 0.8, maxHands = 2)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
serverAddressPort = ("127.0.0.1", 5052)

while True:
success, img = cap.read()
hands, img = detector.findHands(img)
data = []

if hands :
	# Hand 1
	hand = hands[0]
	lmList = hand["lmList"]
	for lm in lmList :
data.extend([lm[0], h - lm[1], lm[2]])

sock.sendto(str.encode(str(data)), serverAddressPort)

cv2.imshow("Image", img)
cv2.waitKey(1)

//连接到PLC
int cnt = 0;
while (0 != ptrPLC->ConnectTo("192.168.2.12", 0, 1)) {

	cnt++;
	if (cnt > 10)
		return false;
}

return true;

//读取plc中浮点数
QByteArray array;
array.resize(len);
for (int i = 0; i < array.size(); i++)
{
	array[i] = buf[len - 1 - i];
}
float aa;

memcpy(&aa, array, 4);
return aa;

//读取PLC中指定位置的数据 DB6.DBX78.0
if (ptrPLC->Connected())
{
	const int Len = 1;
	byte buff[Len] = { 0 };

	ptrPLC->DBRead(6, 78, Len, buff);
	return GetBit(buff[0], 0);
}

//断开PLC
if (ptrPLC->Connected())
{
	ptrPLC->Disconnect();
}