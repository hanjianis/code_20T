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
	//上来就有个延时3s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x30指令返回矢量字。延迟3秒.请稍侯..."));
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
		//更新测试结果
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
			//还未结束
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x30指令返回矢量字.延时3秒。请稍候..."));
			m_tmTestUseTm->start(3 * 1000);//延时3s
			return;
		}
		if (atd.id == 44)
		{
			//还未结束
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x39指令返回矢量字.延时3秒。请稍候..."));
			m_tmTestUseTm->start(3 * 1000);//延时3s
			return;
		}
		if (atd.id == 42)
		{
			//还未结束
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在DPU Flash擦除. 延时300秒. 请稍候..."));
			m_tmTestUseTm->start(atd.tm * 1000);//延时3s
			_JizhunTuState = 1;
			m_tmDPUFlash->start(atd.tm * 1000 / (28 * 3));
			return;
		}
		if (atd.id == 43)
		{
			//m_tmTestUseTm->start(atd.tm * 1000);//延时3s
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
	//3个提示消息 轮回播放 共轮回28遍 （方案这么写的）
	//
	QStringList lst;
	if (_JizhunTuState == 1)
	{
		lst << QString::fromLocal8Bit("当前指令字33");
		lst << QString::fromLocal8Bit("当前指令字33 返回指令字8800");
		lst << QString::fromLocal8Bit("  ");//空的
	}
	else if (_JizhunTuState == 2)
	{
		lst << QString::fromLocal8Bit("当前指令字34");
		lst << QString::fromLocal8Bit("当前指令字34 返回指令字8800");
		lst << QString::fromLocal8Bit("  ");//空的
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
		str = QString::fromLocal8Bit("基准图装订.总记录数123，当前记录号%1").arg(_JizhunTuRecord);
	else
		str = QString::fromLocal8Bit("基准图装订.总记录数164，当前记录号%1").arg(_JizhunTuRecord);

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
