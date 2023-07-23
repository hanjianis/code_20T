#include "MultTestOBJ.h"
#include <QTime>
#include "MessageBoxDlg.h"
#include "InputTemperatureDlg.h"
#include "DeviceMgr/PLCManager.h"
#include "DeviceMgr/LDGDB_Manager.h"
#include "DeviceMgr/KJGXSMNQ_Manager.h"
#include "DeviceMgr/ZHDY_Manager.h"
#include "DeviceMgr/Dan_Manager.h"
#include "DeviceMgr/Dan2_Manager.h"
#include "DeviceOnlineManage.h"
#define  MAX_DELAY 5//正常应该是120
#define MAX_1553_DELAY 5//正常应该是630
MultTestOBJ::MultTestOBJ(AutoTestWidget* at, QWidget *parent)
	: QObject(parent)
{
	m_at = at;
	m_parent = parent;
	pXL = XLManager::GetInstance();
	connect(this, SIGNAL(AddTaskItem(AutoTestData&)), parent, SLOT(AddTableWidget(AutoTestData&)));

	connect(this, SIGNAL(AddTaskItemResult(AutoTestData&)), parent, SLOT(AddAutoTestResult(AutoTestData&)));
	connect(this, SIGNAL(UpdateToolTipSignal(QString)), parent, SLOT(UpdateToolTip(QString)));
	connect(this, SIGNAL(SendStopInsSingal()), parent, SLOT(RecvStopMultiSlot()));
	connect(this, SIGNAL(SendUseTmSignal()), parent, SLOT(SetTestUseTm()));
	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));
	m_tm1553DelayTm = new QTimer();
	connect(m_tm1553DelayTm, SIGNAL(timeout()), this, SLOT(Update1553Delay()));
	m_tmDPUFlash = new QTimer();
	connect(m_tmDPUFlash, SIGNAL(timeout()), this, SLOT(UpdateDPFlash()));
	m_tmDPUFlashFinish = new QTimer();
	connect(m_tmDPUFlashFinish, SIGNAL(timeout()), this, SLOT(UpdateDPUFlashFinish()));
	m_tmPLC = new QTimer();
	connect(m_tmPLC, SIGNAL(timeout()), this, SLOT(PLCTmSlot()));
	m_tmCheckState = new QTimer();
	connect(m_tmCheckState, SIGNAL(timeout()), this, SLOT(CheckStateSlot()));
}

MultTestOBJ::~MultTestOBJ()
{
}

void MultTestOBJ::start()
{
	//打开综合电源对话框
//	MessageBoxDlg dlg11(QString::fromLocal8Bit("接通综合电源"));
//	dlg11.exec();
	//20210604 确保接通综合电源后 请求弹的线路连接状态
	Dan_Manager::getInstance()->RequestLineInfo();
	LDGDB_Manager::getInstance()->RequestPowerStatus();

	m_tmCheckState->start(2000);//20210604 2s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("正在初始化设置，请稍后"));
	return;

}

void MultTestOBJ::StopCheck()
{
	killTimer(_tmid_mult);
	_tmid_mult = 0;
	killTimer(_tmid_mult_result);
	_tmid_mult_result = 0;
	if (m_tmTestUseTm->isActive())
		m_tmTestUseTm->stop();
	if (m_tm1553DelayTm->isActive())
		m_tm1553DelayTm->stop();
	if (m_tmDPUFlash->isActive())
		m_tmDPUFlash->stop();
	if (m_tmDPUFlashFinish->isActive())
		m_tmDPUFlashFinish->stop();
	if (m_tmPLC->isActive())
		m_tmPLC->stop();
	if (m_tmCheckState->isActive())
		m_tmCheckState->stop();
	emit SendStopInsSingal();
}

