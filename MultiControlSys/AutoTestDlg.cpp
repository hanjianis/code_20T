#include "AutoTestDlg.h"
#include "Packet.h"
#include "XLManager.h"

#include <QDesktopWidget>
#include "AtmoTask.h"
#include "PowerTask.h"
#include "LogMgr.h"
#include <QDebug>
#include "DeviceMgr/CK_Manager.h"
#include "DeviceMgr/HecDataManager.h"
#include "InsConfigDlg.h"
#include "MessageBoxDlg.h"
#include "MyToolTipDlg.h"
#include "GlobalManager.h"
#include "DeviceMgr/PLCManager.h"
#include "DeviceMgr/SPQ_Manager.h"
//测试结果 列序号
#define COLUMN_VAL  3
#define COLUMN_UNIT  4
#define COLUMN_CONTENT  5
AutoTestDlg::AutoTestDlg(int nType,QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    pXL = XLManager::GetInstance();
    _tcpClient = TCPClient::GetInstance();
    _udpServer = UDPServer::getInstance();


    excelOperate = new ExcelOperate(this);
    _type = nType;
    _tmid_auto = 0;
    _tmid = 0;
    ui.comboBox->clear();
    ui.comboBox_3->clear();
    ui.comboBox_3->addItem(QString::fromLocal8Bit("所有项目"));
    QStringList lst;
    lst << QString::fromLocal8Bit("选择测试单元");
    //请求一下适配器连接状态 在点击开始按钮的时候 判断数据
    SPQ_Manager::getInstance()->RequestPowerControl();

    if (_type == ATT_SYS)
    {

        ui.lineEdit->setText(QString::fromLocal8Bit("系统自检状态"));

        lst << QString::fromLocal8Bit("系统自检");
        ui.comboBox->addItems(lst);
        lst.clear();
        lst << QString::fromLocal8Bit("连续测试") << QString::fromLocal8Bit("系统自检");
        //ui.listWidget->setVisible(false);
        ui.comboBox_3->addItems(XLManager::GetInstance()->m_lstSelfCheckItems);
    }
    else
    {
        ui.lineEdit->setText(QString::fromLocal8Bit("K/AKD20"));
        lst << QString::fromLocal8Bit("单项测试") << QString::fromLocal8Bit("惯导测试") << QString::fromLocal8Bit("综合测试") << QString::fromLocal8Bit("挂飞训练弹") << QString::fromLocal8Bit("测试训练弹") << QString::fromLocal8Bit("总检查") << QString::fromLocal8Bit("舵机复位");
        ui.comboBox->addItems(lst);
        //ui.comboBox_3->addItems(XLManager::GetInstance()->m_lstAutoTestItems);
        ui.comboBox_3->addItem(QString::fromLocal8Bit("所有项目"));
        m_at = new AutoTestWidget(ui.listItems);
        ui.verticalLayout_16->addWidget(m_at);
    }

    m_itemsdlg = new TestItemsDlg( this);
    GlobalManager::getInstance()->m_at = m_at;//供自动测试 -》单项测试用
    ui.comboBox_2->setDisabled(true);
    ui.comboBox_3->setDisabled(true);

    ui.tableWidget->setRowCount(0);
    ui.tableWidget->verticalHeader()->hide();
    ui.tableWidget->setColumnWidth(0, 80);
    ui.tableWidget->setColumnWidth(1, 300);
    ui.tableWidget->setColumnWidth(2, 140);
    ui.tableWidget->setColumnWidth(3, 140);
    ui.tableWidget->setColumnWidth(4, 130);
    ui.tableWidget->setColumnWidth(5, 130);
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //填充表格
    ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择模式

    on_timeout();
    m_tmTimer = new QTimer();
    connect(m_tmTimer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    m_tmTimer->start(1000);

    m_tmTestUseTm = new QTimer();
    connect(m_tmTestUseTm, SIGNAL(timeout()), this, SLOT(SetTestUseTm()));


    setWindowFlags(Qt::FramelessWindowHint);
    resize(WIDTH, HEIGHT);
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move(0, 0);
    //connect(CK_Manager::getInstance(), SIGNAL(UpdateCheckResult(int,float)), this, SLOT(UpdateCheckResultCK(int, float)));
//	CreateExcel();
}

AutoTestDlg::~AutoTestDlg()
{
}

void AutoTestDlg::MNLTDJC()
{
    ISysCheckItem* task1 = _lstTaskDataType.front();

    if (task1 != nullptr)
    {
        if (task1->is_stop())//已经结束 换下一个
        {
            _lstTaskDataType.pop_front();
            if (_lstTaskDataType.size() > 0&&end_test==0)
            {
                ISysCheckItem* task2 = _lstTaskDataType.front();
                task2->StartCheck();
            }
            else
            {
                killTimer(_tmid);
                ui.btnstart->setDisabled(false);
                ui.toolButton_2->setDisabled(false);
                ui.quit->setDisabled(false);
                killTimer(_tmid);
                m_tmTestUseTm->stop();
                int usetm = (GetTickCount() - _startTickCount) / 1000;
                excelOperate->SaveAs(usetm);
                _tcpClient->SendMsgID(eMsg_T_OnTestOver);
                ui.quit->setEnabled(true);

            }
        }
    }
    //AutoTestData atd = pXL->m_lstMNLTDJC[_datatype].at(_lstindex);
    //AddTableWidget(atd);

    //_lstindex++;
    ////发送UDP 请求
    //if (atd.type == AUTO_TYPE_UDP)
    //{
    //	//请求规则
    //	if (_datatype == 3)//程控管理器
    //	{

    //	}
    //}
    //if (_lstindex >= pXL->m_lstMNLTDJC[_datatype].count())
    //{
    //	//换下一个
    //	_lstindex = 0;
    //	_lstTaskDataType.pop_front();
    //	if (_lstTaskDataType.size() > 0)//还有
    //	{
    //		_datatype = _lstTaskDataType.front();
    //	}
    //	else
    //	{
    //		ui.btnstart->setDisabled(false);
    //		ui.toolButton_2->setDisabled(false);
    //		ui.quit->setDisabled(false);
    //		killTimer(_tmid);
    //		int usetm = (GetTickCount() - _startTickCount) / 1000;
    //		excelOperate->SaveAs(usetm);
    //	}
    //	return;
    //}
    //atd = pXL->m_lstMNLTDJC[_datatype].at(_lstindex);
    //ui.label_2->setText(atd.tip);
}



void AutoTestDlg::CreateExcel()
{
    int unit = ui.comboBox->currentIndex();
    excelOperate->CreateExcel(_type,unit);
    excelOperate->_FileInfo.unitType = _type;
    excelOperate->_FileInfo.unitName = ui.comboBox->currentText();
    excelOperate->_FileInfo.modeType = ui.comboBox_2->currentIndex();
    excelOperate->_FileInfo.modeName = ui.comboBox_2->currentText();
}

void AutoTestDlg::SetTestUseTm()
{
    int usetm = (GetTickCount() - _startTickCount)/1000;

    //转化成00:00:00格式
    QString str = QString("%1:%2:%3").arg(usetm/3600, 2, 10, QLatin1Char('0'))
        .arg((usetm % 3600)/60, 2, 10, QLatin1Char('0'))
        .arg(usetm % 60, 2, 10, QLatin1Char('0'));
    ui.lineEdit_2->setText(str);
}

void AutoTestDlg::AddTableWidget(AutoTestData& atd)
{
    int row = ui.tableWidget->rowCount();
    ui.tableWidget->insertRow(row);
    int column = 0;
    QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row+1));
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget->setItem(row, column++, item);

    item = new QTableWidgetItem(QString("%1").arg(atd.name));
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget->setItem(row, column++, item);

    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item = new QTableWidgetItem(QString("%1").arg(atd.standardname));
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget->setItem(row, column++, item);


    item = new QTableWidgetItem(QString("%1").arg(atd.unit));
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget->setItem(row, COLUMN_UNIT, item);


    ui.tableWidget->scrollToBottom();
    if(atd.tip.isEmpty() == false)
        ui.label_2->setText(atd.tip);
    return;



}

