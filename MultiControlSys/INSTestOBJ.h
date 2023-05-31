#pragma once

#include <QObject>
#include <QTimerEvent>
#include "Packet.h"
#include "XLManager.h"
#include "AutoTestWidget.h"
#include <QTimer>
//�ߵ������߼�
//�Զ�����->�ߵ�����ʱ �����ö��� ����ʼִ��
//�����ö�ʱ�����½����������Լ����Խ�� �����;�����⴦�� �͸���������id������ ������ʱ֮��
//�ߵ����Զ�Ӧ��������λ�����ݿ� ins��
class INSTestOBJ : public QObject
{
	Q_OBJECT

public:

	INSTestOBJ(AutoTestWidget* at, QWidget *parent);
	~INSTestOBJ();
	//
	QWidget* m_Parent = nullptr;//�����ھ��
	XLManager* pXL;//���ݿ�ĵ���
	int _startTickCount = 0;//����ʹ��ʱ��
	int _lstindex = 0;//����ֵ �ߵ������ֵ��ʶ�� �õ���������id ���ݿ����ܿ���
	int _datatype = 1;//�������� һֱ��1
	int _tmid_ins;//�ߵ����ԵĶ�ʱ��id
	int _tmid_ins_result;//�ߵ����Խ���Ķ�ʱ��id
	int _insState = 0;//�ߵ�״̬ 1����׼ 2������
	QTimer* m_tmTestUseTm;//���ڲ���ʹ��ʱ��
	QTimer* m_tmCheckState = nullptr;//������ʱ�ȴ����緵�� �¿�ס���棬�������˶�ʱ�� ��start��ʱ������� 
	AutoTestWidget* m_at = nullptr;//������� �������ڴ���
public:
	virtual void start();//��ʼ
	virtual void StopCheck();
	virtual void timerEvent(QTimerEvent *event);//��ʱ���ص�
	float generateRand(float min, float max);//���������
signals:
	void AddTaskItem(AutoTestData& data);//���²����� ���õ���
	void AddTaskItemResult(AutoTestData& data);//���²��Խ��
	void UpdateToolTipSignal(QString str);//������ʾ��Ϣ
	void SendStopInsSingal();//֪ͨ���Խ���
	void SendUseTmSignal();//���ڹߵ����� ʱ�䶨ʱ�������Լ�obj�����Ҫ֪ͨ�������ʱ��
private:
	void RandomAtd(AutoTestData & atd);//������Խ��
	void SetSimularData(int srcid, int targetid);//���ý�����������Ϣ��
public slots:
	void UpdateTmLabel();//��ʱ��ʱ���ص� 
	void CheckStateSlot();//��·״̬������ʱ�ļ��
};
