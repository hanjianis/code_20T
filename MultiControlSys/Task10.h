#pragma once

#include <QObject>
#include "ITask.h"
//�Զ����� ������Ե�datatype=10��������
class Task10 : public ITask
{
	Q_OBJECT

public:
	Task10(QObject *parent);
	~Task10();
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