void AutoTestDlg::AddAutoTestResult(AutoTestData& atd)
{

    int row = ui.tableWidget->rowCount()-1;
    QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(atd.val));
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget->setItem(row, COLUMN_VAL, item);
    //更新结果
    if (atd.content == 1)
    {
        item = new QTableWidgetItem(QString::fromLocal8Bit("√"));
        _correct_count++;
    }
    else if (atd.content == 0)
    {
        item = new QTableWidgetItem(QString::fromLocal8Bit("×"));
        _error_count++;
    }
    else
    {
        item = new QTableWidgetItem(QString::fromLocal8Bit("//"));
        _correct_count++;
    }
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget->setItem(row, COLUMN_CONTENT, item);

    if (atd.tip.isEmpty() == false)
        ui.label_2->setText(atd.tip);

    excelOperate->InsertSheet(row + 1, atd);
    //ui.tableWidget->scrollToBottom();
    updateResult();//更新正确 错误数量
}

//更新正确 错误数量
void AutoTestDlg::updateResult()
{
    QString str = QString("%1").arg(_correct_count);
    ui.lineEdit_3->setText(str);
    str = QString("%4").arg(_error_count);
    ui.lineEdit_4->setText(str);
}

void AutoTestDlg::timerEvent(QTimerEvent *event)
{
    int tmid = event->timerId();
    if (tmid == _tmid)
    {

        MNLTDJC();
        return;
    }
    if (_tmid_auto == tmid)
    {
        ITask* task1 = pXL->m_lstTasks.front();
        if (task1 != nullptr)
        {

            if (task1->is_stop())//已经结束 换下一个
            {
                pXL->m_lstTasks.pop_front();
                if (pXL->m_lstTasks.size() > 0)
                {
                    ITask* task2 = pXL->m_lstTasks.front();
                    task2->start();
                }
                else
                {
                    killTimer(_tmid_auto);
                    _tmid_auto = 0;
                    m_tmTestUseTm->stop();
                    UpdateToolTip(QString::fromLocal8Bit("单项测试流程结束"));
                    int usetm = (GetTickCount() - _startTickCount) / 1000;
                    excelOperate->SaveAs(usetm);
                    _tcpClient->SendMsgID(eMsg_T_OnTestOver);
                    ui.quit->setEnabled(true);
                }
            }
        }
        //AutoSingle();
    }
    /*
    //综合
    if (_tmid_mult == tmid)
    {
        AddTableWidget(pXL->m_mapMULT_TEST[_datatype][_lstindex]);

        _tmid_mult_result = startTimer(100);
        killTimer(_tmid_mult);
        _tmid_mult = 0;

    }
    if (_tmid_mult_result == tmid)
    {
        killTimer(_tmid_mult_result);
        _tmid_mult_result = 0;
        AddAutoTestResult(pXL->m_mapMULT_TEST[_datatype][_lstindex++]);
        _tmid_mult = startTimer(20);
        if (_lstindex >= pXL->m_mapMULT_TEST[_datatype].size())
        {

            //停止
            killTimer(_tmid_mult);
            _tmid_ins = 0;
            m_tmTestUseTm->stop();
            int usetm = (GetTickCount() - _startTickCount) / 1000;
            excelOperate->SaveAs(usetm);

            _tcpClient->SendMsgID(eMsg_T_OnTestOver);
        }
    }
    */
}
void AutoTestDlg::DQ_Failed()//have not tested
{
    killTimer(_tmid_auto);
    _tmid_auto = 0;
    m_tmTestUseTm->stop();
    UpdateToolTip(QString::fromLocal8Bit("单项测试流程结束"));
    int usetm = (GetTickCount() - _startTickCount) / 1000;
    excelOperate->SaveAs(usetm);
    _tcpClient->SendMsgID(eMsg_T_OnTestOver);
    ui.quit->setEnabled(true);
}
void AutoTestDlg::on_quit_clicked()
{
    close();
}

