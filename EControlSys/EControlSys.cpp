#include "EControlSys.h"
#include "TestDlg.h"
#include "MsgManager.h"
#include "LogMgr.h"
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "PlanThinkDlg.h"
#include "GlobalManager.h"
#include "DeviceOnlineItemWidget.h"
QString g_SelectStyle = QString("background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #DEF0FE,stop:1 #C0DEF6);");
EControlSys::EControlSys(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	ConnectSQLServer();

	GlobalManager::getInstance();
	//初始化界面
	m_control = new ControlWidget(ui.groupBox);
	ui.verticalLayout_4->addWidget(m_control);

	m_kaoshi = new KaoShiManage(ui.groupBox);
	ui.verticalLayout_4->addWidget(m_kaoshi);
	m_kaoshi->setVisible(false);

	m_system = new SystemWidget(ui.groupBox);
	ui.verticalLayout_4->addWidget(m_system);
	m_system->setVisible(false);

	on_control_clicked();
	//隐藏
	ui.tableWidget->setVisible(false);
	ui.textBrowser->setVisible(false);
	//设备在线状态
	/*m_deviceWidget = new DeviceOnlineWidget(this);
	ui.verticalLayout->addWidget(m_deviceWidget, 0);*/
	//初始化tablewidget
	ui.tableWidget->setColumnWidth(0, 80);
	ui.tableWidget->setColumnWidth(1, 200);
	ui.tableWidget->setColumnWidth(2, 200);
	ui.tableWidget->setColumnWidth(3, 200);
	ui.tableWidget->setColumnWidth(4, 1000);
	ui.tableWidget->setAlternatingRowColors(true);
	ui.tableWidget->verticalHeader()->setVisible(false);
	//
	LogMgr* pLog = LogMgr::GetInstance();
	connect(pLog, SIGNAL(AddLogSignal(QString)), this, SLOT(AddLogSlot(QString)));

	MesStatusBar();
	/*************/
	m_MTcpSver = new ETCPServer(this, M_PORT);
	for (int i = eMsg_T_OnAppStart; i < eMsg_T_OnAppStart + 99; i++)
	{
		m_MTcpSver->RegisterEvent(i, std::bind(&EControlSys::ParseMsgM, this, std::placeholders::_1));
	}
	QString strLog = QString::fromLocal8Bit("综合测控软件服务启动，端口：%1").arg(M_PORT);
	LogMgr::GetInstance()->AddLog(strLog);
	/*************/
	m_ETcpSver = new ETCPServer(this, E_PORT);
	for (int i = eMsg_E_GetSysTime; i < eMsg_E_GetSysTime + 99; i++)
	{
		m_ETcpSver->RegisterEvent(i, std::bind(&EControlSys::ParseMsgE, this, std::placeholders::_1));
	}
	strLog = QString::fromLocal8Bit("火工品测试软件服务启动，端口：%1").arg(E_PORT);
	LogMgr::GetInstance()->AddLog(strLog);
	/*************/
	m_InsTcpServer = new ETCPServer(this, INS_PORT);
	for (int i = eMsg_K_OnAppStart; i < eMsg_K_OnAppStart + 999; i++)
	{
		m_InsTcpServer->RegisterEvent(i, std::bind(&EControlSys::ParseMsgIns, this, std::placeholders::_1));
	}
	strLog = QString::fromLocal8Bit("惯导测试软件服务启动，端口：%1").arg(E_PORT);
	LogMgr::GetInstance()->AddLog(strLog);
	/*************/
	/************************************************************************/
	m_FuseTcpServer = new ETCPServer(this, FUSE_PORT);
	for (int i = eMsg_F_OnAppStart; i < eMsg_F_OnAppStart + 999; i++)
	{
		m_FuseTcpServer->RegisterEvent(i, std::bind(&EControlSys::ParseMsgFuse, this, std::placeholders::_1));
	}
	strLog = QString::fromLocal8Bit("引信测试软件服务启动，端口：%1").arg(FUSE_PORT);
	LogMgr::GetInstance()->AddLog(strLog);
	/************************************************************************/
	m_test = new TestDlg(this);
	MsgManager::GetInstance();

	//setWindowFlags(Qt::FramelessWindowHint);
	showMaximized();
}
void EControlSys::MesStatusBar()
{
	//按照global 添加设备在线item
	QMap<int, DeviceOnline>::iterator it = GlobalManager::getInstance()->m_mapDeviceOnline.begin();//key 设备端口
	while (it != GlobalManager::getInstance()->m_mapDeviceOnline.end())
	{
		ui.statusBar->addWidget(new DeviceOnlineItemWidget(*it));
		it++;
	}
	
	return;
	QLabel* label1 = new QLabel(QString::fromLocal8Bit("综合测控软件:"));
	m_lableStateVR.push_back( new QLabel());
	m_lableStateVR[0]->setStyleSheet(QString::fromUtf8("image: url(:/EControlSys/res/red.png);"));

	//在statusBar中加入两个label
	ui.statusBar->addWidget(label1);
	ui.statusBar->addWidget(m_lableStateVR[0]);

	label1 = new QLabel(QString::fromLocal8Bit("火工品测控仪:"));
	m_lableStateVR.push_back(new QLabel());
	m_lableStateVR[1]->setStyleSheet(QString::fromUtf8("image: url(:/EControlSys/res/red.png);"));
	
	//在statusBar中加入两个label
	ui.statusBar->addWidget(label1);
	ui.statusBar->addWidget(m_lableStateVR[1]);

}

