#pragma once

#include <QObject>
#include "ITask.h"
//�Զ����Եĵ������ʱ�Ĵ���ϵͳ�����߼�
class AtmoTask : public ITask
{
	Q_OBJECT

public:
	AtmoTask(QObject *parent);
	~AtmoTask();
	QTimer* m_tmTestUseTm;//���ڲ���ʹ��ʱ��
	QTimer* m_tmPLC;
	QTimer* m_tmPLCRead;//��ȡ����timer

	int  read100Already = 0;
	int read60Already = 0;
	int read20Already = 0;
public:
	virtual void start() ;//��ʼ���
	virtual void StopCheck();//����
	virtual void timerEvent(QTimerEvent *event);//��ʱ������
public slots:
	void UpdateTmLabel();//���ڴ�������ʱ����ʱtimer�ص�
	void PLCTmSlot();
	void PLCReadDataSlot();

signals:
	void DQ_failed();
};