void AutoTestDlg::on_btnstart_clicked()
{
    bool bStartSuccess = false;//是否可以开始执行
    _startTickCount = GetTickCount();
    _correct_count = 0;
    _error_count = 0;

    if (_type == ATT_SYS)
    {
        //先判断适配器是否正常
        if (SPQ_Manager::getInstance()->CheckLineConnected() == false)
        {
            MessageBoxDlg dlg(QString::fromLocal8Bit("请检查电缆是否连接正确"));
            dlg.exec();
            return;
        }
        _tcpClient->SendMsgID(eMsg_T_OnSelfCheck);
        _datatype = ui.comboBox_3->currentIndex();
        ui.btnstart->setDisabled(true);
        ui.toolButton_2->setEnabled(true);
        ui.quit->setDisabled(true);
        _lstTaskDataType.clear();

        ui.tableWidget->setRowCount(0);
        if (_datatype == 0)//所有项目
        {
            for (int i = 1; i <= 9; i++)
            {
                if(i == 3)
                    _lstTaskDataType.push_back(new CK_Manager(this));
                else
                    _lstTaskDataType.push_back(new ISysCheckItem(i, this));
            }
        }
        if (_datatype == 3)
            _lstTaskDataType.push_back(new CK_Manager(this));
        else{

            _lstTaskDataType.push_back(new ISysCheckItem(_datatype, this));
        }
        _lstindex = 0;
        CreateExcel();
        _tmid = startTimer(50);
        ISysCheckItem* task1 = _lstTaskDataType.front();
        task1->StartCheck();
        bStartSuccess = true;

    }
    if (_type == ATT_AUTO)
    {
        int unit = ui.comboBox->currentIndex();
        if (unit > MULT_TEST)
            return;

        if (unit == SIGNLE_TEST)//单项测试
        {
            _tcpClient->SendMsgID(eMsg_T_OnItemTest);
            ui.tableWidget->setRowCount(0);

            m_itemsdlg->exec();
            m_at->UpdateInsLables(1, 40);
            //ITask* task = new PowerTask(this);
            //m_lstTasks.push_back(task);
            CreateExcel();
            ITask* task1 = pXL->m_lstTasks.front();
            task1->start();
            _tmid_auto = startTimer(50);
            bStartSuccess = true;
        }
        if (unit == INS_TEST)// 惯导测试
        {
            _tcpClient->SendMsgID(eMsg_T_OnINS);
            _datatype = 1;
            ui.tableWidget->setRowCount(0);
            _lstindex = 0;
            CreateExcel();
            //ADD
            if (_insTest == nullptr)
            {
                _insTest = new INSTestOBJ(m_at, this);

            }
            _insTest->start();
            bStartSuccess = true;
        }
        if (unit == MULT_TEST)//综合测试
        {
            _tcpClient->SendMsgID(eMsg_T_OnComprehensiveTest);
            _datatype = 1;
            ui.tableWidget->setRowCount(0);
            _lstindex = 0;
            CreateExcel();
            //_tmid_mult = startTimer(50);
            if (_multTest == nullptr)
                _multTest = new MultTestOBJ(m_at, this);
            _multTest->start();
            bStartSuccess = true;
        }

    }
    if (bStartSuccess == true)
    {
        _tcpClient->SendMsgID(eMsg_T_OnTestStart);
        ui.quit->setEnabled(false);
        m_tmTestUseTm->start();
    }
}

