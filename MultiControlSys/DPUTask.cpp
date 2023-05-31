#include "DPUTask.h"
#include "XLManager.h"
DPUTask::DPUTask(QObject *parent)
	: ITask(3,parent)
{
	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));
	m_tmDPUFlash = new QTimer();
	connect(m_tmDPUFlash, SIGNAL(timeout()), this, SLOT(UpdateDPFlash()));
}

DPUTask::~DPUTask()
{
}



void DPUTask::timerEvent(QTimerEvent *event)
{
	qDebug() << "11111111111111111";
	int tmid = event->timerId();
	if (tmid == _tmid)
	{
		killTimer(_tmid);
		_tmid = 0;
		AutoSingle();
		_tmid_result = startTimer(100);
		return;

	}
	if (tmid == _tmid_result)
	{
		//���²��Խ��
		killTimer(_tmid_result);
		_tmid_result = 0;
		XLManager* pXL = XLManager::GetInstance();
		AutoTestData atd = (pXL->m_mapSINGLE_TEST[_datatype]).at(_lstindex);
		RandomAtd(atd);
		emit AddTaskItemResult(atd);

		_lstindex++;

		if (_lstindex >= pXL->m_mapSINGLE_TEST[_datatype].count())
		{
			emit UpdateToolTipSignal(QString::fromLocal8Bit("  "));
			killTimer(_tmid_result);
			_lstindex = 0;
			_stop = 1;
			return;
		}
		if (atd.id == 23)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x65ָ���ʸ����.��ʱ3�롣���Ժ�..."));
			m_tmTestUseTm->start(3 * 1000);//��ʱ3s
			return;
		}
		_tmid = startTimer(50);
		return;
	}
}

void DPUTask::UpdateTmLabel()
{
	m_tmTestUseTm->stop();
	_tmid = startTimer(50);
}
