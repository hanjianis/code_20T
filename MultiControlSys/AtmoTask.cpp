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

   // PLCManager::getInstance()->SetDQ20TStart( );

}

AtmoTask::~AtmoTask()
{
}

void AtmoTask::start()
{
	//打开综合电源对话框
	MessageBoxDlg dlg(QString::fromLocal8Bit("打开E23-20T大气数据测控仪"));
	dlg.exec();
	emit UpdateToolTipSignal(QString::fromLocal8Bit("正在打开大气数据测控仪,请稍后..."));
	/*
	if (PLCManager::getInstance()->ConnectPLC() == false)//PLC连接失败 会卡在打开大气仪界面 目前没有好的解决方式 不知道为什么
	{
		MessageBoxDlg dlg3(QString::fromLocal8Bit("打开大气数据测控仪失败！请检查电源"));
		dlg3.exec();
		emit UpdateToolTipSignal(QString::fromLocal8Bit("打开大气数据测控仪失败...."));
		StopCheck();
		return;
    }
	PLCManager::getInstance()->SetDQ20TStart();
	emit UpdateToolTipSignal(QString::fromLocal8Bit("打开大气数据测控仪成功...."));
	MessageBoxDlg dlg2(QString::fromLocal8Bit("待自检完成后，完成放气"));
	dlg2.exec();
	//当index=28时，有个输入温度的dialog 16：40
	//index=29时 有个提示 是否进行气密性检查 16:18

	ITask::start();
	*/
	
    if (PLCManager::getInstance()->ConnectPLC() == true)
    {
        PLCManager::getInstance()->SetDQ20TStart();
 //       Sleep(5000);
//        if(PLCManager::getInstance()->ReadDQ20T())
//        {
            emit UpdateToolTipSignal(QString::fromLocal8Bit("打开大气数据测控仪成功...."));
            MessageBoxDlg dlg2(QString::fromLocal8Bit("待自检完成后，完成放气"));
            dlg2.exec();
            //当index=28时，有个输入温度的dialog 16：40
            //index=29时 有个提示 是否进行气密性检查 16:18

            ITask::start();
//        }else{
//            MessageBoxDlg dlg3(QString::fromLocal8Bit("打开大气数据测控仪失败！请检查电源"));
//            dlg3.exec();
//            emit UpdateToolTipSignal(QString::fromLocal8Bit("打开大气数据测控仪失败...."));
//            StopCheck();
//            return;
//        }
    }else{
        MessageBoxDlg dlg3(QString::fromLocal8Bit("打开大气数据测控仪失败！请检查电源"));
        dlg3.exec();
        emit UpdateToolTipSignal(QString::fromLocal8Bit("打开大气数据测控仪失败...."));
        StopCheck();
        return;
    }
	
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
		//更新测试结果
		killTimer(_tmid_result);
		_tmid_result = 0;
		XLManager* pXL = XLManager::GetInstance();
		AutoTestData& atd = (pXL->m_mapSINGLE_TEST[_datatype])[_lstindex];
	
		RandomAtd(atd);
		emit AddTaskItemResult(atd);
		//更新静压 总压1 总压2
		if (atd.id == 32 || atd.id == 35 || atd.id == 38)
		{
			SetSimularData(32, 26);//第一个参数没有意义
		}
		
		if (atd.id == 33 || atd.id == 36 || atd.id == 39)
		{
			SetSimularData(32, 27);//第一个参数没有意义
		}
		if (atd.id == 34 || atd.id == 37 || atd.id == 40)
		{
			SetSimularData(32, 28);//第一个参数没有意义
		}
		//设置静压积分 从视频里得到的
		if (atd.id == 34)//第一次
		{
			SetSimularData(QString("45873.8"), 29);
		}
		if (atd.id == 37)//第二次
		{
			SetSimularData(QString("3.5"), 29);
		}
		if (atd.id == 40)//第三次
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
			MyToolTipDlg dlg(QString::fromLocal8Bit("选择提示"),QString::fromLocal8Bit("是否进行气密性检查？"));
			dlg.exec();
			PLCManager::getInstance()->SetSingleStart();
			m_tmPLC->start(200);
			/*emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待气压泄露，延时60秒，请稍候..."));
			m_tmTestUseTm->start(60 * 1000);*/
			return;
		}
		if (atd.id == 31)
		{
			emit UpdateToolTipSignal(QString::fromLocal8Bit("正在压力设置，请稍候..."));
			m_tmTestUseTm->start(20 * 1000);
			return;
		}
		if (atd.id == 34 || atd.id == 37)
		{
			//单纯延时
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
		emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待气压泄露，延时60秒，请稍候..."));
		m_tmTestUseTm->start(60 * 1000);
	}
	if (PLCManager::getInstance()->Read1MinUnValid() == true)
	{
		m_tmPLC->stop();
		MessageBoxDlg dlg2(QString::fromLocal8Bit("气压漏气"));
		dlg2.exec();
		PLCManager::getInstance()->SetSingleStop();
		PLCManager::getInstance()->DisConnectPLC();
		emit DQ_failed();
		//m_tmPLC->stop();
		//emit UpdateToolTipSignal(QString::fromLocal8Bit("正在等待气压泄露，延时60秒，请稍候..."));
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
			AutoTestData* atd = &((pXL->m_mapSINGLE_TEST[_datatype])[5]);//100kpa静压
			atd->val = QString("%1").arg(fval);
			fval = PLCManager::getInstance()->ReadZongYa();
			AutoTestData* atd2 = &((pXL->m_mapSINGLE_TEST[_datatype])[6]);//100kpa动压
			atd2->val = QString("%1").arg(fval);
			AutoTestData* atd3 = &((pXL->m_mapSINGLE_TEST[_datatype])[7]);//100kpa动压
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
			AutoTestData* atd = &((pXL->m_mapSINGLE_TEST[_datatype])[8]);//100kpa静压
			atd->val = QString("%1").arg(fval);
			fval = PLCManager::getInstance()->ReadZongYa();
			AutoTestData* atd2 = &((pXL->m_mapSINGLE_TEST[_datatype])[9]);//100kpa动压
			atd2->val = QString("%1").arg(fval);
			AutoTestData* atd3 = &((pXL->m_mapSINGLE_TEST[_datatype])[10]);//100kpa动压
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
			AutoTestData* atd = &((pXL->m_mapSINGLE_TEST[_datatype])[11]);//100kpa静压
			atd->val = QString("%1").arg(fval);
			fval = PLCManager::getInstance()->ReadZongYa();
			AutoTestData* atd2 = &((pXL->m_mapSINGLE_TEST[_datatype])[12]);//100kpa动压
			atd2->val = QString("%1").arg(fval);
			AutoTestData* atd3 = &((pXL->m_mapSINGLE_TEST[_datatype])[13]);//100kpa动压
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
			_stop = true;//结束
			read20Already = 1;
		}
}