void MultTestOBJ::timerEvent(QTimerEvent *event)
{
	int tmid = event->timerId();
	//综合
	if (_tmid_mult == tmid)
	{
		emit AddTaskItem(pXL->m_mapMULT_TEST[_datatype][_lstindex]);
		//判断下一个的等待延时 根据atd.tm判断 若是0就默认20ms 否则就根据tm的延时(单位是s)
		AutoTestData &atd1 = pXL->m_mapMULT_TEST[_datatype][_lstindex];
		if (atd1.tm == 0)
			_tmid_mult_result = startTimer(20);
		else
			_tmid_mult_result = startTimer(atd1.tm * 1000);
	
		if (atd1.id == 37) //跟数据库对应
		{
			_JizhunTuState = 1;//用	_JizhunTuState 区分是当前字是0x33 还是0x34 提示信息不同
			m_tmDPUFlash->start(atd1.tm * 1000 / (28 * 3));//300s内完成28*3次更新
		//	return;
		}
		if (atd1.id == 40) //跟数据库对应
		{
			_JizhunTuState = 2;//用	_JizhunTuState 区分是当前字是0x33 还是0x34 提示信息不同
			m_tmDPUFlash->start(atd1.tm * 1000 / (3 * 3));//300s内完成3*3次更新
		//	return;
		}
		killTimer(_tmid_mult);
		_tmid_mult = 0;
		return;

	}
	if (_tmid_mult_result == tmid)
	{
		killTimer(_tmid_mult_result);
		_tmid_mult_result = 0;
		//考虑测试结果的随机
		AutoTestData &atd = pXL->m_mapMULT_TEST[_datatype][_lstindex];
		RandomAtd(atd);
		emit AddTaskItemResult(atd);
		_lstindex++;
		if (_lstindex == 23)
		{
			//打开大气数据测控仪
			MessageBoxDlg dlg1(QString::fromLocal8Bit("打开EZ23-20T大气数据测控仪"), m_parent);
			dlg1.exec();
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在打开大气数据测控仪,请稍后..."));
			
			if (PLCManager::getInstance()->ConnectPLC() == false)//PLC连接失败 会卡在打开大气仪界面 目前没有好的解决方式 不知道为什么
			{
				MessageBoxDlg dlg3(QString::fromLocal8Bit("打开大气数据测控仪失败！请检查电源"));
				dlg3.exec();
				emit UpdateToolTipSignal(QString::fromLocal8Bit("打开大气数据测控仪失败...."));
				StopCheck();
				return;
			}
			emit UpdateToolTipSignal(QString::fromLocal8Bit("打开大气数据测控仪成功...."));
			MessageBoxDlg dlg2(QString::fromLocal8Bit("待自检完成后，完成放气"), m_parent);
			dlg2.exec();
			PLCManager::getInstance()->SetMulStart();
			m_tmPLC->start(500);//
			return;
		}
		if (atd.id == 29)//当前这项是数据库中转母线供电指令 下一项是雷达高度表 让雷达高度表开机 自检
		{
			LDGDB_Manager::getInstance()->RequsetSelfCheck();
		}
		if (atd.id == 46)//当前显示的是46 地形匹配基准图信息 下一项是下视唤醒
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
			label:{}
		}
		if (atd.id == 50)//当前显示的是50 下视转飞控 下一项是下视休眠
		{
			//下视休眠 也就是关闭综合电源 第7路
			
			ZHDY_Manager::getInstance()->RequestPowerControl(7, 0);
			Sleep(1 * 1000);
		}
		if (atd.id == 25)//输入温度
		{
			//输入大气温度
			InputTemperatureDlg dlg22(m_parent);
			dlg22.exec();
		}
		if (atd.id == 37) //跟数据库对应
		{
			m_tmDPUFlash->stop();//300s内完成28*3次更新
		//	return;
		}
		
		if (atd.id == 38)
		{
			_JizhunTuState = 1;
			_JizhunTuRecord = 1;
			m_tmDPUFlashFinish->start(20);
			return;
		}
		if (atd.id == 40)
		{
			m_tmDPUFlash->stop();//300s内完成28*3次更新
		}
		if (atd.id == 41)//基准图装订 这次记录数共164
		{
			_JizhunTuState = 2;
			_JizhunTuRecord = 1;
			m_tmDPUFlashFinish->start(20);
			return;
		}
		//如果当前到了84 使用一个timer 开始进行数据模拟 主要是界面的提示信息 等待组合对准延时120s和1553板卡630s(实际是210s)
		if (atd.id == 84)
		{
			_delaySec = 0;
			m_at->UpdateInsLables(41, 80);
			_startTickCount = GetTickCount();
			m_tmTestUseTm->start(1000);//
			return;
		}
		_tmid_mult = startTimer(20);

		if (_lstindex >= pXL->m_mapMULT_TEST[_datatype].size())
		{

			//停止
			killTimer(_tmid_mult);
			emit SendStopInsSingal();
		}
		return;
	}
}

