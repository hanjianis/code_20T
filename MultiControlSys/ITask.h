#pragma once

#include <QObject>
#include <QTimerEvent>
#include "Packet.h"
#include <QDebug>
#include <QTimer>
//�Զ����� ������Եĵ��������������
//û�����⴦��ʱ ���øò����� �������Ҫ�̳��ڸ���
class ITask : public QObject
{
	Q_OBJECT

public:

	ITask(int datatype = 0, QObject *parent = nullptr);
	~ITask();
public:
	int _datatype;
	int _tmid;
	int _tmid_result;//�����ʱ��
	int _lstindex;
	int _stop;
	QTimer* m_tmDelay = nullptr;//������ʱ

public:
	virtual void start() ;//��ʼִ��
	virtual void StopCheck();//����
	virtual void timerEvent(QTimerEvent *event);//timer�ص�
	virtual void AutoSingle() ;//������Ϣ������ ����������
	virtual void AutoSingleResult();//������������Խ��
	virtual int is_stop();//�жϸõ����Ƿ����
	float generateRand(float min, float max);//��min max ֮�����������
	void RandomAtd(AutoTestData & atd);//�޸Ĳ������ʵ��ֵ �������
	void SetSimularData(int srcid, int targetid);//����������Ϣ�������� srcid���������id targetid��Ҫ�����ĸ�label
	void SetSimularData(QString val,int labelid);//����һЩ��Ϣ����ֵ ��Щֵ��֪��ʲô���壬ֻ֪����Ƶ����ô��ʾ��
signals:
	void AddTaskItem(AutoTestData& data);//�ź� �����źŵ�AutoTestDlg ������Ӧ������
	void AddTaskItemResult(AutoTestData& data);////�ź� �����źŵ�AutoTestDlg ������Ӧ��������
	void UpdateToolTipSignal(QString str);//�ź� �����źŵ�AutoTestDlg ���½������ʾ��Ϣ

	void StopSignleTestSignal();//�����������
public slots:
	void TmDelaySlot();//��ʱtimer�Ļص� ��Щ������ʱ ��Ҫ�̶�����ʱ����ʱ

};
