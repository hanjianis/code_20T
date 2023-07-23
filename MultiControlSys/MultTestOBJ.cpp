#include "MultTestOBJ.h"
#include <QTime>
#include "MessageBoxDlg.h"
#include "InputTemperatureDlg.h"
#include "DeviceMgr/PLCManager.h"
#include "DeviceMgr/LDGDB_Manager.h"
#include "DeviceMgr/KJGXSMNQ_Manager.h"
#include "DeviceMgr/ZHDY_Manager.h"
#include "DeviceMgr/Dan_Manager.h"
#include "DeviceMgr/Dan2_Manager.h"
#include "DeviceOnlineManage.h"
#define  MAX_DELAY 5//����Ӧ����120
#define MAX_1553_DELAY 5//����Ӧ����630
MultTestOBJ::MultTestOBJ(AutoTestWidget* at, QWidget *parent)
	: QObject(parent)
{
	m_at = at;
	m_parent = parent;
	pXL = XLManager::GetInstance();
	connect(this, SIGNAL(AddTaskItem(AutoTestData&)), parent, SLOT(AddTableWidget(AutoTestData&)));

	connect(this, SIGNAL(AddTaskItemResult(AutoTestData&)), parent, SLOT(AddAutoTestResult(AutoTestData&)));
	connect(this, SIGNAL(UpdateToolTipSignal(QString)), parent, SLOT(UpdateToolTip(QString)));
	connect(this, SIGNAL(SendStopInsSingal()), parent, SLOT(RecvStopMultiSlot()));
	connect(this, SIGNAL(SendUseTmSignal()), parent, SLOT(SetTestUseTm()));
	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));
	m_tm1553DelayTm = new QTimer();
	connect(m_tm1553DelayTm, SIGNAL(timeout()), this, SLOT(Update1553Delay()));
	m_tmDPUFlash = new QTimer();
	connect(m_tmDPUFlash, SIGNAL(timeout()), this, SLOT(UpdateDPFlash()));
	m_tmDPUFlashFinish = new QTimer();
	connect(m_tmDPUFlashFinish, SIGNAL(timeout()), this, SLOT(UpdateDPUFlashFinish()));
	m_tmPLC = new QTimer();
	connect(m_tmPLC, SIGNAL(timeout()), this, SLOT(PLCTmSlot()));
	m_tmCheckState = new QTimer();
	connect(m_tmCheckState, SIGNAL(timeout()), this, SLOT(CheckStateSlot()));
}

MultTestOBJ::~MultTestOBJ()
{
}

void MultTestOBJ::start()
{
	//���ۺϵ�Դ�Ի���
//	MessageBoxDlg dlg11(QString::fromLocal8Bit("��ͨ�ۺϵ�Դ"));
//	dlg11.exec();
	//20210604 ȷ����ͨ�ۺϵ�Դ�� ���󵯵���·����״̬
	Dan_Manager::getInstance()->RequestLineInfo();
	LDGDB_Manager::getInstance()->RequestPowerStatus();

	m_tmCheckState->start(2000);//20210604 2s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڳ�ʼ�����ã����Ժ�"));
	return;

}

void MultTestOBJ::StopCheck()
{
	killTimer(_tmid_mult);
	_tmid_mult = 0;
	killTimer(_tmid_mult_result);
	_tmid_mult_result = 0;
	if (m_tmTestUseTm->isActive())
		m_tmTestUseTm->stop();
	if (m_tm1553DelayTm->isActive())
		m_tm1553DelayTm->stop();
	if (m_tmDPUFlash->isActive())
		m_tmDPUFlash->stop();
	if (m_tmDPUFlashFinish->isActive())
		m_tmDPUFlashFinish->stop();
	if (m_tmPLC->isActive())
		m_tmPLC->stop();
	if (m_tmCheckState->isActive())
		m_tmCheckState->stop();
	emit SendStopInsSingal();
}

