#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EControlSys.h"
#include <QLabel>
#include "ETCPServer.h"
#include "TestDlg.h"
#include "ControlWidget.h"
#include "KaoShiManage.h"
#include "SystemWidget.h"
#include "DeviceOnlineItemWidget.h"
class EControlSys : public QMainWindow
{
    Q_OBJECT

public:
    EControlSys(QWidget *parent = Q_NULLPTR);

private:
    Ui::EControlSysClass ui;
	QList<QLabel*> m_lableStateVR;
	QList<QLabel*> m_lableStateUnit;
	ETCPServer* m_MTcpSver;//�ۺϲ�����
	ETCPServer* m_ETcpSver;//��Ʒ������
	ETCPServer* m_InsTcpServer;//�ߵ�
	ETCPServer* m_FuseTcpServer;//����
	TestDlg* m_test;
private:
	//����widget
	ControlWidget* m_control;
	//���Թ���
	KaoShiManage* m_kaoshi;
	//ϵͳ����
	SystemWidget* m_system;

	void AddTableWidget(int msgid);

	void MesStatusBar();
public:
	//
	virtual void closeEvent(QCloseEvent *event);

	int ParseMsgE(PMsgData pPacket);
	int ParseMsgM(PMsgData pPacket);
	int ParseMsgIns(PMsgData pPacket);
	int ParseMsgFuse(PMsgData pPacket);
public slots:
	void ConnectSvrSlot(int portnum);
	void DisConnectSvrSlot(int portnum);
	void AddLogSlot(QString);//�����־
	void on_actionTest_triggered();
	void on_actionqidong_triggered();
	void on_close_clicked();
	void on_min_clicked();
	void on_max_clicked();
	void on_plan_clicked();
	void on_control_clicked();
	void on_kaoshi_clicked();
	void on_system_clicked();
private:
	void ConnectSQLServer();
};
