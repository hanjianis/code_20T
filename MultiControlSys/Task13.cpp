#include "Task13.h"
#include "XLManager.h"
#include "MyMessageBox.h"
Task13::Task13(QObject *parent)
	: ITask(13, parent)
{
	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));
	m_tmDPUFlash = new QTimer();
	connect(m_tmDPUFlash, SIGNAL(timeout()), this, SLOT(UpdateDPFlash()));
	m_tmDPUFlashFinish = new QTimer();
	connect(m_tmDPUFlashFinish, SIGNAL(timeout()), this, SLOT(UpdateDPUFlashFinish()));
}

Task13::~Task13()
{
}

void Task13::start()
{
	//上来就有个延时3s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x8f指令返回矢量字，延时3秒，请稍侯..."));
	m_tmTestUseTm->start(3 * 1000);
}

void Task13::StopCheck()
{
	ITask::StopCheck();
	if (m_tmTestUseTm->isActive())
		m_tmTestUseTm->stop();
	if (m_tmDPUFlash->isActive())
		m_tmDPUFlash->stop();
	if (m_tmDPUFlashFinish->isActive())
		m_tmDPUFlashFinish->stop();
}

void Task13::timerEvent(QTimerEvent *event)
{
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
		if (atd.id == 144)
		{
			//还未结束
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x94指令返回矢量字，延时3秒，请稍侯..."));
			m_tmTestUseTm->start(3 * 1000);//延时3s
			return;
		}
		if (atd.id == 146)
		{
			//还未结束
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x96指令返回矢量字，延时3秒，请稍侯..."));
			m_tmTestUseTm->start(3 * 1000);//延时3s
			return;
		}
		if (atd.id == 152)
		{
			//还未结束
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x92指令返回矢量字，延时3秒，请稍侯..."));
			m_tmTestUseTm->start(3 * 1000);//延时3s
			return;
		}
		if (atd.id == 156)
		{
			//还未结束
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x91指令返回矢量字，延时3秒，请稍侯..."));
			m_tmTestUseTm->start(3 * 1000);//延时3s
			return;
		}
		if (atd.id == 160)
		{
			//还未结束
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x93指令返回矢量字，延时3秒，请稍侯..."));
			m_tmTestUseTm->start(3 * 1000);//延时3s
			return;
		}
		if (atd.id == 160)
		{
			//还未结束
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x93指令返回矢量字，延时3秒，请稍侯..."));
			m_tmTestUseTm->start(3 * 1000);//延时3s
			return;
		}
		if (atd.id == 185)
		{
			MyMessageBox dlg(QString::fromLocal8Bit("操作提示"), QString::fromLocal8Bit("请选择是否自动松开保险开关?\r\nYes----自动  No---手动"));
			dlg.exec();
		}
		
		atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
		//如果下一条消息 显示 需要延时，则添加延时timer
		if (atd.tm != 0)
		{
			//于此同时 发送下一条的提示信息到界面
			emit UpdateToolTipSignal(atd.tip);
			m_tmDelay->start(atd.tm * 1000);
			return;
		}
		_tmid = startTimer(50);
		return;
	}
}

void Task13::UpdateTmLabel()
{
	m_tmTestUseTm->stop();
	_tmid = startTimer(50);
}
void Task13::UpdateDPFlash()
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
void Task13::UpdateDPUFlashFinish()
{
	QString str;
	if (_JizhunTuState == 1)
		str = QString::fromLocal8Bit("基准图装订.总记录数258，当前记录号%1").arg(_JizhunTuRecord);
	//else
	//	str = QString::fromLocal8Bit("基准图装订.总记录数164，当前记录号%1").arg(_JizhunTuRecord);

	emit UpdateToolTipSignal(str);
	_JizhunTuRecord++;
	if (_JizhunTuState == 1 && _JizhunTuRecord > 258)
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
