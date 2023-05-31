#include "CPUTask.h"

CPUTask::CPUTask(QObject *parent)
	: ITask(2,parent)
{
	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));
}

CPUTask::~CPUTask()
{
}

void CPUTask::start()
{
	emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x65ָ���ʸ���֡��ӳ�3��.���Ժ�..."));
	m_tmTestUseTm->start(3000);
}

void CPUTask::StopCheck()
{
	ITask::StopCheck();
	if (m_tmTestUseTm->isActive())
		m_tmTestUseTm->stop();
}

void CPUTask::timerEvent(QTimerEvent *event)
{
	ITask::timerEvent(event);
}

void CPUTask::UpdateTmLabel()
{
	emit UpdateToolTipSignal(QString::fromLocal8Bit("  "));
	ITask::start();
	m_tmTestUseTm->stop();
}
