#include "AtmoTask.h"
#include<QDebug>
#include "XLManager.h"
#include "MessageBoxDlg.h"
#include "InputTemperatureDlg.h"
#include "MyToolTipDlg.h"
#include "DeviceMgr/PLCManager.h"
AtmoTask::AtmoTask(QObject *parent)
	: ITask(4,parent)
{
	_datatype = 4;
	m_tmTestUseTm = new QTimer();
	connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(UpdateTmLabel()));
	m_tmPLC = new QTimer();
	connect(m_tmPLC, SIGNAL(timeout()), this, SLOT(PLCTmSlot()));
	m_tmPLCRead = new QTimer();
	connect(m_tmPLCRead, SIGNAL(timeout()), this, SLOT(PLCReadDataSlot()));


	connect(this, SIGNAL(DQ_failed()), parent, SLOT(DQ_Failed()));
}

AtmoTask::~AtmoTask()
{
}

void AtmoTask::start()
{
	//���ۺϵ�Դ�Ի���
	MessageBoxDlg dlg(QString::fromLocal8Bit("��E23-20T�������ݲ����"));
	dlg.exec();
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
	MessageBoxDlg dlg2(QString::fromLocal8Bit("���Լ���ɺ���ɷ���"));
	dlg2.exec();
	//��index=28ʱ���и������¶ȵ�dialog 16��40
	//index=29ʱ �и���ʾ �Ƿ���������Լ�� 16:18

	ITask::start();
}

void AtmoTask::StopCheck()
{
	ITask::StopCheck();
	if (m_tmTestUseTm->isActive())
		m_tmTestUseTm->stop();
	if (m_tmPLC->isActive())
		m_tmPLC->stop();
	if (m_tmPLCRead->isActive())
		m_tmPLCRead->stop();

}

void AtmoTask::timerEvent(QTimerEvent *event)
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
		AutoTestData& atd = (pXL->m_mapSINGLE_TEST[_datatype])[_lstindex];
	
		RandomAtd(atd);
		emit AddTaskItemResult(atd);
		//���¾�ѹ ��ѹ1 ��ѹ2
		if (atd.id == 32 || atd.id == 35 || atd.id == 38)
		{
			SetSimularData(32, 26);//��һ������û������
		}
		
		if (atd.id == 33 || atd.id == 36 || atd.id == 39)
		{
			SetSimularData(32, 27);//��һ������û������
		}
		if (atd.id == 34 || atd.id == 37 || atd.id == 40)
		{
			SetSimularData(32, 28);//��һ������û������
		}
		//���þ�ѹ���� ����Ƶ��õ���
		if (atd.id == 34)//��һ��
		{
			SetSimularData(QString("45873.8"), 29);
		}
		if (atd.id == 37)//�ڶ���
		{
			SetSimularData(QString("3.5"), 29);
		}
		if (atd.id == 40)//������
		{
			SetSimularData(QString("45873.8"), 29);
		}
		_lstindex++;

		if (_lstindex >= pXL->m_mapSINGLE_TEST[_datatype].count())
		{
			emit UpdateToolTipSignal(QString::fromLocal8Bit("  "));
			killTimer(_tmid_result);
			_lstindex = 0;
			_stop = 1;
			return;
		}
		if (atd.id == 28)
		{
			InputTemperatureDlg dlg;
			dlg.exec();
			
		}
		if (atd.id == 29)
		{
			MyToolTipDlg dlg(QString::fromLocal8Bit("ѡ����ʾ"),QString::fromLocal8Bit("�Ƿ���������Լ�飿"));
			dlg.exec();
			PLCManager::getInstance()->SetSingleStart();
			m_tmPLC->start(200);
			/*emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ���ѹй¶����ʱ60�룬���Ժ�..."));
			m_tmTestUseTm->start(60 * 1000);*/
			return;
		}
		if (atd.id == 31)
		{
			emit UpdateToolTipSignal(QString::fromLocal8Bit("����ѹ�����ã����Ժ�..."));
			m_tmTestUseTm->start(20 * 1000);
			return;
		}
		if (atd.id == 34 || atd.id == 37)
		{
			//������ʱ
			emit UpdateToolTipSignal(QString::fromLocal8Bit("  "));
			m_tmTestUseTm->start(20 * 1000);
			return;
		}
		_tmid = startTimer(50);
		return;
	}
}

void AtmoTask::UpdateTmLabel()
{
	m_tmTestUseTm->stop();
	m_tmPLCRead->start(100);
}

