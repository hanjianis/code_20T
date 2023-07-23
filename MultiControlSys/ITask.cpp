#include "ITask.h"
#include "XLManager.h"
#include <QDebug>
#include <QTime>
#include "MyToolTipDlg.h"
#include "MyMessageBox.h"
#include "DeviceMgr/Dan_Manager.h"
#include "DeviceMgr/ZHDY_Manager.h"
#include "DeviceMgr/LDGDB_Manager.h"
#include "DeviceMgr/KJGXSMNQ_Manager.h"
#include "DeviceMgr/CK_Manager.h"
#include "DeviceMgr/Dan2_Manager.h"
#include "MessageBoxDlg.h"

ITask::ITask(int datatype,QObject *parent)
	: QObject(parent)
{
	connect(this, SIGNAL(AddTaskItem(AutoTestData&)), parent, SLOT(AddTableWidget(AutoTestData&)));

	connect(this, SIGNAL(AddTaskItemResult(AutoTestData&)), parent, SLOT(AddAutoTestResult(AutoTestData&)));
	connect(this, SIGNAL(UpdateToolTipSignal(QString)), parent, SLOT(UpdateToolTip(QString)));
	_datatype = datatype;
	_lstindex = 0;
	_stop = 0;
	m_tmDelay = new QTimer();
	connect(m_tmDelay, SIGNAL(timeout()), this, SLOT(TmDelaySlot()));

	connect(this, SIGNAL(StopSignleTestSignal()), parent, SLOT(DQ_Failed()));
}

ITask::~ITask()
{
}

void ITask::start()
{

	_tmid = startTimer(50);
}

void ITask::StopCheck()
{
	killTimer(_tmid);
	_tmid = 0;
	killTimer(_tmid_result);
	_tmid_result = 0;
	_stop = 1;
}

void ITask::timerEvent(QTimerEvent *event)
{
	int tmid = event->timerId();
	if (tmid == _tmid)
	{
		killTimer(_tmid);
		_tmid = 0;
		XLManager* pXL = XLManager::GetInstance();
		AutoTestData& atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
		emit AddTaskItem(atd);
		
		_tmid_result = startTimer(100);
		return;
	}
	if (tmid == _tmid_result)
	{
		//���²��Խ��
		killTimer(_tmid_result);
		_tmid_result = 0;

		AutoSingleResult();
		XLManager* pXL = XLManager::GetInstance();
		AutoTestData& atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
	//	RandomAtd(atd);
		//emit AddTaskItemResult(atd);
		if (atd.id == 117)//��117������º���һ��118��ʾ��������� ��ʾ������������Ƶ���ʾ
		{
			MyToolTipDlg dlg(QString::fromLocal8Bit("��ʾ��Ϣ"), QString::fromLocal8Bit("����Ƽ�������������ֱ���ӹ�Դ��"));//���ʱ�� Ӧ�ÿ�������ƿ��� ����udpͨ��
			dlg.exec();

			//�������
			Dan_Manager::getInstance()->RequsetLamControl(1);
			MyMessageBox dlg2(QString::fromLocal8Bit("ȷ����ʾ"), QString::fromLocal8Bit("������Ƿ�������"));//���ʱ�� Ӧ�ÿ�������ƿ��� ����udpͨ��
			dlg2.exec();
		}
		if (atd.id == 51)//��ǰ��ʾ����תĸ��ָ�� ��һ�����״�߶ȱ��Լ� ���״�߶ȱ��� �Լ�
		{
			LDGDB_Manager::getInstance()->RequsetSelfCheck();
		}
		

		_lstindex++;
			
		if (_lstindex >= pXL->m_mapSINGLE_TEST[_datatype].count())
		{

			killTimer(_tmid_result);
			_lstindex = 0;
			_stop = 1;
			return;
		}
		atd = pXL->m_mapSINGLE_TEST[_datatype].at(_lstindex);
	
		//��������� �������״�߶�
		//���ø߶�ʱ ��û����ʾ�õ�����ֵ ���и��� ��������ģ�� ����������udp
		if (atd.id == 58)//��һ�����״�߶�100�� �����״�߶�
		{
			LDGDB_Manager::getInstance()->RequestPowerControl(100, 0);//˥��ֵ��֪���Ƕ��� ��д��0
		}
		if (atd.id == 59)//��һ�����״�߶�1000�� �����״�߶�
		{
			LDGDB_Manager::getInstance()->RequestPowerControl(1000, 0);//˥��ֵ��֪���Ƕ��� ��д��0
		}
		if (atd.id == 60)//��һ�����״�߶�1500�� �����״�߶�
		{
			LDGDB_Manager::getInstance()->RequestPowerControl(1500, 0);//˥��ֵ��֪���Ƕ��� ��д��0
		}
		//��������ģ����
		if (atd.id == 117)//��һ�������ӻ���
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
			label :{}
		}
		if (atd.id == 121)
		{
			//�ر������
		//	Dan_Manager::getInstance()->RequsetLamControl(0);
			//�������� Ҳ���ǹرճ̿ع����� ��7·
			CK_Manager* ck = new CK_Manager(nullptr);
			ck->RequestPowerControl(7, 0);
			Sleep(1 * 1000);
		}

		//�����һ����Ϣ ��ʾ ��Ҫ��ʱ���������ʱtimer
		if (atd.tm != 0)
		{
			//�ڴ�ͬʱ ������һ������ʾ��Ϣ������
			emit UpdateToolTipSignal(atd.tip);
			m_tmDelay->start(atd.tm * 1000);
			return;
		}
		_tmid = startTimer(50);
		return;
	}
}

