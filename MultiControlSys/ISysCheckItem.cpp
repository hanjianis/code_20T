#include "ISysCheckItem.h"
#include "MessageBoxDlg.h"
#include "MyToolTipDlg.h"
#include "SXZPDY_Manager.h"
#include "LDGDB_Manager.h"
#include "ZHDY_Manager.h"
#include "KJGXSMNQ_Manager.h"
#include "CK_Manager.h"
#include "DeviceOnlineManage.h"
ISysCheckItem::ISysCheckItem(int datatype,QObject *parent)
	: QObject(parent)
{
	pUDPServer = UDPServer::getInstance();
	pXL = XLManager::GetInstance();
	_datatype = datatype;
	_stop = false;
	connect(this, SIGNAL(UpdateCheckResult(int, int, float)), parent, SLOT(UpdateCheckResultCK(int, int, float)),Qt::DirectConnection);
    //界面添加表格数据
	connect(this, SIGNAL(AddTaskItem(AutoTestData&)), parent, SLOT(AddTableWidget(AutoTestData&)));

	connect(this, SIGNAL(AddTaskItemResult(AutoTestData&)), parent, SLOT(AddAutoTestResult(AutoTestData&)));
	m_tmCkOnline = new QTimer();
	connect(m_tmCkOnline, SIGNAL(timeout()), this, SLOT(CkOnlineTimeout()));   
/*
    connect(this, SIGNAL(sig_reminderinformation1(QString)), parent, SLOT(slot_reminderinformation1(QString)));
    connect(this, SIGNAL(sig_reminderinformation2(QString)), parent, SLOT(slot_reminderinformation2(QString)));
    connect(this, SIGNAL(sig_reminderinformation3(QString)), parent, SLOT(slot_reminderinformation3(QString)));
    connect(this, SIGNAL(sig_reminderinformation4(QString)), parent, SLOT(slot_reminderinformation4(QString)));
    connect(this, SIGNAL(sig_reminderinformation5(QString)), parent, SLOT(slot_reminderinformation5(QString)));
    connect(this, SIGNAL(sig_reminderinformation6(QString)), parent, SLOT(slot_reminderinformation6(QString)));
*/    
    connect(this, SIGNAL(sig_endTaskItem()), parent, SLOT(slot_endTaskItem()));
}

ISysCheckItem::~ISysCheckItem()
{
}
//开始测试
void ISysCheckItem::StartCheck()
{
	qDebug() << "ISysCheckItem::StartCheck";
    /*
    QString reminderinformation_1="测试开始";
    emit sig_reminderinformation1(reminderinformation_1);
    Sleep(1000);
    QString reminderinformation_2="继电器模块初始化中...";
    emit sig_reminderinformation2(reminderinformation_2);
    Sleep(100);
    QString reminderinformation_3="多路开关模块初始化中...";
    emit sig_reminderinformation3(reminderinformation_3);
    Sleep(100);
    QString reminderinformation_4="1553B模块初始化中...";
    emit sig_reminderinformation4(reminderinformation_4);
    Sleep(100);
    QString reminderinformation_5="IO模块初始化中...";
    emit sig_reminderinformation5(reminderinformation_5);
    Sleep(100);
    QString reminderinformation_6="数压表模块初始化中...";
    emit sig_reminderinformation6(reminderinformation_6);


    Sleep(5000);
    */
/*
	if (_datatype == 4)//综合电源 
	{
		ZHDY_Manager::getInstance()->RequestPowerControl(1, 1);
	}
	if (_datatype == 5)//三相中频电源
	{
		SXZPDY_Manager::getInstance()->RequestPowerStatus();
		Sleep(100);//等待100ms 等待udp数据返回 认为100ms必然返回
	}
*/
	_tmid = startTimer(50);
	_lstindex = 0;
}

