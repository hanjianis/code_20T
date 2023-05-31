#include "Task5.h"
#include "XLManager.h"
Task5::Task5(QObject *parent)
	: ITask(5,parent)
{
	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));
	m_tmDPUFlash = new QTimer();
	connect(m_tmDPUFlash, SIGNAL(timeout()), this, SLOT(UpdateDPFlash()));
	m_tmDPUFlashFinish = new QTimer();
	connect(m_tmDPUFlashFinish, SIGNAL(timeout()), this, SLOT(UpdateDPUFlashFinish()));
}

Task5::~Task5()
{
}

void Task5::start()
{
	//�������и���ʱ3s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x30ָ���ʸ���֡��ӳ�3��.���Ժ�..."));
	m_tmTestUseTm->start(3 * 1000);
}

void Task5::StopCheck()
{
	ITask::StopCheck();
	if (m_tmTestUseTm->isActive())
		m_tmTestUseTm->stop();
	if (m_tmDPUFlash->isActive())
		m_tmDPUFlash->stop();
	if (m_tmDPUFlashFinish->isActive())
		m_tmDPUFlashFinish->stop();
}

void Task5::timerEvent(QTimerEvent *event)
{
	int tmid = event->timerId();
	if (tmid == _tmid)
	{
		killTimer(_tmid);
		_tmid = 0;
		XLManager* pXL = XLManager::GetInstance();
		AutoTestData& atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
		emit AddTaskItem(atd);
		if (atd.id == 42)
		{
			m_tmDPUFlash->stop();
		}
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
		if (atd.id == 41)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x30ָ���ʸ����.��ʱ3�롣���Ժ�..."));
			m_tmTestUseTm->start(3 * 1000);//��ʱ3s
			return;
		}
		if (atd.id == 44)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x39ָ���ʸ����.��ʱ3�롣���Ժ�..."));
			m_tmTestUseTm->start(3 * 1000);//��ʱ3s
			return;
		}
		if (atd.id == 42)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("����DPU Flash����. ��ʱ300��. ���Ժ�..."));
			m_tmTestUseTm->start(atd.tm * 1000);//��ʱ3s
			_JizhunTuState = 1;
			m_tmDPUFlash->start(atd.tm * 1000 / (28 * 3));
			return;
		}
		if (atd.id == 43)
		{
			//m_tmTestUseTm->start(atd.tm * 1000);//��ʱ3s
			_JizhunTuState = 1;
			_JizhunTuRecord = 1;
			m_tmDPUFlashFinish->start(atd.tm * 1000 / (28 * 3));
			return;
		}
		_tmid = startTimer(50);
		return;
	}
}

void Task5::UpdateTmLabel()
{
	m_tmTestUseTm->stop();
	m_tmDPUFlash->stop();
	_tmid = startTimer(50);
}
void Task5::UpdateDPFlash()
{
	//3����ʾ��Ϣ �ֻز��� ���ֻ�28�� ��������ôд�ģ�
	//
	QStringList lst;
	if (_JizhunTuState == 1)
	{
		lst << QString::fromLocal8Bit("��ǰָ����33");
		lst << QString::fromLocal8Bit("��ǰָ����33 ����ָ����8800");
		lst << QString::fromLocal8Bit("  ");//�յ�
	}
	else if (_JizhunTuState == 2)
	{
		lst << QString::fromLocal8Bit("��ǰָ����34");
		lst << QString::fromLocal8Bit("��ǰָ����34 ����ָ����8800");
		lst << QString::fromLocal8Bit("  ");//�յ�
	}
	static int cnt = 0;
	QString str = lst[cnt % 3];
	cnt++;

	emit UpdateToolTipSignal(str);
}
void Task5::UpdateDPUFlashFinish()
{
	QString str;
	if (_JizhunTuState == 1)
		str = QString::fromLocal8Bit("��׼ͼװ��.�ܼ�¼��123����ǰ��¼��%1").arg(_JizhunTuRecord);
	else
		str = QString::fromLocal8Bit("��׼ͼװ��.�ܼ�¼��164����ǰ��¼��%1").arg(_JizhunTuRecord);

	emit UpdateToolTipSignal(str);
	_JizhunTuRecord++;
	if (_JizhunTuState == 1 && _JizhunTuRecord > 123)
	{
		m_tmDPUFlashFinish->stop();
		_tmid = startTimer(20);
	}
	/*if (_JizhunTuState == 2 && _JizhunTuRecord > 164)
	{
		m_tmDPUFlashFinish->stop();
		_tmid_mult = startTimer(20);
	}*/
}
