#pragma once

#include <QObject>

#include "ITask.h"
//自动测试 单项测试中的datatype=3的数据项在此task执行
class DPUTask : public ITask
{
	Q_OBJECT

public:
	DPUTask(QObject *parent);
	~DPUTask();
	QTimer* m_tmTestUseTm;//用于测试使用时间
	QTimer* m_tmDPUFlash;
public:
	//virtual void start();
	virtual void timerEvent(QTimerEvent *event);//定时器的回调
public slots:
	void UpdateTmLabel();//延时的定时器
};