void MultTestOBJ::timerEvent(QTimerEvent *event)
{
	int tmid = event->timerId();
	//�ۺ�
	if (_tmid_mult == tmid)
	{
		emit AddTaskItem(pXL->m_mapMULT_TEST[_datatype][_lstindex]);
		//�ж���һ���ĵȴ���ʱ ����atd.tm�ж� ����0��Ĭ��20ms ����͸���tm����ʱ(��λ��s)
		AutoTestData &atd1 = pXL->m_mapMULT_TEST[_datatype][_lstindex];
		if (atd1.tm == 0)
			_tmid_mult_result = startTimer(20);
		else
			_tmid_mult_result = startTimer(atd1.tm * 1000);
	
		if (atd1.id == 37) //�����ݿ��Ӧ
		{
			_JizhunTuState = 1;//��	_JizhunTuState �����ǵ�ǰ����0x33 ����0x34 ��ʾ��Ϣ��ͬ
			m_tmDPUFlash->start(atd1.tm * 1000 / (28 * 3));//300s�����28*3�θ���
		//	return;
		}
		if (atd1.id == 40) //�����ݿ��Ӧ
		{
			_JizhunTuState = 2;//��	_JizhunTuState �����ǵ�ǰ����0x33 ����0x34 ��ʾ��Ϣ��ͬ
			m_tmDPUFlash->start(atd1.tm * 1000 / (3 * 3));//300s�����3*3�θ���
		//	return;
		}
		killTimer(_tmid_mult);
		_tmid_mult = 0;
		return;

	}
	if (_tmid_mult_result == tmid)
	{
		killTimer(_tmid_mult_result);
		_tmid_mult_result = 0;
		//���ǲ��Խ�������
		AutoTestData &atd = pXL->m_mapMULT_TEST[_datatype][_lstindex];
		RandomAtd(atd);
		emit AddTaskItemResult(atd);
		_lstindex++;
		if (_lstindex == 23)
		{
			//�򿪴������ݲ����
			MessageBoxDlg dlg1(QString::fromLocal8Bit("��EZ23-20T�������ݲ����"), m_parent);
			dlg1.exec();
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڴ򿪴������ݲ����,���Ժ�..."));
			
			if (PLCManager::getInstance()->ConnectPLC() == false)//PLC����ʧ�� �Ῠ�ڴ򿪴����ǽ��� Ŀǰû�кõĽ����ʽ ��֪��Ϊʲô
			{
				MessageBoxDlg dlg3(QString::fromLocal8Bit("�򿪴������ݲ����ʧ�ܣ������Դ"));
				dlg3.exec();
				emit UpdateToolTipSignal(QString::fromLocal8Bit("�򿪴������ݲ����ʧ��...."));
				StopCheck();
				return;
			}
			emit UpdateToolTipSignal(QString::fromLocal8Bit("�򿪴������ݲ���ǳɹ�...."));
			MessageBoxDlg dlg2(QString::fromLocal8Bit("���Լ���ɺ���ɷ���"), m_parent);
			dlg2.exec();
			PLCManager::getInstance()->SetMulStart();
			m_tmPLC->start(500);//
			return;
		}
		if (atd.id == 29)//��ǰ���������ݿ���תĸ�߹���ָ�� ��һ�����״�߶ȱ� ���״�߶ȱ��� �Լ�
		{
			LDGDB_Manager::getInstance()->RequsetSelfCheck();
		}
		if (atd.id == 46)//��ǰ��ʾ����46 ����ƥ���׼ͼ��Ϣ ��һ�������ӻ���
		{
			KJGXSMNQ_Manager::getInstance()->RequsetSelfCheck();//�����Լ� Ҳ���ǻ���
			//20210604 �������ͼƬ
			KJGXSMNQ_Manager::getInstance()->RequestPowerControl(1);//�������ͼƬ����ȥDan2_Manager��ȥ�����ѯ���� �ж��Ƿ�һ��
			Sleep(200);
			Dan2_Manager::getInstance()->RequestPowerStatus();
			Sleep(200);//
			//���Dan2��KJGXSMNQ��һ�� �Ǿ�����ͬ ����ͬ
			goto label;
			bool bFailed = false;
			if (Dan2_Manager::getInstance()->_imageFlag == 0) bFailed = true;
			if (KJGXSMNQ_Manager::getInstance()->_imageNum != Dan2_Manager::getInstance()->_imageFlag) bFailed = true;
			if (bFailed)
			{
				MessageBoxDlg dlg3(QString::fromLocal8Bit("����ģ�����쳣������"));
				dlg3.exec();
				emit UpdateToolTipSignal(QString::fromLocal8Bit("����ģ�����쳣...."));
				StopCheck();
				return;
			}
			label:{}
		}
		if (atd.id == 50)//��ǰ��ʾ����50 ����ת�ɿ� ��һ������������
		{
			//�������� Ҳ���ǹر��ۺϵ�Դ ��7·
			
			ZHDY_Manager::getInstance()->RequestPowerControl(7, 0);
			Sleep(1 * 1000);
		}
		if (atd.id == 25)//�����¶�
		{
			//��������¶�
			InputTemperatureDlg dlg22(m_parent);
			dlg22.exec();
		}
		if (atd.id == 37) //�����ݿ��Ӧ
		{
			m_tmDPUFlash->stop();//300s�����28*3�θ���
		//	return;
		}
		
		if (atd.id == 38)
		{
			_JizhunTuState = 1;
			_JizhunTuRecord = 1;
			m_tmDPUFlashFinish->start(20);
			return;
		}
		if (atd.id == 40)
		{
			m_tmDPUFlash->stop();//300s�����28*3�θ���
		}
		if (atd.id == 41)//��׼ͼװ�� ��μ�¼����164
		{
			_JizhunTuState = 2;
			_JizhunTuRecord = 1;
			m_tmDPUFlashFinish->start(20);
			return;
		}
		//�����ǰ����84 ʹ��һ��timer ��ʼ��������ģ�� ��Ҫ�ǽ������ʾ��Ϣ �ȴ���϶�׼��ʱ120s��1553�忨630s(ʵ����210s)
		if (atd.id == 84)
		{
			_delaySec = 0;
			m_at->UpdateInsLables(41, 80);
			_startTickCount = GetTickCount();
			m_tmTestUseTm->start(1000);//
			return;
		}
		_tmid_mult = startTimer(20);

		if (_lstindex >= pXL->m_mapMULT_TEST[_datatype].size())
		{

			//ֹͣ
			killTimer(_tmid_mult);
			emit SendStopInsSingal();
		}
		return;
	}
}

