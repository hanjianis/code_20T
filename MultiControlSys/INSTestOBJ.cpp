#include "INSTestOBJ.h"
#include "MessageBoxDlg.h"
#include "HecDataManager.h"
#include "MyToolTipDlg.h"
#include "InsConfigDlg.h"
#include <QTime>
#include "DeviceMgr/Dan2_Manager.h"
#include "DeviceMgr/ZHDY_Manager.h"
#include "DeviceMgr/Dan_Manager.h"
#include "DeviceMgr/LDGDB_Manager.h"
#include "DeviceOnlineManage.h"
INSTestOBJ::INSTestOBJ(AutoTestWidget* at, QWidget *parent)
	: QObject(parent)
{
	m_at = at;
	m_Parent = parent;
	pXL = XLManager::GetInstance();
	connect(this, SIGNAL(AddTaskItem(AutoTestData&)), parent, SLOT(AddTableWidget(AutoTestData&)));

	connect(this, SIGNAL(AddTaskItemResult(AutoTestData&)), parent, SLOT(AddAutoTestResult(AutoTestData&)));
	connect(this, SIGNAL(UpdateToolTipSignal(QString)), parent, SLOT(UpdateToolTip(QString)));
	connect(this, SIGNAL(SendStopInsSingal()), parent, SLOT(RecvStopInsSlot()));
	connect(this, SIGNAL(SendUseTmSignal()), parent, SLOT(SetTestUseTm()));

	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));

	m_tmCheckState = new QTimer();
	connect(m_tmCheckState, SIGNAL(timeout()), this, SLOT(CheckStateSlot()));
}

INSTestOBJ::~INSTestOBJ()
{
}

void INSTestOBJ::start()
{
	//打开综合电源对话框
	MessageBoxDlg dlg11(QString::fromLocal8Bit("接通综合电源"));
	dlg11.exec();
	//20210604 确保接通综合电源后 请求弹的线路连接状态
	Dan_Manager::getInstance()->RequestLineInfo();
	LDGDB_Manager::getInstance()->RequestPowerStatus();

	m_tmCheckState->start(2000);//20210604 2s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("正在初始化设置，请稍后"));
	return;

}

void INSTestOBJ::StopCheck()
{
	killTimer(_tmid_ins);
	_tmid_ins = 0;
	killTimer(_tmid_ins_result);
	_tmid_ins_result = 0;
	if (m_tmTestUseTm->isActive())
		m_tmTestUseTm->stop();
	if (m_tmCheckState->isActive())
		m_tmCheckState->stop();
	emit UpdateToolTipSignal(QString::fromLocal8Bit("惯导测试流程结束"));
	//
	HecDataManager::getInstance()->GetHecData(0);//结束定时上报
	_insState = 0;
	emit SendStopInsSingal();
}

void INSTestOBJ::timerEvent(QTimerEvent *event)
{
	//这里需要注意的是starttimer 在一个timerid里操作另外一个timerid是不正确的 
	int tmid = event->timerId();
	//惯导测试 两个是相互的
	
	if (tmid == _tmid_ins_result)
	{

		killTimer(_tmid_ins_result);
		_tmid_ins_result = 0;
		//考虑测试结果的随机
		AutoTestData &atd = pXL->m_mapINS[_lstindex++];
		RandomAtd(atd);
		emit AddTaskItemResult(atd);

		if (_lstindex == 19)
		{
			//QMessageBox::inforrimation(this,QString::fromLocal8Bit("操作提示"), QString::fromLocal8Bit("请接通中频电源"),QMessageBox::Ok);
			MyToolTipDlg dlgTool1(QString::fromLocal8Bit("操作提示"), QString::fromLocal8Bit("接通卫星信号转发装置"), m_Parent);
			dlgTool1.exec();
			MyToolTipDlg dlgTool(QString::fromLocal8Bit("操作提示"), QString::fromLocal8Bit("请接通中频电源"), m_Parent);
			dlgTool.exec();
			emit UpdateToolTipSignal(QString::fromLocal8Bit("请输入确保输入的位置信息误差小于200m"));
			InsConfigDlg dlg;
			dlg.exec();
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待0x84指令返回矢量字，延时10s，请稍后"));

		}
		
		if (_lstindex == 28)//开始对准
		{
			//开启20min的定时器
			emit UpdateToolTipSignal(QString::fromLocal8Bit("惯导对准"));
			_tmid_ins = startTimer(3*60*1000);//3分钟 测试用 否则等待太久
			//_tmid_ins = startTimer(20*60*1000);//20分钟
			_insState = 1;
			m_at->UpdateInsLables(81, 120);
			_startTickCount = GetTickCount();
			HecDataManager::getInstance()->GetHecData(200);//200ms定时获取
		}
		else
		{
			if (_lstindex == 20)
			{
				_tmid_ins = startTimer(10 * 1000);//延时10s 先用2s 
			}
			else
				_tmid_ins = startTimer(150);

			if (_lstindex > pXL->m_mapINS.size())
			{
				//停止
				killTimer(_tmid_ins);
				emit UpdateToolTipSignal(QString::fromLocal8Bit("惯导测试流程结束"));
				//
				HecDataManager::getInstance()->GetHecData(0);//结束定时上报
				_tmid_ins = 0;
				_insState = 0;
				m_tmTestUseTm->stop();
				emit SendStopInsSingal();
				return;
			}
		}
		return;
	}
	if (tmid == _tmid_ins)
	{
		if (_insState == 1)//对准的20分钟到了
		{
			_tmid_ins = startTimer(1*60 * 1000);//3秒 测试用 否则等待太久
			//_tmid_ins = startTimer(10 * 60 * 1000);//10分钟 导航
			_insState = 2;
			_startTickCount = GetTickCount();
			emit UpdateToolTipSignal(QString::fromLocal8Bit("惯导导航"));
			//下面的数据栏发生变化
			m_at->UpdateInsLables(121, 141);
			return;
		}
		if (_insState == 2)//导航完成
		{
			_insState = 0;
		}

		 //开始继续数据更新
		{
			emit AddTaskItem(pXL->m_mapINS[_lstindex]);

			killTimer(_tmid_ins);
			_tmid_ins = 0;
			_tmid_ins_result = startTimer(100);
		}
		return;
	}

	

}
 //生成随机数
 float INSTestOBJ::generateRand(float min, float max)
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
void INSTestOBJ::RandomAtd(AutoTestData & atd)
{
	//根据atd的类型 standardtype
	if (atd.standardtype == 2)
		return;
	if (atd.standardtype == 1)//在最大最小范围内产生一个随机
	{
		atd.val = QString("%1").arg(generateRand(atd.min,atd.max));
	}
}