void EControlSys::AddTableWidget(int msgid)
{
	m_control->AddTaskLog(msgid);

}

void EControlSys::closeEvent(QCloseEvent *event)
{
	GlobalManager::getInstance()->SaveAll();
}

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

int EControlSys::ParseMsgM(PMsgData pPacket)
{
	int msgid = pPacket->MsgId;
	if (msgid == eMsg_T_OnLine_Device)//UDP设备在线
	{
		Msg_T_Online_Device msg;
		if (msg.ParseFromArray(pPacket->msgBuf,pPacket->MsgLen))
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

void EControlSys::ConnectSvrSlot(int portnum)
{
	//m_lableStateVR[portnum - M_PORT]->setStyleSheet(QString::fromUtf8("image: url(:/EControlSys/res/green.png);"));
	GlobalManager::getInstance()->SetDeviceOnline(portnum, ON_LINE);
}

void EControlSys::DisConnectSvrSlot(int portnum)
{
	//m_lableStateVR[portnum - M_PORT]->setStyleSheet(QString::fromUtf8("image: url(:/EControlSys/res/red.png);"));
	GlobalManager::getInstance()->SetDeviceOnline(portnum,OFF_LINE);
}

void EControlSys::AddLogSlot(QString str)
{
	ui.textBrowser->append(str);
	qDebug() << str;
}

void EControlSys::on_actionTest_triggered()
{
	//m_test->show();
	QSqlQuery query;
	query.prepare("exec [dbo].[AddThinkPlan] ?, ?, ?, ?, ?, ?, ?, ?,? output");
	query.bindValue(0, "PLAN_33");
	query.bindValue(1, "Test2");
	query.bindValue(2, 1);
	query.bindValue(3, QString::fromLocal8Bit("引信测试"));
	query.bindValue(4, "22;44");
	query.bindValue(5, LogMgr::GetInstance()->GetCurrentTimeString());
	query.bindValue(6, QString::fromLocal8Bit("测试"));
	query.bindValue(7, QString::fromLocal8Bit("1232"));
	query.bindValue(8, 0, QSql::Out);
	bool bFlag = query.exec();
	if (bFlag)
	{
		int planid = query.boundValue(8).toInt();
		if (planid < 0)
			bFlag = false;
		else
		{
			GlobalManager::getInstance()->_plan_id = planid + 1;
		}
	}

}

void EControlSys::on_actionqidong_triggered()
{
	MsgData pMsg;
	pMsg.MsgId = 1;
	pMsg.MsgLen = 0;
	pMsg.msgBuf = nullptr;
	//if (msgE.SerializeToArray(pMsg.msgBuf, pMsg.MsgLen))
	{
		m_MTcpSver->SendMsg(&pMsg);
	}
}

void EControlSys::on_close_clicked()
{
	GlobalManager::getInstance()->SaveAll();
	exit(0);
}

void EControlSys::on_min_clicked()
{
	showMinimized();
}

void EControlSys::on_max_clicked()
{
	showMaximized();
}

void EControlSys::on_plan_clicked()
{
	PlanThinkDlg dlg(this);
	if (dlg.exec() == QDialog::Accepted)
	{
		//跳转到导调的任务
		//on_control_clicked();
		m_control->refresh();
		m_kaoshi->refresh();
	}
}

void EControlSys::on_control_clicked()
{
	ui.control->setStyleSheet(g_SelectStyle);
	ui.kaoshi->setStyleSheet("");
	ui.system->setStyleSheet("");
	m_control->setVisible(true);
	m_kaoshi->setVisible(false);
	m_system->setVisible(false);
}

void EControlSys::on_kaoshi_clicked()
{
	ui.kaoshi->setStyleSheet(g_SelectStyle);
	ui.control->setStyleSheet("");
	ui.system->setStyleSheet("");
	m_control->setVisible(false);
	m_kaoshi->setVisible(true);
	m_system->setVisible(false);
}

void EControlSys::on_system_clicked()
{
	ui.system->setStyleSheet(g_SelectStyle);
	ui.kaoshi->setStyleSheet("");
	ui.control->setStyleSheet("");
	m_control->setVisible(false);
	m_kaoshi->setVisible(false);
	m_system->setVisible(true);
}

void EControlSys::ConnectSQLServer()
{
	//连接sqlserver数据库
	
		QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
		db.setDatabaseName(QString("DRIVER={SQL SERVER};"
			"SERVER=%1;" //服务器名称
			"DATABASE=%2;"//数据库名
			"UID=%3;"           //登录名
			"PWD=%4;"        //密码
		)
			.arg("127.0.0.1")
			.arg("20T")
			.arg("20T_access")
			.arg("20T_access")
		);
		if (!db.open())
		{
			qDebug() << "connect sql server failed!";

		}
		else
		{
			qDebug() << "connect sql server successfully!";
		}
	//test
		QSqlQuery query;
		query.exec("select * from test_table");
		while (query.next())	//循环输出
		{
			qDebug() << "===========";
			qDebug() << query.value(0).toInt() << query.value(1).toString();
		}
}