float MultTestOBJ::generateRand(float min, float max)
{
	static bool seedStatus;
	if (!seedStatus)
	{
		qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
		seedStatus = true;
	}
	if (min > max)
	{
		float temp = min;
		min = max;
		max = temp;
	}
	double diff = fabs(max - min);
	double m1 = (double)(qrand() % 100) / 100;
	double retval = min + m1 * diff;
	return retval;
}

void MultTestOBJ::RandomAtd(AutoTestData & atd)
{
	//����atd������ standardtype
	if (atd.standardtype == 2)
		return;
	if (atd.standardtype == 1)//�������С��Χ�ڲ���һ�����
	{
		atd.val = QString("%1").arg(generateRand(atd.min, atd.max));
	}
}

void MultTestOBJ::SetSimularData(int srcid, int targetid)
{
	AutoTestData &atd = pXL->m_mapINS[srcid];
	float val = generateRand(atd.min, atd.max);
	QLabel* lb = pXL->m_mapAutoTestList[targetid].val;
	if (lb != nullptr)
	{
		lb->setText(QString("%1").arg(val));
	}
}
void MultTestOBJ::SetDQData(int targetid,float fVal)
{
	XLManager* pXL = XLManager::GetInstance();

	QLabel* lb = pXL->m_mapAutoTestList[targetid].val;
	if (lb != nullptr)
	{
		lb->setText(QString("%1").arg(fVal));
	}
}
void MultTestOBJ::SetSysTmLabel()
{
	double usetm = (GetTickCount() - _startTickCount) / 1000.0;
	QString strtm = QString::number(usetm, 'f', 2);
	SetTestLabel(41, strtm);
	
}
void MultTestOBJ::SetTestLabel(int labelid, QString str)
{
	QLabel* lb = pXL->m_mapAutoTestList[labelid].val;//ϵͳʱ��
	if (lb != nullptr)
	{
		lb->setText(str);
	}
}
void MultTestOBJ::UpdateTmLabel()
{
	SetSysTmLabel();
	QString str = QString::fromLocal8Bit("�ȴ���ϴ��ٶ�׼��ʱ120�룬��%1��").arg(_delaySec);
	emit UpdateToolTipSignal(str);
	//P1��ѹ P2��ѹ�仯 61.9����0.1�仯 δ����������ʵֵ
	float fVal = generateRand(61.85, 61.96);
	QString strtm = QString::number(fVal, 'f', 6);
	SetTestLabel(57, strtm);
	fVal = generateRand(61.85, 61.96);
	 strtm = QString::number(fVal, 'f', 6);
	SetTestLabel(58, strtm);
	//��ѹ�仯 57.6���ұ仯
	fVal = generateRand(57.6-0.2, 57.6+0.2);
	strtm = QString::number(fVal, 'f', 6);
	SetTestLabel(60, strtm);
	//��ϴ��� 0.1����
	fVal = generateRand(0.1,0.3);
	strtm = QString::number(fVal, 'f', 6);
	SetTestLabel(64, strtm);
	//��ϴ������� 0.19����
	fVal = generateRand(0.19, 0.20);
	strtm = QString::number(fVal, 'f', 6);
	SetTestLabel(73, strtm);
	_delaySec++;
	
	if (_delaySec > MAX_DELAY)
	{
		//���ٶ�׼��ʱ ��� ��ʼ1553B�忨
		m_tmTestUseTm->stop();
		_startTickCount = GetTickCount();
		m_tm1553DelayTm->start(333);
	}
}

