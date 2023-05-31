#include "INSTestOBJ.h"
#include "MessageBoxDlg.h"
#include "HecDataManager.h"
#include "MyToolTipDlg.h"
#include "InsConfigDlg.h"
#include <QTime>
#include "DeviceMgr/Dan2_Manager.h"
#include "DeviceMgr/ZHDY_Manager.h"
#include "DeviceMgr/Dan_Manager.h"
#include "DeviceMgr/LDGDB_Manager.h"
#include "DeviceOnlineManage.h"
INSTestOBJ::INSTestOBJ(AutoTestWidget* at, QWidget *parent)
	: QObject(parent)
{
	m_at = at;
	m_Parent = parent;
	pXL = XLManager::GetInstance();
	connect(this, SIGNAL(AddTaskItem(AutoTestData&)), parent, SLOT(AddTableWidget(AutoTestData&)));

	connect(this, SIGNAL(AddTaskItemResult(AutoTestData&)), parent, SLOT(AddAutoTestResult(AutoTestData&)));
	connect(this, SIGNAL(UpdateToolTipSignal(QString)), parent, SLOT(UpdateToolTip(QString)));
	connect(this, SIGNAL(SendStopInsSingal()), parent, SLOT(RecvStopInsSlot()));
	connect(this, SIGNAL(SendUseTmSignal()), parent, SLOT(SetTestUseTm()));

	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));

	m_tmCheckState = new QTimer();
	connect(m_tmCheckState, SIGNAL(timeout()), this, SLOT(CheckStateSlot()));
}

INSTestOBJ::~INSTestOBJ()
{
}

void INSTestOBJ::start()
{
	//���ۺϵ�Դ�Ի���
	MessageBoxDlg dlg11(QString::fromLocal8Bit("��ͨ�ۺϵ�Դ"));
	dlg11.exec();
	//20210604 ȷ����ͨ�ۺϵ�Դ�� ���󵯵���·����״̬
	Dan_Manager::getInstance()->RequestLineInfo();
	LDGDB_Manager::getInstance()->RequestPowerStatus();

	m_tmCheckState->start(2000);//20210604 2s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڳ�ʼ�����ã����Ժ�"));
	return;

}

void INSTestOBJ::StopCheck()
{
	killTimer(_tmid_ins);
	_tmid_ins = 0;
	killTimer(_tmid_ins_result);
	_tmid_ins_result = 0;
	if (m_tmTestUseTm->isActive())
		m_tmTestUseTm->stop();
	if (m_tmCheckState->isActive())
		m_tmCheckState->stop();
	emit UpdateToolTipSignal(QString::fromLocal8Bit("�ߵ��������̽���"));
	//
	HecDataManager::getInstance()->GetHecData(0);//������ʱ�ϱ�
	_insState = 0;
	emit SendStopInsSingal();
}

void INSTestOBJ::timerEvent(QTimerEvent *event)
{
	//������Ҫע�����starttimer ��һ��timerid���������һ��timerid�ǲ���ȷ�� 
	int tmid = event->timerId();
	//�ߵ����� �������໥��
	
	if (tmid == _tmid_ins_result)
	{

		killTimer(_tmid_ins_result);
		_tmid_ins_result = 0;
		//���ǲ��Խ�������
		AutoTestData &atd = pXL->m_mapINS[_lstindex++];
		RandomAtd(atd);
		emit AddTaskItemResult(atd);

		if (_lstindex == 19)
		{
			//QMessageBox::inforrimation(this,QString::fromLocal8Bit("������ʾ"), QString::fromLocal8Bit("���ͨ��Ƶ��Դ"),QMessageBox::Ok);
			MyToolTipDlg dlgTool1(QString::fromLocal8Bit("������ʾ"), QString::fromLocal8Bit("��ͨ�����ź�ת��װ��"), m_Parent);
			dlgTool1.exec();
			MyToolTipDlg dlgTool(QString::fromLocal8Bit("������ʾ"), QString::fromLocal8Bit("���ͨ��Ƶ��Դ"), m_Parent);
			dlgTool.exec();
			emit UpdateToolTipSignal(QString::fromLocal8Bit("������ȷ�������λ����Ϣ���С��200m"));
			InsConfigDlg dlg;
			dlg.exec();
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x84ָ���ʸ���֣���ʱ10s�����Ժ�"));

		}
		
		if (_lstindex == 28)//��ʼ��׼
		{
			//����20min�Ķ�ʱ��
			emit UpdateToolTipSignal(QString::fromLocal8Bit("�ߵ���׼"));
			_tmid_ins = startTimer(3*60*1000);//3���� ������ ����ȴ�̫��
			//_tmid_ins = startTimer(20*60*1000);//20����
			_insState = 1;
			m_at->UpdateInsLables(81, 120);
			_startTickCount = GetTickCount();
			HecDataManager::getInstance()->GetHecData(200);//200ms��ʱ��ȡ
		}
		else
		{
			if (_lstindex == 20)
			{
				_tmid_ins = startTimer(10 * 1000);//��ʱ10s ����2s 
			}
			else
				_tmid_ins = startTimer(150);

			if (_lstindex > pXL->m_mapINS.size())
			{
				//ֹͣ
				killTimer(_tmid_ins);
				emit UpdateToolTipSignal(QString::fromLocal8Bit("�ߵ��������̽���"));
				//
				HecDataManager::getInstance()->GetHecData(0);//������ʱ�ϱ�
				_tmid_ins = 0;
				_insState = 0;
				m_tmTestUseTm->stop();
				emit SendStopInsSingal();
				return;
			}
		}
		return;
	}
	if (tmid == _tmid_ins)
	{
		if (_insState == 1)//��׼��20���ӵ���
		{
			_tmid_ins = startTimer(1*60 * 1000);//3�� ������ ����ȴ�̫��
			//_tmid_ins = startTimer(10 * 60 * 1000);//10���� ����
			_insState = 2;
			_startTickCount = GetTickCount();
			emit UpdateToolTipSignal(QString::fromLocal8Bit("�ߵ�����"));
			//����������������仯
			m_at->UpdateInsLables(121, 141);
			return;
		}
		if (_insState == 2)//�������
		{
			_insState = 0;
		}

		 //��ʼ�������ݸ���
		{
			emit AddTaskItem(pXL->m_mapINS[_lstindex]);

			killTimer(_tmid_ins);
			_tmid_ins = 0;
			_tmid_ins_result = startTimer(100);
		}
		return;
	}

	

}
 //���������
 float INSTestOBJ::generateRand(float min, float max)
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
void INSTestOBJ::RandomAtd(AutoTestData & atd)
{
	//����atd������ standardtype
	if (atd.standardtype == 2)
		return;
	if (atd.standardtype == 1)//�������С��Χ�ڲ���һ�����
	{
		atd.val = QString("%1").arg(generateRand(atd.min,atd.max));
	}
}

