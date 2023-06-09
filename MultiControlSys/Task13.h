#pragma once

#include <QObject>
#include "ITask.h"
//自动测试 单项测试的datatype=13的数据项
class Task13 : public ITask
{
	Q_OBJECT

public:
	Task13(QObject *parent);
	~Task13();
	int _JizhunTuState;
	int _JizhunTuRecord;//基准图装订的记录号 从1开始到123
	QTimer* m_tmDPUFlash = nullptr;//用于DPU FLash擦除时提示消息更新
	QTimer* m_tmDPUFlashFinish = nullptr;//用于DPU Flash擦除时提示消息更新 对应于数据库中的id=38
	QTimer* m_tmTestUseTm;//用于测试使用时间
public:
	virtual void start();
	virtual void StopCheck();//结束
	virtual void timerEvent(QTimerEvent *event);
public slots:
	void UpdateTmLabel();
	void UpdateDPFlash();
	void UpdateDPUFlashFinish();
};
