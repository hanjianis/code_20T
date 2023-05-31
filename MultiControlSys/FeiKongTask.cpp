#include "FeiKongTask.h"
#include "XLManager.h"
FeiKongTask::FeiKongTask(QObject *parent)
	: ITask(1,parent)
{
	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));
}

FeiKongTask::~FeiKongTask()
{
}

void FeiKongTask::start()
{
	emit UpdateToolTipSignal(QString::fromLocal8Bit("飞控参数装订检查"));
	ITask::start();
	
}

void FeiKongTask::timerEvent(QTimerEvent *event)
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
		if (atd.id == 19)
		{
			//还未结束
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x2指令返回矢量字.延时3秒。请稍后..."));
			m_tmTestUseTm->start(3 * 1000);//延时3s
			return;
		}
		_tmid = startTimer(50);
		return;
	}
}

void FeiKongTask::UpdateTmLabel()
{
	//马上结束
	m_tmTestUseTm->stop();
	emit UpdateToolTipSignal(QString::fromLocal8Bit("当前指令字02 返回矢量字8800"));
	_tmid = startTimer(50);//开始下一条
}
