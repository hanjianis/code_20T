#include "Task10.h"
#include "XLManager.h"
#include "KJGXSMNQ_Manager.h"
#include "Dan2_Manager.h"
#include "MessageBoxDlg.h"
Task10::Task10(QObject *parent)
	: ITask(10, parent)
{
	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));
	m_tmDPUFlash = new QTimer();
	connect(m_tmDPUFlash, SIGNAL(timeout()), this, SLOT(UpdateDPFlash()));
	m_tmDPUFlashFinish = new QTimer();
	connect(m_tmDPUFlashFinish, SIGNAL(timeout()), this, SLOT(UpdateDPUFlashFinish()));
}

Task10::~Task10()
{
}

void Task10::start()
{
	//�������и���ʱ3s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x30ָ���ʸ���֡��ӳ�3��.���Ժ�..."));
	m_tmTestUseTm->start(3 * 1000);
}

void Task10::StopCheck()
{
	ITask::StopCheck();
	if (m_tmTestUseTm->isActive())
		m_tmTestUseTm->stop();
	if (m_tmDPUFlash->isActive())
		m_tmDPUFlash->stop();
	if (m_tmDPUFlashFinish->isActive())
		m_tmDPUFlashFinish->stop();
}

void Task10::timerEvent(QTimerEvent *event)
{
	int tmid = event->timerId();
	if (tmid == _tmid)
	{
		killTimer(_tmid);
		_tmid = 0;
		AutoSingle();
		_tmid_result = startTimer(100);
		return;

	}
	if (tmid == _tmid_result)
	{
		//���²��Խ��
		killTimer(_tmid_result);
		_tmid_result = 0;
		XLManager* pXL = XLManager::GetInstance();
		AutoTestData atd = (pXL->m_mapSINGLE_TEST[_datatype]).at(_lstindex);
		RandomAtd(atd);
		//�����Լ�������
		if (atd.id == 104)
		{
			SetSimularData(104, 36);
		}
		if (atd.id == 105)//�ܿذ汾
		{
			SetSimularData(105, 37);
		}
		if (atd.id == 106)//��׼�汾
		{
			SetSimularData(106, 38);
		}
		emit AddTaskItemResult(atd);

		_lstindex++;

		if (_lstindex >= pXL->m_mapSINGLE_TEST[_datatype].count())
		{
			emit UpdateToolTipSignal(QString::fromLocal8Bit("  "));
			killTimer(_tmid_result);
			_lstindex = 0;
			_stop = 1;
			return;
		}
		if (atd.id == 103) {
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
			if(bFailed)
			{
				MessageBoxDlg dlg3(QString::fromLocal8Bit("����ģ�����쳣������"));
				dlg3.exec();
				emit UpdateToolTipSignal(QString::fromLocal8Bit("����ģ�����쳣...."));
				StopCheck();
				emit StopSignleTestSignal();
				return;
			}
		label: {}
		}
		if (atd.id == 41)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x30ָ���ʸ����.��ʱ3�롣���Ժ�..."));
			m_tmTestUseTm->start(3 * 1000);//��ʱ3s
			return;
		}
		if (atd.id == 44)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x39ָ���ʸ����.��ʱ3�롣���Ժ�..."));
			m_tmTestUseTm->start(3 * 1000);//��ʱ3s
			return;
		}
		if (atd.id == 42)
		{
			//��δ����

			return;
		}
		if (atd.id == 101)
		{
			//m_tmTestUseTm->start(atd.tm * 1000);//��ʱ3s
			_JizhunTuState = 1;
			_JizhunTuRecord = 1;
			m_tmDPUFlashFinish->start(atd.tm * 1000 / (28 * 3));
			return;
		}
		atd = pXL->m_mapSINGLE_TEST[_datatype][_lstindex];
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

void Task10::UpdateTmLabel()
{
	m_tmTestUseTm->stop();
	_tmid = startTimer(50);
}
void Task10::UpdateDPFlash()
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
	QString str = lst[cnt % 3];
	cnt++;

	emit UpdateToolTipSignal(str);
}
void Task10::UpdateDPUFlashFinish()
{
	QString str;
	if (_JizhunTuState == 1)
		str = QString::fromLocal8Bit("��׼ͼװ��.�ܼ�¼��258����ǰ��¼��%1").arg(_JizhunTuRecord);
	//else
	//	str = QString::fromLocal8Bit("��׼ͼװ��.�ܼ�¼��164����ǰ��¼��%1").arg(_JizhunTuRecord);

	emit UpdateToolTipSignal(str);
	_JizhunTuRecord++;
	if (_JizhunTuState == 1 && _JizhunTuRecord > 258)
	{
		m_tmDPUFlashFinish->stop();
		_tmid = startTimer(20);
	}
	/*if (_JizhunTuState == 2 && _JizhunTuRecord > 164)
	{
		m_tmDPUFlashFinish->stop();
		_tmid_mult = startTimer(20);
	}*/
}
