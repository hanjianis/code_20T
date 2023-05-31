#pragma once

#include <QObject>
#include <QTimerEvent>
#include "Packet.h"
#include "XLManager.h"
#include "AutoTestWidget.h"
#include <QTimer>
//惯导测试逻辑
//自动测试->惯导测试时 创建该对象 并开始执行
//不断用定时器更新界面数据项以及测试结果 如果中途有特殊处理 就根据数据项id做处理 比如延时之类
//惯导测试对应的数据项位于数据库 ins表
class INSTestOBJ : public QObject
{
	Q_OBJECT

public:

	INSTestOBJ(AutoTestWidget* at, QWidget *parent);
	~INSTestOBJ();
	//
	QWidget* m_Parent = nullptr;//父窗口句柄
	XLManager* pXL;//数据库的单体
	int _startTickCount = 0;//测试使用时间
	int _lstindex = 0;//索引值 惯导是用字典标识的 用的是数据项id 数据库里能看到
	int _datatype = 1;//数据类型 一直是1
	int _tmid_ins;//惯导测试的定时器id
	int _tmid_ins_result;//惯导测试结果的定时器id
	int _insState = 0;//惯导状态 1：对准 2：导航
	QTimer* m_tmTestUseTm;//用于测试使用时间
	QTimer* m_tmCheckState = nullptr;//用于延时等待网络返回 怕卡住界面，所以用了定时器 在start的时候就用了 
	AutoTestWidget* m_at = nullptr;//下面的栏 由主窗口传递
public:
	virtual void start();//开始
	virtual void StopCheck();
	virtual void timerEvent(QTimerEvent *event);//定时器回调
	float generateRand(float min, float max);//产生随机数
signals:
	void AddTaskItem(AutoTestData& data);//更新测试项 引用调用
	void AddTaskItemResult(AutoTestData& data);//更新测试结果
	void UpdateToolTipSignal(QString str);//更新提示信息
	void SendStopInsSingal();//通知测试结束
	void SendUseTmSignal();//对于惯导而言 时间定时器都在自己obj里，所以要通知界面更新时间
private:
	void RandomAtd(AutoTestData & atd);//随机测试结果
	void SetSimularData(int srcid, int targetid);//设置界面的下面的信息栏
public slots:
	void UpdateTmLabel();//延时定时器回调 
	void CheckStateSlot();//线路状态返回延时的检测
};
