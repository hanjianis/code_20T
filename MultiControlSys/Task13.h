#pragma once

#include <QObject>
#include "ITask.h"
//�Զ����� ������Ե�datatype=13��������
class Task13 : public ITask
{
	Q_OBJECT

public:
	Task13(QObject *parent);
	~Task13();
	int _JizhunTuState;
	int _JizhunTuRecord;//��׼ͼװ���ļ�¼�� ��1��ʼ��123
	QTimer* m_tmDPUFlash = nullptr;//����DPU FLash����ʱ��ʾ��Ϣ����
	QTimer* m_tmDPUFlashFinish = nullptr;//����DPU Flash����ʱ��ʾ��Ϣ���� ��Ӧ�����ݿ��е�id=38
	QTimer* m_tmTestUseTm;//���ڲ���ʹ��ʱ��
public:
	virtual void start();
	virtual void StopCheck();//����
	virtual void timerEvent(QTimerEvent *event);
public slots:
	void UpdateTmLabel();
	void UpdateDPFlash();
	void UpdateDPUFlashFinish();
};
