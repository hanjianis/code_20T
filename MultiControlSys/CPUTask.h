#pragma once

#include <QObject>
#include "ITask.h"
//�Զ����� ��������е�datatype=2���������ڴ�taskִ��
class CPUTask : public ITask
{
	Q_OBJECT

public:
	CPUTask(QObject *parent);
	~CPUTask();
	QTimer* m_tmTestUseTm;//���ڲ���ʹ��ʱ��
public:
	virtual void start();//��ʼִ��
	virtual void StopCheck();//����
	virtual void timerEvent(QTimerEvent *event);//��ʱ���Ļص�
public slots:
	void UpdateTmLabel();//��ʱ�Ķ�ʱ��
};
