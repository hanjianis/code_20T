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
	//���ۺϵ�Դ�Ի���
    MessageBoxDlg dlg(QString::fromLocal8Bit("��ͨ�ۺϵ�Դ"));
    dlg.exec();
	//20210604 �κ�һ��������� ��������һ�� ������·����������
	Dan_Manager::getInstance()->RequestLineInfo();
	LDGDB_Manager::getInstance()->RequestPowerStatus();

	m_tmCheckState->start(2000);//20210604 2s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڳ�ʼ�����ã����Ժ�"));
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
	//�ж���·״̬���״�

	//20210604 �ж�������·״̬
	if (Dan_Manager::getInstance()->CheckLineConnected() == false)
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("���鵯�ϵ����Ƿ�������ȷ"));
		dlg.exec();
		StopCheck();
		emit StopSignleTestSignal();
		return;
	}
	//������һ
	if (LDGDB_Manager::getInstance()->CheckConneced() == false ||
		Dan_Manager::getInstance()->CheckLeiDaGaoDu() == false)
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("�����״�߶ȱ��Ƿ�������ȷ"));
		dlg.exec();
		StopCheck();
		emit StopSignleTestSignal();
		return;
	}
	ITask::start();
}
