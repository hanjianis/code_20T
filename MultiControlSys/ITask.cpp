#include "ITask.h"
#include "XLManager.h"
#include <QDebug>
#include <QTime>
#include "MyToolTipDlg.h"
#include "MyMessageBox.h"
#include "DeviceMgr/Dan_Manager.h"
#include "DeviceMgr/ZHDY_Manager.h"
#include "DeviceMgr/LDGDB_Manager.h"
#include "DeviceMgr/KJGXSMNQ_Manager.h"
#include "DeviceMgr/CK_Manager.h"
#include "DeviceMgr/Dan2_Manager.h"
#include "MessageBoxDlg.h"

ITask::ITask(int datatype,QObject *parent)
	: QObject(parent)
{
	connect(this, SIGNAL(AddTaskItem(AutoTestData&)), parent, SLOT(AddTableWidget(AutoTestData&)));

	connect(this, SIGNAL(AddTaskItemResult(AutoTestData&)), parent, SLOT(AddAutoTestResult(AutoTestData&)));
	connect(this, SIGNAL(UpdateToolTipSignal(QString)), parent, SLOT(UpdateToolTip(QString)));
	_datatype = datatype;
	_lstindex = 0;
	_stop = 0;
	m_tmDelay = new QTimer();
	connect(m_tmDelay, SIGNAL(timeout()), this, SLOT(TmDelaySlot()));

	connect(this, SIGNAL(StopSignleTestSignal()), parent, SLOT(DQ_Failed()));
}

ITask::~ITask()
{
}

void ITask::start()
{

	_tmid = startTimer(50);
}

void ITask::StopCheck()
{
	killTimer(_tmid);
	_tmid = 0;
	killTimer(_tmid_result);
	_tmid_result = 0;
	_stop = 1;
}

