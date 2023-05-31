#pragma once

#include <QObject>
#include "ITask.h"
//自动测试 单项测试中的datatype=2的数据项在此task执行
class CPUTask : public ITask
{
	Q_OBJECT

public:
	CPUTask(QObject *parent);
	~CPUTask();
	QTimer* m_tmTestUseTm;//用于测试使用时间
public:
	virtual void start();//开始执行
	virtual void StopCheck();//结束
	virtual void timerEvent(QTimerEvent *event);//定时器的回调
public slots:
	void UpdateTmLabel();//延时的定时器
};