void AutoTestDlg::on_toolButton_2_clicked()
{
    if (_type == ATT_SYS)//系统自检暂停
    {

        killTimer(_tmid);
        _tmid = 0;
        //各个未完成任务 都设置为已完成
        while (_lstTaskDataType.size() > 0)
        {
            ISysCheckItem* task1 = _lstTaskDataType.front();
            if (task1 != nullptr)
            {
                task1->StopCheck();
                task1->_stop = true;
                _lstTaskDataType.pop_front();
            }
        }

    }
    if (_type == ATT_AUTO)
    {
        int unit = ui.comboBox->currentIndex();
        if (unit > MULT_TEST)
            return;
        if (unit == SIGNLE_TEST)//单项测试暂停
        {

            killTimer(_tmid_auto);
            _tmid_auto = 0;

            while (pXL->m_lstTasks.size() > 0)
            {
                ITask* task1 = pXL->m_lstTasks.front();  //获取list中的第一个元素变量
                if (task1 != nullptr)
                {
                    task1->StopCheck();
                }
                pXL->m_lstTasks.pop_front();
            }
            UpdateToolTip(QString::fromLocal8Bit("单项测试流程结束"));
        }
        if (unit == INS_TEST)//惯导测试暂停
        {
            _insTest->StopCheck();
            return;
        }
        if (unit == MULT_TEST)//惯导测试暂停
        {
            _multTest->StopCheck();
            return;
        }
    }

    m_tmTestUseTm->stop();
    int usetm = (GetTickCount() - _startTickCount) / 1000;
    excelOperate->SaveAs(usetm);
    _tcpClient->SendMsgID(eMsg_T_OnTestOver);
    ui.btnstart->setDisabled(false);
    ui.toolButton_2->setDisabled(false);
    ui.quit->setEnabled(true);
    //GlobalManager::getInstance()->ShowButtonTip(this);
}