void ITask::AutoSingle()
{
	XLManager* pXL = XLManager::GetInstance();
	AutoTestData& atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
	emit AddTaskItem(atd);

	//_lstindex++;
	//if (_lstindex >= pXL->m_mapSINGLE_TEST[_datatype].count())
	//{

	//	killTimer(_tmid);
	//	_lstindex = 0;
	//	_stop = 1;
	//	return;
	//}
	//atd = pXL->m_mapSINGLE_TEST[_datatype].at(_lstindex);
	
}

void ITask::AutoSingleResult()
{

	XLManager* pXL = XLManager::GetInstance();
	AutoTestData& atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
	RandomAtd(atd);
	if (atd.id == 49)//ĸ�ߵ�ѹ ������Ϣ�� ĸ�ߵ�ѹλ��datatype=6 û�е������� ������itask�ﴦ��
	{
		SetSimularData(49, 7);
	}
	if (atd.id == 27)//��ͨ���Լ�
	{
		SetSimularData(27, 19);
	}
	if (atd.id == 28)//��ͨ���Լ�
	{
		SetSimularData(28, 20);
	}
	if (atd.id == 124)//﮵�ص�ѹ
	{
		SetSimularData(124, 8);
	}
	if (atd.id == 52)//�״���Լ�
	{
		SetSimularData(52,21);
	}
	if (atd.id == 53)//�״���Լ�
	{
		SetSimularData(53, 22);
	}
	if (atd.id == 58)//�״�߶�100m
	{
		SetSimularData(58, 30);
	}
	if (atd.id == 59)//�״�߶�1000m
	{
		SetSimularData(59, 30);
	}
	if (atd.id == 60)//�״�߶�1500m
	{
		SetSimularData(60, 30);
	}
	emit AddTaskItemResult(atd);
}

int ITask::is_stop()
{
	return _stop;
}

float ITask::generateRand(float min, float max)
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

void ITask::RandomAtd(AutoTestData & atd)
{
	if (atd.type == 2)
		return;
	//����atd������ standardtype
	if (atd.standardtype == 2)
		return;
	if (atd.standardtype == 1)//�������С��Χ�ڲ���һ�����
	{
		atd.val = QString("%1").arg(generateRand(atd.min, atd.max));
	}
}

void ITask::SetSimularData(int srcid, int targetid)
{
	XLManager* pXL = XLManager::GetInstance();
	AutoTestData& atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
	QString val = atd.val;
	QLabel* lb = pXL->m_mapAutoTestList[targetid].val;
	if (lb != nullptr)
	{
		lb->setText(QString("%1").arg(val));
	}
}

void ITask::SetSimularData(QString val, int labelid)
{
	XLManager* pXL = XLManager::GetInstance();
	QLabel* lb = pXL->m_mapAutoTestList[labelid].val;
	if (lb != nullptr)
	{
		lb->setText(QString("%1").arg(val));
	}
}

void ITask::TmDelaySlot()
{
	m_tmDelay->stop();
	_tmid = startTimer(50);
}