void ITask::timerEvent(QTimerEvent *event)
{
	int tmid = event->timerId();
	if (tmid == _tmid)
	{
		killTimer(_tmid);
		_tmid = 0;
		XLManager* pXL = XLManager::GetInstance();
		AutoTestData& atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
		emit AddTaskItem(atd);
		
		_tmid_result = startTimer(100);
		return;
	}
	if (tmid == _tmid_result)
	{
		//更新测试结果
		killTimer(_tmid_result);
		_tmid_result = 0;

		AutoSingleResult();
		XLManager* pXL = XLManager::GetInstance();
		AutoTestData& atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
	//	RandomAtd(atd);
		//emit AddTaskItemResult(atd);
		if (atd.id == 117)//当117结果更新后，下一跳118显示的是闪光灯 提示出来两个闪光灯的提示
		{
			MyToolTipDlg dlg(QString::fromLocal8Bit("提示信息"), QString::fromLocal8Bit("闪光灯即将工作，请勿直视视光源。"));//这个时候 应该控制闪光灯开启 调用udp通信
			dlg.exec();

			//打开闪光灯
			Dan_Manager::getInstance()->RequsetLamControl(1);
			MyMessageBox dlg2(QString::fromLocal8Bit("确认提示"), QString::fromLocal8Bit("闪光灯是否正常？"));//这个时候 应该控制闪光灯开启 调用udp通信
			dlg2.exec();
		}
		if (atd.id == 51)//当前显示的是转母线指令 下一项是雷达高度表自检 让雷达高度表开机 自检
		{
			LDGDB_Manager::getInstance()->RequsetSelfCheck();
		}
		

		_lstindex++;
			
		if (_lstindex >= pXL->m_mapSINGLE_TEST[_datatype].count())
		{

			killTimer(_tmid_result);
			_lstindex = 0;
			_stop = 1;
			return;
		}
		atd = pXL->m_mapSINGLE_TEST[_datatype].at(_lstindex);
	
		//单项测试里 有设置雷达高度
		//设置高度时 并没有显示拿到网络值 进行更新 而是自我模拟 但是设置了udp
		if (atd.id == 58)//下一项是雷达高度100米 设置雷达高度
		{
			LDGDB_Manager::getInstance()->RequestPowerControl(100, 0);//衰减值不知道是多少 先写个0
		}
		if (atd.id == 59)//下一项是雷达高度1000米 设置雷达高度
		{
			LDGDB_Manager::getInstance()->RequestPowerControl(1000, 0);//衰减值不知道是多少 先写个0
		}
		if (atd.id == 60)//下一项是雷达高度1500米 设置雷达高度
		{
			LDGDB_Manager::getInstance()->RequestPowerControl(1500, 0);//衰减值不知道是多少 先写个0
		}
		//关于下视模拟器
		if (atd.id == 117)//下一项是下视唤醒
		{
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
			if (bFailed)
			{
				MessageBoxDlg dlg3(QString::fromLocal8Bit("下视模拟器异常，请检查"));
				dlg3.exec();
				emit UpdateToolTipSignal(QString::fromLocal8Bit("下视模拟器异常...."));
				StopCheck();
				return;
			}
			label :{}
		}
		if (atd.id == 121)
		{
			//关闭闪光灯
		//	Dan_Manager::getInstance()->RequsetLamControl(0);
			//下视休眠 也就是关闭程控管理器 第7路
			CK_Manager* ck = new CK_Manager(nullptr);
			ck->RequestPowerControl(7, 0);
			Sleep(1 * 1000);
		}

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

void ITask::AutoSingle()
{
	XLManager* pXL = XLManager::GetInstance();
	AutoTestData& atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
	emit AddTaskItem(atd);

	//_lstindex++;
	//if (_lstindex >= pXL->m_mapSINGLE_TEST[_datatype].count())
	//{

	//	killTimer(_tmid);
	//	_lstindex = 0;
	//	_stop = 1;
	//	return;
	//}
	//atd = pXL->m_mapSINGLE_TEST[_datatype].at(_lstindex);
	
}

void ITask::AutoSingleResult()
{

	XLManager* pXL = XLManager::GetInstance();
	AutoTestData& atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
	RandomAtd(atd);
	if (atd.id == 49)//母线电压 更新信息栏 母线电压位于datatype=6 没有单独处理 所以在itask里处理
	{
		SetSimularData(49, 7);
	}
	if (atd.id == 27)//三通道自检
	{
		SetSimularData(27, 19);
	}
	if (atd.id == 28)//三通道自检
	{
		SetSimularData(28, 20);
	}
	if (atd.id == 124)//锂电池电压
	{
		SetSimularData(124, 8);
	}
	if (atd.id == 52)//雷达表自检
	{
		SetSimularData(52,21);
	}
	if (atd.id == 53)//雷达表自检
	{
		SetSimularData(53, 22);
	}
	if (atd.id == 58)//雷达高度100m
	{
		SetSimularData(58, 30);
	}
	if (atd.id == 59)//雷达高度1000m
	{
		SetSimularData(59, 30);
	}
	if (atd.id == 60)//雷达高度1500m
	{
		SetSimularData(60, 30);
	}
	emit AddTaskItemResult(atd);
}

int ITask::is_stop()
{
	return _stop;
}
//随机数
float ITask::generateRand(float min, float max)
{
	static bool seedStatus;
	if (!seedStatus)
	{
		qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
		seedStatus = true;
	}
	if (min > max)
	{
		float temp = min;
		min = max;
		max = temp;
	}
	double diff = fabs(max - min);
	double m1 = (double)(qrand() % 100) / 100;
	double retval = min + m1 * diff;
	return retval;
}

void ITask::RandomAtd(AutoTestData & atd)
{
	if (atd.type == 2)
		return;
	//根据atd的类型 standardtype
	if (atd.standardtype == 2)
		return;
	if (atd.standardtype == 1)//在最大最小范围内产生一个随机
	{
		atd.val = QString("%1").arg(generateRand(atd.min, atd.max));
	}
}

void ITask::SetSimularData(int srcid, int targetid)
{
	XLManager* pXL = XLManager::GetInstance();
	AutoTestData& atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
	QString val = atd.val;
	QLabel* lb = pXL->m_mapAutoTestList[targetid].val;
	if (lb != nullptr)
	{
		lb->setText(QString("%1").arg(val));
	}
}

void ITask::SetSimularData(QString val, int labelid)
{
	XLManager* pXL = XLManager::GetInstance();
	QLabel* lb = pXL->m_mapAutoTestList[labelid].val;
	if (lb != nullptr)
	{
		lb->setText(QString("%1").arg(val));
	}
}

void ITask::TmDelaySlot()
{
	m_tmDelay->stop();
	_tmid = startTimer(50);
}
