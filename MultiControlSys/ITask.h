#pragma once

#include <QObject>
#include <QTimerEvent>
#include "Packet.h"
#include <QDebug>
#include <QTimer>
//自动测试 单项测试的单个测试任务基类
//没有特殊处理时 就用该测试类 否则就需要继承于该类
class ITask : public QObject
{
	Q_OBJECT

public:

	ITask(int datatype = 0, QObject *parent = nullptr);
	~ITask();
public:
	int _datatype;
	int _tmid;
	int _tmid_result;//结果定时器
	int _lstindex;
	int _stop;
	QTimer* m_tmDelay = nullptr;//用于延时

public:
	virtual void start() ;//开始执行
	virtual void StopCheck();//结束
	virtual void timerEvent(QTimerEvent *event);//timer回调
	virtual void AutoSingle() ;//发送消息到界面 更新数据项
	virtual void AutoSingleResult();//更新数据项测试结果
	virtual int is_stop();//判断该单项是否完成
	float generateRand(float min, float max);//在min max 之间生成随机数
	void RandomAtd(AutoTestData & atd);//修改测试项的实测值 自我随机
	void SetSimularData(int srcid, int targetid);//设置下面信息栏的数据 srcid是数据项的id targetid是要更新哪个label
	void SetSimularData(QString val,int labelid);//设置一些信息栏的值 这些值不知道什么含义，只知道视频里这么显示的
signals:
	void AddTaskItem(AutoTestData& data);//信号 发送信号到AutoTestDlg 更新相应数据项
	void AddTaskItemResult(AutoTestData& data);////信号 发送信号到AutoTestDlg 更新相应数据项结果
	void UpdateToolTipSignal(QString str);//信号 发送信号到AutoTestDlg 更新界面的提示信息

	void StopSignleTestSignal();//结束单项测试
public slots:
	void TmDelaySlot();//延时timer的回调 有些数据项时 需要固定设置时间延时

};