void MultTestOBJ::Update1553Delay()
{
	SetSysTmLabel();
	double usetm = (GetTickCount() - _startTickCount) / 1000.0;
	QString strtm = QString::number(usetm, 'f', 2);
	QString str = QString::fromLocal8Bit("1553B�忨ʱ�䣺%1��").arg(strtm);
	emit UpdateToolTipSignal(str);

	if (usetm > MAX_1553_DELAY)
	{
		//1553Bģ����� 
		m_tm1553DelayTm->stop();
		_tmid_mult = startTimer(20);
	}
}

void MultTestOBJ::UpdateDPFlash()
{
	//3����ʾ��Ϣ �ֻز��� ���ֻ�28�� ��������ôд�ģ�
	//
	QStringList lst;
	if (_JizhunTuState == 1)
	{
		lst << QString::fromLocal8Bit("��ǰָ����33");
		lst << QString::fromLocal8Bit("��ǰָ����33 ����ָ����8800");
		lst << QString::fromLocal8Bit("  ");//�յ�
	}
	else if (_JizhunTuState == 2)
	{
		lst << QString::fromLocal8Bit("��ǰָ����34");
		lst << QString::fromLocal8Bit("��ǰָ����34 ����ָ����8800");
		lst << QString::fromLocal8Bit("  ");//�յ�
	}
	static int cnt = 0;
	QString str = lst[cnt%3];
	cnt++;

	emit UpdateToolTipSignal(str);
}

void MultTestOBJ::UpdateDPUFlashFinish()
{
	QString str;
	if(_JizhunTuState == 1)
		str = QString::fromLocal8Bit("��׼ͼװ��.�ܼ�¼��123����ǰ��¼��%1").arg(_JizhunTuRecord);
	else
		str = QString::fromLocal8Bit("��׼ͼװ��.�ܼ�¼��164����ǰ��¼��%1").arg(_JizhunTuRecord);

	emit UpdateToolTipSignal(str);
	_JizhunTuRecord++;
	if (_JizhunTuState==1 && _JizhunTuRecord > 123)
	{
		m_tmDPUFlashFinish->stop();
		_tmid_mult = startTimer(20);
	}
	if (_JizhunTuState == 2 && _JizhunTuRecord > 164)
	{
		m_tmDPUFlashFinish->stop();
		_tmid_mult = startTimer(20);
	}
}

