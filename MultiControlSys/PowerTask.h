#pragma once

#include <QObject>
#include "ITask.h"
//自动测试->单项测试 daatype=0的测试 只是弹出一个对话框 其他逻辑都有父类ITask实现
class PowerTask : public ITask
{
	Q_OBJECT

public:
	PowerTask(QObject *parent);
	~PowerTask();
	QTimer* m_tmCheckState = nullptr;//用于延时等待网络返回 怕卡住界面，所以用了定时器 在start的时候就用了 
public:
	virtual void start() ;
	virtual void StopCheck();//结束
public slots:
	void CheckStateSlot();//线路状态返回延时的检测


};