float MultTestOBJ::generateRand(float min, float max)
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

void MultTestOBJ::RandomAtd(AutoTestData & atd)
{
	//根据atd的类型 standardtype
	if (atd.standardtype == 2)
		return;
	if (atd.standardtype == 1)//在最大最小范围内产生一个随机
	{
		atd.val = QString("%1").arg(generateRand(atd.min, atd.max));
	}
}

void MultTestOBJ::SetSimularData(int srcid, int targetid)
{
	AutoTestData &atd = pXL->m_mapINS[srcid];
	float val = generateRand(atd.min, atd.max);
	QLabel* lb = pXL->m_mapAutoTestList[targetid].val;
	if (lb != nullptr)
	{
		lb->setText(QString("%1").arg(val));
	}
}
void MultTestOBJ::SetDQData(int targetid,float fVal)
{
	XLManager* pXL = XLManager::GetInstance();

	QLabel* lb = pXL->m_mapAutoTestList[targetid].val;
	if (lb != nullptr)
	{
		lb->setText(QString("%1").arg(fVal));
	}
}
void MultTestOBJ::SetSysTmLabel()
{
	double usetm = (GetTickCount() - _startTickCount) / 1000.0;
	QString strtm = QString::number(usetm, 'f', 2);
	SetTestLabel(41, strtm);
	
}
void MultTestOBJ::SetTestLabel(int labelid, QString str)
{
	QLabel* lb = pXL->m_mapAutoTestList[labelid].val;//系统时间
	if (lb != nullptr)
	{
		lb->setText(str);
	}
}
void MultTestOBJ::UpdateTmLabel()
{
	SetSysTmLabel();
	QString str = QString::fromLocal8Bit("等待组合垂速对准延时120秒，第%1秒").arg(_delaySec);
	emit UpdateToolTipSignal(str);
	//P1气压 P2气压变化 61.9左右0.1变化 未来可能是真实值
	float fVal = generateRand(61.85, 61.96);
	QString strtm = QString::number(fVal, 'f', 6);
	SetTestLabel(57, strtm);
	fVal = generateRand(61.85, 61.96);
	 strtm = QString::number(fVal, 'f', 6);
	SetTestLabel(58, strtm);
	//静压变化 57.6左右变化
	fVal = generateRand(57.6-0.2, 57.6+0.2);
	strtm = QString::number(fVal, 'f', 6);
	SetTestLabel(60, strtm);
	//组合垂速 0.1左右
	fVal = generateRand(0.1,0.3);
	strtm = QString::number(fVal, 'f', 6);
	SetTestLabel(64, strtm);
	//组合垂速增量 0.19左右
	fVal = generateRand(0.19, 0.20);
	strtm = QString::number(fVal, 'f', 6);
	SetTestLabel(73, strtm);
	_delaySec++;
	
	if (_delaySec > MAX_DELAY)
	{
		//垂速对准延时 完成 开始1553B板卡
		m_tmTestUseTm->stop();
		_startTickCount = GetTickCount();
		m_tm1553DelayTm->start(333);
	}
}

void MultTestOBJ::Update1553Delay()
{
	SetSysTmLabel();
	double usetm = (GetTickCount() - _startTickCount) / 1000.0;
	QString strtm = QString::number(usetm, 'f', 2);
	QString str = QString::fromLocal8Bit("1553B板卡时间：%1秒").arg(strtm);
	emit UpdateToolTipSignal(str);

	if (usetm > MAX_1553_DELAY)
	{
		//1553B模拟完成 
		m_tm1553DelayTm->stop();
		_tmid_mult = startTimer(20);
	}
}

void MultTestOBJ::UpdateDPFlash()
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
	QString str = lst[cnt%3];
	cnt++;

	emit UpdateToolTipSignal(str);
}

