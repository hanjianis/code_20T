#include "PowerTask.h"
#include<QDebug>
#include "XLManager.h"
#include "MessageBoxDlg.h"
#include "DeviceMgr/Dan_Manager.h"
#include "DeviceMgr/LDGDB_Manager.h"
PowerTask::PowerTask(QObject *parent)
	: ITask(0,parent)
{
	_datatype = 0;
	m_tmCheckState = new QTimer();
	connect(m_tmCheckState, SIGNAL(timeout()), this, SLOT(CheckStateSlot()));

}

PowerTask::~PowerTask()
{
}

void PowerTask::start()
{
	//打开综合电源对话框
    MessageBoxDlg dlg(QString::fromLocal8Bit("接通综合电源"));
    dlg.exec();
	//20210604 任何一个单项测试 都先有这一步 所以线路检查加在这里
	Dan_Manager::getInstance()->RequestLineInfo();
	LDGDB_Manager::getInstance()->RequestPowerStatus();

	m_tmCheckState->start(2000);//20210604 2s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("正在初始化设置，请稍后"));
	return;
	//ITask::start();
}

void PowerTask::StopCheck()
{
	if (m_tmCheckState->isActive())
		m_tmCheckState->stop();
	ITask::StopCheck();
}

void PowerTask::CheckStateSlot()
{
	
	m_tmCheckState->stop();
	//判断线路状态和雷达

	//20210604 判断所有线路状态
	if (Dan_Manager::getInstance()->CheckLineConnected() == false)
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("请检查弹上电缆是否连接正确"));
		dlg.exec();
		StopCheck();
		emit StopSignleTestSignal();
		return;
	}
	//二者有一
	if (LDGDB_Manager::getInstance()->CheckConneced() == false ||
		Dan_Manager::getInstance()->CheckLeiDaGaoDu() == false)
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("请检查雷达高度表是否连接正确"));
		dlg.exec();
		StopCheck();
		emit StopSignleTestSignal();
		return;
	}
	ITask::start();
}