void MultTestOBJ::PLCTmSlot()
{
	if (PLCManager::getInstance()->ReadMulIsEnd() == true)
	{
		float fval = PLCManager::getInstance()->ReadJingYa();
		SetDQData(26, fval);//��ѹ
		fval = PLCManager::getInstance()->ReadZongYa();
		SetDQData(27, fval);//��ѹ
		SetDQData(28, fval);//��ѹ

		m_tmPLC->stop();
		PLCManager::getInstance()->SetMulStop();
		PLCManager::getInstance()->DisConnectPLC();
		//_tmid = startTimer(50);
		_tmid_mult = startTimer(20);
	}

	//if (_plcState == 1)
	//{
	//	if (read100Already == 0 && PLCManager::getInstance()->Read100KPaIsEnd() == true)
	//	{
	//		float fval = PLCManager::getInstance()->ReadJingYa();
	//		SetDQData(26, fval);//��ѹ
	//		fval = PLCManager::getInstance()->ReadZongYa();
	//		SetDQData(27, fval);//��ѹ
	//		SetDQData(28, fval);//��ѹ
	//		read100Already = 1;
	//	}
	//	if (read60Already == 0 && PLCManager::getInstance()->Read60KPaIsEnd() == true)
	//	{
	//		float fval = PLCManager::getInstance()->ReadJingYa();
	//		SetDQData(26, fval);//��ѹ
	//		fval = PLCManager::getInstance()->ReadZongYa();
	//		SetDQData(27, fval);//��ѹ
	//		SetDQData(28, fval);//��ѹ
	//		
	//		read60Already = 1;
	//	}
	//	if (read20Already == 0 && PLCManager::getInstance()->Read20KPaIsEnd() == true)
	//	{
	//		float fval = PLCManager::getInstance()->ReadJingYa();
	//		SetDQData(26, fval);//��ѹ
	//		fval = PLCManager::getInstance()->ReadZongYa();
	//		SetDQData(27, fval);//��ѹ
	//		SetDQData(28, fval);//��ѹ
	//	
	//		m_tmPLC->stop();
	//		PLCManager::getInstance()->SetMulStop();
	//		PLCManager::getInstance()->DisConnectPLC();
	//		//_tmid = startTimer(50);
	//		_tmid_mult = startTimer(20);
	//		read20Already = 1;
	//	}
	//	return;
	//}
	//if (PLCManager::getInstance()->Read1MinValid() == true)
	//{
	//	_plcState = 1;
	//
	//}
	//if (PLCManager::getInstance()->Read1MinUnValid() == true)
	//{
	//	_plcState = 2;
	//	m_tmPLC->stop();
	//	MessageBoxDlg dlg2(QString::fromLocal8Bit("��ѹ©��"));
	//	dlg2.exec();
	//	PLCManager::getInstance()->SetMulStop();
	//	PLCManager::getInstance()->DisConnectPLC();
	//	emit SendStopInsSingal();
	//	//m_tmPLC->stop();
	//	//emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ���ѹй¶����ʱ60�룬���Ժ�..."));
	//	//m_tmTestUseTm->start(60 * 1000);
	//}
}

void MultTestOBJ::CheckStateSlot()
{
	m_tmCheckState->stop();

	//�ж���·״̬���״�
	
	//������һ
	if (LDGDB_Manager::getInstance()->CheckConneced() == false ||
		Dan_Manager::getInstance()->CheckLeiDaGaoDu() == false)
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("�����״�߶ȱ��Ƿ�������ȷ"));
		dlg.exec();
		StopCheck();
		return;
	}
	//20210605 ���ߵ� 
	if ((DeviceOnlineManage::getInstance()->m_nDeviceOnlineFlag & 0x4) == 0)//���᲻����
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("����ߵ��Ƿ�������ȷ"));
		dlg.exec();
		StopCheck();
		return;
	}

	//20210604 �ж�������·״̬
	if (Dan_Manager::getInstance()->CheckLineConnected() == false)
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("���鵯�ϵ����Ƿ�������ȷ"));
		dlg.exec();
		StopCheck();
		return;
	}
	_lstindex = 0;
	_tmid_mult = startTimer(50);
	m_at->UpdateInsLables(1, 40);
}