void AtmoTask::PLCTmSlot()
{
	//
	if (PLCManager::getInstance()->Read1MinValid() == true)
	{
		m_tmPLC->stop();
		AutoSingle();
		AutoSingleResult();
		_lstindex++;
		AutoSingle();
		AutoSingleResult();
		_lstindex++;
		emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ���ѹй¶����ʱ60�룬���Ժ�..."));
		m_tmTestUseTm->start(60 * 1000);
	}
	if (PLCManager::getInstance()->Read1MinUnValid() == true)
	{
		m_tmPLC->stop();
		MessageBoxDlg dlg2(QString::fromLocal8Bit("��ѹ©��"));
		dlg2.exec();
		PLCManager::getInstance()->SetSingleStop();
		PLCManager::getInstance()->DisConnectPLC();
		emit DQ_failed();
		//m_tmPLC->stop();
		//emit UpdateToolTipSignal(QString::fromLocal8Bit("���ڵȴ���ѹй¶����ʱ60�룬���Ժ�..."));
		//m_tmTestUseTm->start(60 * 1000);
	}
	
}

void AtmoTask::PLCReadDataSlot()
{
		qDebug() << PLCManager::getInstance()->Read100KPaIsEnd();
		if ( read100Already==0 && PLCManager::getInstance()->Read100KPaIsEnd() == true)
		{
			float fval = PLCManager::getInstance()->ReadJingYa();
			XLManager* pXL = XLManager::GetInstance();
			AutoTestData* atd = &((pXL->m_mapSINGLE_TEST[_datatype])[5]);//100kpa��ѹ
			atd->val = QString("%1").arg(fval);
			fval = PLCManager::getInstance()->ReadZongYa();
			AutoTestData* atd2 = &((pXL->m_mapSINGLE_TEST[_datatype])[6]);//100kpa��ѹ
			atd2->val = QString("%1").arg(fval);
			AutoTestData* atd3 = &((pXL->m_mapSINGLE_TEST[_datatype])[7]);//100kpa��ѹ
			atd3->val = QString("%1").arg(fval);
			AutoSingle();
			AutoSingleResult();
			_lstindex++;
			AutoSingle();
			AutoSingleResult();
			_lstindex++;
			AutoSingle();
			AutoSingleResult();
			_lstindex++;

			read100Already = 1;
		}
		if (read60Already == 0 && PLCManager::getInstance()->Read60KPaIsEnd() == true)
		{
			float fval = PLCManager::getInstance()->ReadJingYa();
			XLManager* pXL = XLManager::GetInstance();
			AutoTestData* atd = &((pXL->m_mapSINGLE_TEST[_datatype])[8]);//100kpa��ѹ
			atd->val = QString("%1").arg(fval);
			fval = PLCManager::getInstance()->ReadZongYa();
			AutoTestData* atd2 = &((pXL->m_mapSINGLE_TEST[_datatype])[9]);//100kpa��ѹ
			atd2->val = QString("%1").arg(fval);
			AutoTestData* atd3 = &((pXL->m_mapSINGLE_TEST[_datatype])[10]);//100kpa��ѹ
			atd3->val = QString("%1").arg(fval);
			AutoSingle();
			AutoSingleResult();
			_lstindex++;
			AutoSingle();
			AutoSingleResult();
			_lstindex++;
			AutoSingle();
			AutoSingleResult();
			_lstindex++;

			read60Already = 1;
		}
		if (read20Already == 0 &&  PLCManager::getInstance()->Read20KPaIsEnd() == true)
		{
			float fval = PLCManager::getInstance()->ReadJingYa();
			XLManager* pXL = XLManager::GetInstance();
			AutoTestData* atd = &((pXL->m_mapSINGLE_TEST[_datatype])[11]);//100kpa��ѹ
			atd->val = QString("%1").arg(fval);
			fval = PLCManager::getInstance()->ReadZongYa();
			AutoTestData* atd2 = &((pXL->m_mapSINGLE_TEST[_datatype])[12]);//100kpa��ѹ
			atd2->val = QString("%1").arg(fval);
			AutoTestData* atd3 = &((pXL->m_mapSINGLE_TEST[_datatype])[13]);//100kpa��ѹ
			atd3->val = QString("%1").arg(fval);
			AutoSingle();
			AutoSingleResult();
			_lstindex++;
			AutoSingle();
			AutoSingleResult();
			_lstindex++;
			AutoSingle();
			AutoSingleResult();
			_lstindex++;
			m_tmPLCRead->stop();
			PLCManager::getInstance()->SetSingleStop();
			PLCManager::getInstance()->DisConnectPLC();
			//_tmid = startTimer(50);
			_stop = true;//����
			read20Already = 1;
		}
}
