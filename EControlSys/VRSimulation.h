#pragma once

#include <QWidget>
#include "ui_VRSimulation.h"
#include <qtcpsocket.h>
#include <QTimer>
#include "Packet.h"
class VRSimulation : public QWidget
{
	Q_OBJECT

public:
	VRSimulation(QWidget *parent = Q_NULLPTR);
	~VRSimulation();

private:
	Ui::VRSimulation ui;
	int m_playerid;
	QTcpSocket* socket;
	QTimer* m_timer;
	QTimer* m_timer2;
	char* RecvBuf;
	int RecvLen;
	char* m_bufTmp;
	MsgData m_msg;
	
	public slots:
	void on_connect_clicked();
	void on_close_clicked();

	void on_time_out();
	void on_time2_out();
	void socketRead();

	//

	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
private:
	QString GetTime();
	void ParseMsg(int msgid, int nDataLen, char* buf);
	void SendMsgID(int msgid);
};
