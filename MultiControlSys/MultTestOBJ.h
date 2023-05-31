#pragma once
#include "Packet.h"
#include "XLManager.h"
#include <QObject>
#include "AutoTestWidget.h"
#include <QTimer>
//自动测试->综合测试 数据库是multest
class MultTestOBJ : public QObject
{
	Q_OBJECT

public:
	MultTestOBJ(AutoTestWidget* at,QWidget *parent);
	~MultTestOBJ();
public:
	QWidget* m_parent=nullptr;
	XLManager* pXL=nullptr;
	
	QTimer* m_tmTestUseTm=nullptr;//用于等待垂速延时的时间
	QTimer* m_tm1553DelayTm = nullptr;//用于1553B延时
	QTimer* m_tmDPUFlash = nullptr;//用于DPU FLash擦除时提示消息更新
	QTimer* m_tmDPUFlashFinish = nullptr;//用于DPU Flash擦除时提示消息更新 对应于数据库中的id=38
	QTimer* m_tmPLC = nullptr;//PLC状态检测timer
	QTimer* m_tmCheckState = nullptr;//用于延时等待网络返回 怕卡住界面，所以用了定时器 在start的时候就用了 
	int _plcState = 0;//PLC状态 1:1分钟合格 2：1分钟不合格  
	int  read100Already = 0;
	int read60Already = 0;
	int read20Already = 0;

	AutoTestWidget* m_at = nullptr;//下面的栏 由主窗口传递

	int _lstindex = 0;
	int _datatype = 1;
	int _tmid_mult;//综合测试的定时器id
	int _tmid_mult_result;//综合测试结果的定时器id
	int _delaySec;//等待垂速延时的时间 120s 
	int _delay1553;
	int _startTickCount = 0;
	int _JizhunTuRecord;//基准图装订的记录号 从1开始到123
	int _JizhunTuState;//用于标识_JizhunTuRecord 是到123 还是到164 _JizhunTuState=1时_JizhunTuRecord=123 否则_JizhunTuRecord=164
public:
	virtual void start();
	virtual void StopCheck();
	virtual void timerEvent(QTimerEvent *event);
	float generateRand(float min, float max);
private:
	void RandomAtd(AutoTestData & atd);

	void SetSimularData(int srcid, int targetid);
	void SetDQData(int targetid, float fVal);//设置下面信息懒数据
	void SetSysTmLabel();//更新信息栏上的系统时间
	void SetTestLabel(int labelid, QString str);
signals:
	void AddTaskItem(AutoTestData& data);
	void AddTaskItemResult(AutoTestData& data);
	void UpdateToolTipSignal(QString str);//提示信息
	void SendStopInsSingal();//通知测试结束
	void SendUseTmSignal();//对于惯导而言 时间定时器都在自己obj里，所以要通知界面更新时间
public slots:
	void UpdateTmLabel();
	void Update1553Delay();
	void UpdateDPFlash();
	void UpdateDPUFlashFinish();
	void PLCTmSlot();
	void CheckStateSlot();//线路状态返回延时的检测
};
