#pragma once

#include <QObject>
#include "ITask.h"
//�Զ����� ��������е�datatype=1���������ڴ�taskִ��
class FeiKongTask : public ITask
{
	Q_OBJECT

public:
	FeiKongTask(QObject *parent);
	~FeiKongTask();
	QTimer* m_tmTestUseTm;//���ڲ���ʹ��ʱ��
public:
	virtual void start();
	virtual void timerEvent(QTimerEvent *event);//��ʱ���Ļص�
public slots:
	void UpdateTmLabel();//��ʱ�Ķ�ʱ��
};