void INSTestOBJ::SetSimularData(int srcid, int targetid)
{
	AutoTestData &atd = pXL->m_mapINS[srcid];
	float val = generateRand(atd.min, atd.max);
	QLabel* lb = pXL->m_mapAutoTestList[targetid].val;
	if (lb != nullptr)
	{
		lb->setText(QString("%1").arg(val));
	}
}

void INSTestOBJ::UpdateTmLabel()
{
	double usetm = (GetTickCount() - _startTickCount) /1000.0;

	//转化成00:00:00格式
	//QString str = QString("%1").arg(usetm, 2, 10, QLatin1Char('0'));
	QString str = QString::number(usetm, 'f', 2);
	//调用dan2manager 获取卫星定位信息
	if (_insState != 0)
	{
		Dan2_Manager::getInstance()->RequestPowerControl();

	}
	//更新对准时间
	if (_insState == 1)//处于对准状态
	{
		//xlmanager的m_mapAutoTestList第81个是对准时间label
		QLabel* lb = pXL->m_mapAutoTestList[81].val;
		if (lb != nullptr)
		{
			lb->setText(str);
		}
		//随机一些模拟数据
		//惯性垂速增量 根据惯导测试数据项 该数据的数值范围 进行模拟 对准的惯性垂速增量 map得43
		SetSimularData(43,89);
		//平台温控电阻
		SetSimularData(30, 98);
		//XYZ轴脉冲 加速度计脉冲 对准 数据项对应于34（Z) 35(X) 36(Y)
		SetSimularData(34, 99);
		SetSimularData(35, 100);
		SetSimularData(36, 101);
		//俯仰角用九轴得俯仰角
		//GPS周秒 不知道怎么对应 但是是变化得
		//北斗时间周分 北斗时间秒 也不知道怎么对应
		//ZXY轴漂移值 对应于对准数据项 
		SetSimularData(37, 118);
		SetSimularData(39, 119);
		SetSimularData(41, 120);
	}
	if (_insState == 2)//处于导航状态
	{
		//xlmanager的m_mapAutoTestList第121个是导航时间label
		QLabel* lb = pXL->m_mapAutoTestList[121].val;
		if (lb != nullptr)
		{
			lb->setText(str);
		}
		//随机一些模拟数据
		//惯性垂速增量 根据惯导测试数据项 该数据的数值范围 进行模拟 对准的惯性垂速增量 map得53
		SetSimularData(53, 131);
		//平台温控电阻
		SetSimularData(52, 132);
	}
}

void INSTestOBJ::CheckStateSlot()
{
	m_tmCheckState->stop();
	//判断线路状态和雷达
	
	//20210604 判断所有线路状态
	if (Dan_Manager::getInstance()->CheckLineConnected() == false)
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("请检查弹上电缆是否连接正确"));
		dlg.exec();
		StopCheck();
		return;
	}
	//二者有一
	if (LDGDB_Manager::getInstance()->CheckConneced() == false ||
		Dan_Manager::getInstance()->CheckLeiDaGaoDu() == false)
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("请检查雷达高度表是否连接正确"));
		dlg.exec();
		StopCheck();
		return;
	}
	//20210605 检测惯导 
	if ((DeviceOnlineManage::getInstance()->m_nDeviceOnlineFlag & 0x4) == 0)//九轴不在线
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("请检查惯导是否连接正确"));
		dlg.exec();
		StopCheck();
		return;
	}
	_lstindex = 1;
	_insState = 0;
	m_at->UpdateInsLables(1, 40);
	_tmid_ins = startTimer(50);
	m_tmTestUseTm->start(800);
}