//界面发送数据库数据
void ISysCheckItem::timerEvent(QTimerEvent *event)
{
	int tmid = event->timerId();

	if (tmid == _tmid)
	{
		killTimer(_tmid);
		_tmid = 0;
        if(systemclass==1)
        {
            if (_lstindex >= pXL->m_lstSystemselftest[_datatype].size())
            {
                return;
                _stop = true;
            }
            AutoTestData& atd = pXL->m_lstSystemselftest[_datatype][_lstindex];
            emit AddTaskItem(atd);
            if (atd.tm == 0)
                _tmid_result = startTimer(20);
            else
                _tmid_result = startTimer(atd.tm * 1000);

            /*
            if (_datatype == 4)//综合电源 挨个供电
            {
                ZHDY_Special();
            }
            if (_datatype == 7 && atd.id == 127)//雷达高度表
            {

                LDGDB_Manager::getInstance()->RequsetSelfCheck();
                m_tmCkOnline->start(1000);//开始检测雷达高度表是否开机成功
                //等待开机完成检测到心跳后 在开启	_tmid_result = startTimer(50);
                return;
            }
            */
        }

        if(systemclass==0)
        {
            if (_lstindex >= pXL->m_lstAirtightnessinspection[_datatype].size())
            {
                return;
                _stop = true;
            }
            AutoTestData& atd = pXL->m_lstAirtightnessinspection[_datatype][_lstindex];
            emit AddTaskItem(atd);

            if (atd.tm == 0)
               _tmid_result = startTimer(20);
            else
               _tmid_result = startTimer(atd.tm * 1000);


            /*
            if (_datatype == 4)//综合电源 挨个供电
            {
                ZHDY_Special();
            }

            if (_datatype == 7 && atd.id == 127)//雷达高度表
            {

                LDGDB_Manager::getInstance()->RequsetSelfCheck();
                m_tmCkOnline->start(1000);//开始检测雷达高度表是否开机成功
                //等待开机完成检测到心跳后 在开启	_tmid_result = startTimer(50);
                return;
            }
            */
        }
        //_tmid_result = startTimer(50);
		return;
		
	}
	if (tmid == _tmid_result)
	{
		killTimer(_tmid_result);
		_tmid_result = 0;
        if(systemclass==1)
        {
            AutoTestData& atd = pXL->m_lstSystemselftest[_datatype][_lstindex];
            emit AddTaskItemResult(atd);
            if(atd.id==180)
            {
                Sleep(2000);
                emit sig_endTaskItem();
            }
            /*
            if (atd.id == 1)
            {
                MessageBoxDlg dlg(QString::fromLocal8Bit("打开所有设备"));
                dlg.exec();
            }
            if (atd.id == 133)
            {
                KJGXSMNQ_Manager::getInstance()->RequsetSelfCheck();

                MyToolTipDlg dlg(QString::fromLocal8Bit("提示信息"),QString::fromLocal8Bit("景象模拟器是否正常？"));
                dlg.exec();
                _stop = true;
                return;
            }
            */
            _lstindex++;
            if (_lstindex >= pXL->m_lstSystemselftest[_datatype].size())
            {
                _stop = true;
                /*
                if (_datatype == 7)//雷达高度表
                {
                    //关闭程控管理器 第10路
                    //CK_Manager* ck = new CK_Manager(nullptr);
                //	ck->RequestPowerControl(10, 0);
                }
                if (_datatype == 4)//4:综合电源
                {
                    ZHDY_Manager::getInstance()->RequestPowerControl(1, 0);//1:综合电源第一路，0下电 1开电
                    Sleep(200);
                    for (unsigned char i=2;i<=8 ;i++)
                    {
                        ZHDY_Manager::getInstance()->RequestPowerControl(i, 0);
                        Sleep(200);
                    }
                }
                */
                return;
            }
        }

        if(systemclass==0)
        {
            AutoTestData& atd = pXL->m_lstAirtightnessinspection[_datatype][_lstindex];
            emit AddTaskItemResult(atd);
            if(atd.id==5)
            {
                Sleep(2000);
                emit sig_endTaskItem();
            }
            /*
            if (atd.id == 1)
            {
                MessageBoxDlg dlg(QString::fromLocal8Bit("打开所有设备"));
                dlg.exec();
            }
            if (atd.id == 188)
            {
                KJGXSMNQ_Manager::getInstance()->RequsetSelfCheck();

                MyToolTipDlg dlg(QString::fromLocal8Bit("提示信息"),QString::fromLocal8Bit("景象模拟器是否正常？"));
                dlg.exec();
                _stop = true;
                return;
            }
            */
            _lstindex++;
            if (_lstindex >= pXL->m_lstAirtightnessinspection[_datatype].size())
            {
                _stop = true;
                /*
                if (_datatype == 7)//雷达高度表
                {
                    //关闭程控管理器 第10路
                    //CK_Manager* ck = new CK_Manager(nullptr);
                //	ck->RequestPowerControl(10, 0);
                }
                if (_datatype == 4)//4:综合电源
                {
                    ZHDY_Manager::getInstance()->RequestPowerControl(1, 0);//1:综合电源第一路，0下电 1开电
                    Sleep(200);
                    for (unsigned char i=2;i<=8 ;i++)
                    {
                        ZHDY_Manager::getInstance()->RequestPowerControl(i, 0);
                        Sleep(200);
                    }
                }
                */
                return;
            }
        }

		_tmid = startTimer(50);
		return;
	}
}

bool ISysCheckItem::is_stop()
{
	return _stop;
}

void ISysCheckItem::StopCheck()
{
	killTimer(_tmid);
	_tmid = 0;
	killTimer(_tmid_result);
	_tmid_result = 0;
	_stop = true;
}

void ISysCheckItem::ZHDY_Special()
{
	//不知道为什么界面上 只有 1 2 3 4 5 6 8路
	AutoTestData& atd = pXL->m_lstMNLTDJC[_datatype][_lstindex];
	if (_lstindex == 6)
		//根据_lstindex 判断是第几路 index+1 
	{
		//第7 8 两路都上
		ZHDY_Manager::getInstance()->RequestPowerControl(_lstindex + 1, 1);//上电 
		Sleep(200);
		ZHDY_Manager::getInstance()->RequestPowerControl(_lstindex + 2, 1);//上电 
	}
	else
		ZHDY_Manager::getInstance()->RequestPowerControl(_lstindex + 1, 1);//上电 
	Sleep(200);//sleep以后 查询电源状态
	ZHDY_Manager::getInstance()->RequestPowerStatus();
}

void ISysCheckItem::CkOnlineTimeout()
{
	int flag = (DeviceOnlineManage::getInstance()->m_nDeviceOnlineFlag);
	bool bb = flag & 0x100;
	if((flag & 0x100) )//如果在线 
	{
		LDGDB_Manager::getInstance()->RequestPowerControl(1000, 80);//设置
		m_tmCkOnline->stop();//停止定时器
		_tmid_result = startTimer(100);

	}
}
