#pragma once

#include <QObject>
#include "ITask.h"
//�Զ�����->������� daatype=0�Ĳ��� ֻ�ǵ���һ���Ի��� �����߼����и���ITaskʵ��
class PowerTask : public ITask
{
	Q_OBJECT

public:
	PowerTask(QObject *parent);
	~PowerTask();
	QTimer* m_tmCheckState = nullptr;//������ʱ�ȴ����緵�� �¿�ס���棬�������˶�ʱ�� ��start��ʱ������� 
public:
	virtual void start() ;
	virtual void StopCheck();//����
public slots:
	void CheckStateSlot();//��·״̬������ʱ�ļ��


};
