#pragma once

#include <QObject>
#include "ITask.h"
//自动测试的单项测试时的大气系统测试逻辑
class AtmoTask : public ITask
{
	Q_OBJECT

public:
	AtmoTask(QObject *parent);
	~AtmoTask();
	QTimer* m_tmTestUseTm;//用于测试使用时间
	QTimer* m_tmPLC;
	QTimer* m_tmPLCRead;//获取数据timer

	int  read100Already = 0;
	int read60Already = 0;
	int read20Already = 0;
public:
	virtual void start() ;//开始检测
	virtual void StopCheck();//结束
	virtual void timerEvent(QTimerEvent *event);//定时器函数
public slots:
	void UpdateTmLabel();//用于大气测试时的延时timer回调
	void PLCTmSlot();
	void PLCReadDataSlot();

signals:
	void DQ_failed();
};