void AutoTestDlg::on_comboBox_currentIndexChanged(int index)
{
    if (index > 0) {
        ui.comboBox_2->setDisabled(false);
    }
}

void AutoTestDlg::on_comboBox_2_currentIndexChanged(int index)
{
    if (index > 0)
    {
        ui.comboBox_3->setDisabled(false);
    }
    else{
        ui.comboBox_3->setCurrentIndex(0);
        ui.comboBox_3->setDisabled(true);
        }
}

void AutoTestDlg::UpdateToolTip(QString str)
{
    if(str.isEmpty() == false)
        ui.label_2->setText(str);
}

void AutoTestDlg::RecvStopInsSlot()
{
    m_tmTestUseTm->stop();
    int usetm = (GetTickCount() - _startTickCount) / 1000;
    excelOperate->SaveAs(usetm);
    _tcpClient->SendMsgID(eMsg_T_OnTestOver);
    ui.quit->setEnabled(true);
}

void AutoTestDlg::RecvStopMultiSlot()
{
    UpdateToolTip(QString::fromLocal8Bit("综合测试流程结束"));
    m_tmTestUseTm->stop();
    int usetm = (GetTickCount() - _startTickCount) / 1000;
    excelOperate->SaveAs(usetm);
    _tcpClient->SendMsgID(eMsg_T_OnTestOver);
    ui.quit->setEnabled(true);
}
//未找到
void AutoTestDlg::on_testBtn_clicked()
{
    PLCManager::getInstance()->SetSingleStart();    
}

void AutoTestDlg::on_testBtn2_clicked()
{
    PLCManager::getInstance()->SetSingleStop();
}

void AutoTestDlg::on_testBtn3_clicked()
{
    PLCManager::getInstance()->SetMulStart();
}

void AutoTestDlg::on_testBtn4_clicked()
{
    PLCManager::getInstance()->SetMulStop();
}

void AutoTestDlg::UpdateCheckResultCK(int datatype,int nId, float fVal)
{
    //从map 中找到 CK的 ID=3
    //QString str = QString("%1").arg(fVal);
    AutoTestData& atd = pXL->m_lstMNLTDJC[datatype][nId];// .val;// = str;
    //atd.val = str;


    AddTableWidget(pXL->m_lstMNLTDJC[datatype][nId]);
    AddAutoTestResult(atd);
}

void AutoTestDlg::on_timeout()
{
    //qDebug() << "dongya ==="<<PLCManager::getInstance()->ReadDongYa();
    //qDebug() << "jingya ===" << PLCManager::getInstance()->ReadJingYa();
    //qDebug() << "zongya ===" << PLCManager::getInstance()->ReadZongYa();

    //qDebug() << "100kpa bool333 = " << PLCManager::getInstance()->Read1MinValid();
    //qDebug() << "100kpa bool111 = " << PLCManager::getInstance()->Read1MinUnValid();
    //qDebug() << "100kpa bool = " << PLCManager::getInstance()->Read100KPaIsEnd();
    //qDebug() << "100kpa bool = " << PLCManager::getInstance()->Read100KPaIsEnd();
    //qDebug() << "60kpa bool = " << PLCManager::getInstance()->Read60KPaIsEnd();
    //qDebug() << "20kpa bool = " << PLCManager::getInstance()->Read20KPaIsEnd();
    LogMgr* pLog = LogMgr::GetInstance();
    ui.lable_date->setText(pLog->GetCurrentDate());
    ui.lable_time->setText(pLog->GetCurrentTimeHMS());
}
