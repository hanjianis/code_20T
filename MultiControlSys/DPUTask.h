#pragma once

#include <QObject>

#include "ITask.h"
//�Զ����� ��������е�datatype=3���������ڴ�taskִ��
class DPUTask : public ITask
{
	Q_OBJECT

public:
	DPUTask(QObject *parent);
	~DPUTask();
	QTimer* m_tmTestUseTm;//���ڲ���ʹ��ʱ��
	QTimer* m_tmDPUFlash;
public:
	//virtual void start();
	virtual void timerEvent(QTimerEvent *event);//��ʱ���Ļص�
public slots:
	void UpdateTmLabel();//��ʱ�Ķ�ʱ��
};
