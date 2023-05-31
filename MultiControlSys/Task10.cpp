#include "Task10.h"
#include "XLManager.h"
#include "KJGXSMNQ_Manager.h"
#include "Dan2_Manager.h"
#include "MessageBoxDlg.h"
Task10::Task10(QObject *parent)
	: ITask(10, parent)
{
	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));
	m_tmDPUFlash = new QTimer();
	connect(m_tmDPUFlash, SIGNAL(timeout()), this, SLOT(UpdateDPFlash()));
	m_tmDPUFlashFinish = new QTimer();
	connect(m_tmDPUFlashFinish, SIGNAL(timeout()), this, SLOT(UpdateDPUFlashFinish()));
}

Task10::~Task10()
{
}

void Task10::start()
{
	//上来就有个延时3s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x30指令返回矢量字。延迟3秒.请稍侯..."));
	m_tmTestUseTm->start(3 * 1000);
}

void Task10::StopCheck()
{
	ITask::StopCheck();
	if (m_tmTestUseTm->isActive())
		m_tmTestUseTm->stop();
	if (m_tmDPUFlash->isActive())
		m_tmDPUFlash->stop();
	if (m_tmDPUFlashFinish->isActive())
		m_tmDPUFlashFinish->stop();
}

void Task10::timerEvent(QTimerEvent *event)
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
		//下视自检结果更新
		if (atd.id == 104)
		{
			SetSimularData(104, 36);
		}
		if (atd.id == 105)//管控版本
		{
			SetSimularData(105, 37);
		}
		if (atd.id == 106)//配准版本
		{
			SetSimularData(106, 38);
		}
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
		if (atd.id == 103) {
			KJGXSMNQ_Manager::getInstance()->RequsetSelfCheck();//启动自检 也就是唤醒
		//20210604 请求更换图片
			KJGXSMNQ_Manager::getInstance()->RequestPowerControl(1);//这里更换图片，再去Dan2_Manager里去请求查询依次 判断是否一致
			Sleep(200);
			Dan2_Manager::getInstance()->RequestPowerStatus();
			Sleep(200);//
			//如果Dan2和KJGXSMNQ的一致 那就是相同 否则不同
			goto label;
			bool bFailed = false;
			if (Dan2_Manager::getInstance()->_imageFlag == 0) bFailed = true;
			if (KJGXSMNQ_Manager::getInstance()->_imageNum != Dan2_Manager::getInstance()->_imageFlag) bFailed = true;
			if(bFailed)
			{
				MessageBoxDlg dlg3(QString::fromLocal8Bit("下视模拟器异常，请检查"));
				dlg3.exec();
				emit UpdateToolTipSignal(QString::fromLocal8Bit("下视模拟器异常...."));
				StopCheck();
				emit StopSignleTestSignal();
				return;
			}
		label: {}
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

			return;
		}
		if (atd.id == 101)
		{
			//m_tmTestUseTm->start(atd.tm * 1000);//延时3s
			_JizhunTuState = 1;
			_JizhunTuRecord = 1;
			m_tmDPUFlashFinish->start(atd.tm * 1000 / (28 * 3));
			return;
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

void Task10::UpdateTmLabel()
{
	m_tmTestUseTm->stop();
	_tmid = startTimer(50);
}
void Task10::UpdateDPFlash()
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
void Task10::UpdateDPUFlashFinish()
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
