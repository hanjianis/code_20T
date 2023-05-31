#pragma once
#include "Packet.h"
#include "XLManager.h"
#include <QObject>
#include "AutoTestWidget.h"
#include <QTimer>
//�Զ�����->�ۺϲ��� ���ݿ���multest
class MultTestOBJ : public QObject
{
	Q_OBJECT

public:
	MultTestOBJ(AutoTestWidget* at,QWidget *parent);
	~MultTestOBJ();
public:
	QWidget* m_parent=nullptr;
	XLManager* pXL=nullptr;
	
	QTimer* m_tmTestUseTm=nullptr;//���ڵȴ�������ʱ��ʱ��
	QTimer* m_tm1553DelayTm = nullptr;//����1553B��ʱ
	QTimer* m_tmDPUFlash = nullptr;//����DPU FLash����ʱ��ʾ��Ϣ����
	QTimer* m_tmDPUFlashFinish = nullptr;//����DPU Flash����ʱ��ʾ��Ϣ���� ��Ӧ�����ݿ��е�id=38
	QTimer* m_tmPLC = nullptr;//PLC״̬���timer
	QTimer* m_tmCheckState = nullptr;//������ʱ�ȴ����緵�� �¿�ס���棬�������˶�ʱ�� ��start��ʱ������� 
	int _plcState = 0;//PLC״̬ 1:1���Ӻϸ� 2��1���Ӳ��ϸ�  
	int  read100Already = 0;
	int read60Already = 0;
	int read20Already = 0;

	AutoTestWidget* m_at = nullptr;//������� �������ڴ���

	int _lstindex = 0;
	int _datatype = 1;
	int _tmid_mult;//�ۺϲ��ԵĶ�ʱ��id
	int _tmid_mult_result;//�ۺϲ��Խ���Ķ�ʱ��id
	int _delaySec;//�ȴ�������ʱ��ʱ�� 120s 
	int _delay1553;
	int _startTickCount = 0;
	int _JizhunTuRecord;//��׼ͼװ���ļ�¼�� ��1��ʼ��123
	int _JizhunTuState;//���ڱ�ʶ_JizhunTuRecord �ǵ�123 ���ǵ�164 _JizhunTuState=1ʱ_JizhunTuRecord=123 ����_JizhunTuRecord=164
public:
	virtual void start();
	virtual void StopCheck();
	virtual void timerEvent(QTimerEvent *event);
	float generateRand(float min, float max);
private:
	void RandomAtd(AutoTestData & atd);

	void SetSimularData(int srcid, int targetid);
	void SetDQData(int targetid, float fVal);//����������Ϣ������
	void SetSysTmLabel();//������Ϣ���ϵ�ϵͳʱ��
	void SetTestLabel(int labelid, QString str);
signals:
	void AddTaskItem(AutoTestData& data);
	void AddTaskItemResult(AutoTestData& data);
	void UpdateToolTipSignal(QString str);//��ʾ��Ϣ
	void SendStopInsSingal();//֪ͨ���Խ���
	void SendUseTmSignal();//���ڹߵ����� ʱ�䶨ʱ�������Լ�obj�����Ҫ֪ͨ�������ʱ��
public slots:
	void UpdateTmLabel();
	void Update1553Delay();
	void UpdateDPFlash();
	void UpdateDPUFlashFinish();
	void PLCTmSlot();
	void CheckStateSlot();//��·״̬������ʱ�ļ��
};