void INSTestOBJ::SetSimularData(int srcid, int targetid)
{
	AutoTestData &atd = pXL->m_mapINS[srcid];
	float val = generateRand(atd.min, atd.max);
	QLabel* lb = pXL->m_mapAutoTestList[targetid].val;
	if (lb != nullptr)
	{
		lb->setText(QString("%1").arg(val));
	}
}

void INSTestOBJ::UpdateTmLabel()
{
	double usetm = (GetTickCount() - _startTickCount) /1000.0;

	//ת����00:00:00��ʽ
	//QString str = QString("%1").arg(usetm, 2, 10, QLatin1Char('0'));
	QString str = QString::number(usetm, 'f', 2);
	//����dan2manager ��ȡ���Ƕ�λ��Ϣ
	if (_insState != 0)
	{
		Dan2_Manager::getInstance()->RequestPowerControl();

	}
	//���¶�׼ʱ��
	if (_insState == 1)//���ڶ�׼״̬
	{
		//xlmanager��m_mapAutoTestList��81���Ƕ�׼ʱ��label
		QLabel* lb = pXL->m_mapAutoTestList[81].val;
		if (lb != nullptr)
		{
			lb->setText(str);
		}
		//���һЩģ������
		//���Դ������� ���ݹߵ����������� �����ݵ���ֵ��Χ ����ģ�� ��׼�Ĺ��Դ������� map��43
		SetSimularData(43,89);
		//ƽ̨�¿ص���
		SetSimularData(30, 98);
		//XYZ������ ���ٶȼ����� ��׼ �������Ӧ��34��Z) 35(X) 36(Y)
		SetSimularData(34, 99);
		SetSimularData(35, 100);
		SetSimularData(36, 101);
		//�������þ���ø�����
		//GPS���� ��֪����ô��Ӧ �����Ǳ仯��
		//����ʱ���ܷ� ����ʱ���� Ҳ��֪����ô��Ӧ
		//ZXY��Ư��ֵ ��Ӧ�ڶ�׼������ 
		SetSimularData(37, 118);
		SetSimularData(39, 119);
		SetSimularData(41, 120);
	}
	if (_insState == 2)//���ڵ���״̬
	{
		//xlmanager��m_mapAutoTestList��121���ǵ���ʱ��label
		QLabel* lb = pXL->m_mapAutoTestList[121].val;
		if (lb != nullptr)
		{
			lb->setText(str);
		}
		//���һЩģ������
		//���Դ������� ���ݹߵ����������� �����ݵ���ֵ��Χ ����ģ�� ��׼�Ĺ��Դ������� map��53
		SetSimularData(53, 131);
		//ƽ̨�¿ص���
		SetSimularData(52, 132);
	}
}

void INSTestOBJ::CheckStateSlot()
{
	m_tmCheckState->stop();
	//�ж���·״̬���״�
	
	//20210604 �ж�������·״̬
	if (Dan_Manager::getInstance()->CheckLineConnected() == false)
	{
		MessageBoxDlg dlg(QString::fromLocal8Bit("���鵯�ϵ����Ƿ�������ȷ"));
		dlg.exec();
		StopCheck();
		return;
	}
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
	_lstindex = 1;
	_insState = 0;
	m_at->UpdateInsLables(1, 40);
	_tmid_ins = startTimer(50);
	m_tmTestUseTm->start(800);
}
