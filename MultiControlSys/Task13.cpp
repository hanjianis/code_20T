#include "Task13.h"
#include "XLManager.h"
#include "MyMessageBox.h"
Task13::Task13(QObject *parent)
	: ITask(13, parent)
{
	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));
	m_tmDPUFlash = new QTimer();
	connect(m_tmDPUFlash, SIGNAL(timeout()), this, SLOT(UpdateDPFlash()));
	m_tmDPUFlashFinish = new QTimer();
	connect(m_tmDPUFlashFinish, SIGNAL(timeout()), this, SLOT(UpdateDPUFlashFinish()));
}

Task13::~Task13()
{
}

void Task13::start()
{
	//�������и���ʱ3s
	emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x8fָ���ʸ���֣���ʱ3�룬���Ժ�..."));
	m_tmTestUseTm->start(3 * 1000);
}

void Task13::StopCheck()
{
	ITask::StopCheck();
	if (m_tmTestUseTm->isActive())
		m_tmTestUseTm->stop();
	if (m_tmDPUFlash->isActive())
		m_tmDPUFlash->stop();
	if (m_tmDPUFlashFinish->isActive())
		m_tmDPUFlashFinish->stop();
}

void Task13::timerEvent(QTimerEvent *event)
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
		if (atd.id == 144)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x94ָ���ʸ���֣���ʱ3�룬���Ժ�..."));
			m_tmTestUseTm->start(3 * 1000);//��ʱ3s
			return;
		}
		if (atd.id == 146)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x96ָ���ʸ���֣���ʱ3�룬���Ժ�..."));
			m_tmTestUseTm->start(3 * 1000);//��ʱ3s
			return;
		}
		if (atd.id == 152)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x92ָ���ʸ���֣���ʱ3�룬���Ժ�..."));
			m_tmTestUseTm->start(3 * 1000);//��ʱ3s
			return;
		}
		if (atd.id == 156)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x91ָ���ʸ���֣���ʱ3�룬���Ժ�..."));
			m_tmTestUseTm->start(3 * 1000);//��ʱ3s
			return;
		}
		if (atd.id == 160)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x93ָ���ʸ���֣���ʱ3�룬���Ժ�..."));
			m_tmTestUseTm->start(3 * 1000);//��ʱ3s
			return;
		}
		if (atd.id == 160)
		{
			//��δ����
			emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ�0x93ָ���ʸ���֣���ʱ3�룬���Ժ�..."));
			m_tmTestUseTm->start(3 * 1000);//��ʱ3s
			return;
		}
		if (atd.id == 185)
		{
			MyMessageBox dlg(QString::fromLocal8Bit("������ʾ"), QString::fromLocal8Bit("��ѡ���Ƿ��Զ��ɿ����տ���?\r\nYes----�Զ�  No---�ֶ�"));
			dlg.exec();
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

void Task13::UpdateTmLabel()
{
	m_tmTestUseTm->stop();
	_tmid = startTimer(50);
}
void Task13::UpdateDPFlash()
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
void Task13::UpdateDPUFlashFinish()
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
