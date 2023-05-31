#pragma once

#include <QObject>
#include "ITask.h"
//自动测试 单项测试中的datatype=1的数据项在此task执行
class FeiKongTask : public ITask
{
	Q_OBJECT

public:
	FeiKongTask(QObject *parent);
	~FeiKongTask();
	QTimer* m_tmTestUseTm;//用于测试使用时间
public:
	virtual void start();
	virtual void timerEvent(QTimerEvent *event);//定时器的回调
public slots:
	void UpdateTmLabel();//延时的定时器
};