void MultTestOBJ::UpdateDPUFlashFinish()
{
	QString str;
	if(_JizhunTuState == 1)
		str = QString::fromLocal8Bit("基准图装订.总记录数123，当前记录号%1").arg(_JizhunTuRecord);
	else
		str = QString::fromLocal8Bit("基准图装订.总记录数164，当前记录号%1").arg(_JizhunTuRecord);

	emit UpdateToolTipSignal(str);
	_JizhunTuRecord++;
	if (_JizhunTuState==1 && _JizhunTuRecord > 123)
	{
		m_tmDPUFlashFinish->stop();
		_tmid_mult = startTimer(20);
	}
	if (_JizhunTuState == 2 && _JizhunTuRecord > 164)
	{
		m_tmDPUFlashFinish->stop();
		_tmid_mult = startTimer(20);
	}
}

void MultTestOBJ::PLCTmSlot()
{
	if (PLCManager::getInstance()->ReadMulIsEnd() == true)
	{
		float fval = PLCManager::getInstance()->ReadJingYa();
		SetDQData(26, fval);//静压
		fval = PLCManager::getInstance()->ReadZongYa();
		SetDQData(27, fval);//总压
		SetDQData(28, fval);//总压

		m_tmPLC->stop();
		PLCManager::getInstance()->SetMulStop();
		PLCManager::getInstance()->DisConnectPLC();
		//_tmid = startTimer(50);
		_tmid_mult = startTimer(20);
	}

	//if (_plcState == 1)
	//{
	//	if (read100Already == 0 && PLCManager::getInstance()->Read100KPaIsEnd() == true)
	//	{
	//		float fval = PLCManager::getInstance()->ReadJingYa();
	//		SetDQData(26, fval);//静压
	//		fval = PLCManager::getInstance()->ReadZongYa();
	//		SetDQData(27, fval);//总压
	//		SetDQData(28, fval);//总压
	//		read100Already = 1;
	//	}
	//	if (read60Already == 0 && PLCManager::getInstance()->Read60KPaIsEnd() == true)
	//	{
	//		float fval = PLCManager::getInstance()->ReadJingYa();
	//		SetDQData(26, fval);//静压
	//		fval = PLCManager::getInstance()->ReadZongYa();
	//		SetDQData(27, fval);//总压
	//		SetDQData(28, fval);//总压
	//		
	//		read60Already = 1;
	//	}
	//	if (read20Already == 0 && PLCManager::getInstance()->Read20KPaIsEnd() == true)
	//	{
	//		float fval = PLCManager::getInstance()->ReadJingYa();
	//		SetDQData(26, fval);//静压
	//		fval = PLCManager::getInstance()->ReadZongYa();
	//		SetDQData(27, fval);//总压
	//		SetDQData(28, fval);//总压
	//	
	//		m_tmPLC->stop();
	//		PLCManager::getInstance()->SetMulStop();
	//		PLCManager::getInstance()->DisConnectPLC();
	//		//_tmid = startTimer(50);
	//		_tmid_mult = startTimer(20);
	//		read20Already = 1;
	//	}
	//	return;
	//}
	//if (PLCManager::getInstance()->Read1MinValid() == true)
	//{
	//	_plcState = 1;
	//
	//}
	//if (PLCManager::getInstance()->Read1MinUnValid() == true)
	//{
	//	_plcState = 2;
	//	m_tmPLC->stop();
	//	MessageBoxDlg dlg2(QString::fromLocal8Bit("气压漏气"));
	//	dlg2.exec();
	//	PLCManager::getInstance()->SetMulStop();
	//	PLCManager::getInstance()->DisConnectPLC();
	//	emit SendStopInsSingal();
	//	//m_tmPLC->stop();
	//	//emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待气压泄露，延时60秒，请稍候..."));
	//	//m_tmTestUseTm->start(60 * 1000);
	//}
}

void MultTestOBJ::CheckStateSlot()
{
	m_tmCheckState->stop();

	//判断线路状态和雷达
	
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

	//20210604 判断所有线路状态
	if (Dan_Manager::getInstance()->CheckLineConnected() == false)
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("请检查弹上电缆是否连接正确"));
		dlg.exec();
		StopCheck();
		return;
	}
	_lstindex = 0;
	_tmid_mult = startTimer(50);
	m_at->UpdateInsLables(1, 40);
}
