#include "AutoTestDlg12A.h"
#include "ui_AutoTestDlg12A.h"
#include "Packet.h"
#include "XLManager.h"
#include <QDesktopWidget>
#include "PowerTask.h"
#include "LogMgr.h"
#include <QDebug>
#include "MessageBoxDlg.h"
#include "GlobalManager.h"

//测试结果 列序号
#define COLUMN_VAL  3
#define COLUMN_UNIT  4
#define COLUMN_CONTENT  5
//int systemclass;
int automatictestingclass;

int hearBeat_CK;       //识别程控心跳包
int hearBeat_CK20T;       //识别程控心跳包
int hearBeat_SPQ;      //识别适配器心跳包
int hearBeat_HT;       //识别滑台心跳包
int hearBeat_ZJ;       //识别自检模拟器心跳包
int end_test;

AutoTestDlg12A::AutoTestDlg12A(int nType,QWidget *parent) :
    QDialog(parent)
{


    //给窗口添加背景图
    QPixmap Images(":/MultiControlSys/res/bk.png");
    QPalette Palette = this->palette();
    Palette.setBrush(QPalette::Background, Images);
    this->setPalette(Palette);
    ui.setupUi(this);
    pXL = XLManager::GetInstance();
    _tcpClient = TCPClient::GetInstance();
    //使用udp
    _udpServer = UDPServer::getInstance();


    ui.progressBar->setTextVisible(false);
    ui.progressBar->setValue(10);

    excelOperate = new ExcelOperate(this);
    _type = nType;
    _tmid_auto = 0;            //自动检测
    _tmid = 0;             //系统自检
    ui.comboBox->clear();
    ui.comboBox_3->clear();
    ui.comboBox_3->addItem(QString::fromLocal8Bit("所有项目"));
    QStringList lst;
    lst << QString::fromLocal8Bit("选择测试单元");
    //请求一下适配器连接状态 在点击开始按钮的时候 判断数据
    hearBeat_CK=0;
    hearBeat_CK20T=0;       //识别程控心跳包
    //请求滑台
    hearBeat_SPQ=0;
    //请求程控
    hearBeat_HT=0;
    //请求自检模拟器
    hearBeat_ZJ=0;

    if (_type == ATT_SYS)
    {
        ui.lineEdit->setText(QString::fromLocal8Bit("系统自检状态"));

        lst << QString::fromLocal8Bit("自检模拟器自检")
               << QString::fromLocal8Bit("气密检查")
                    << QString::fromLocal8Bit("信号源自检")
                        << QString::fromLocal8Bit("目标模拟器自检")
                           << QString::fromLocal8Bit("高度表信号源自检")
                              << QString::fromLocal8Bit("综合电源自检")
                              << QString::fromLocal8Bit("系统自检");
        ui.comboBox->addItems(lst);
        lst.clear();
        //cobobox添加项目
        lst << QString::fromLocal8Bit("连续测试") << QString::fromLocal8Bit("系统自检");
        //ui.listWidget->setVisible(false);
        ui.comboBox_3->addItems(XLManager::GetInstance()->m_lstSelfCheckItems);
    }
    else
    {
        ui.lineEdit->setText(QString::fromLocal8Bit("YJ-12战斗弹"));
        lst << QString::fromLocal8Bit("电气单元") << QString::fromLocal8Bit("舵系统单元") << QString::fromLocal8Bit("气压高度表单元")
            << QString::fromLocal8Bit("无线电高度表单元") << QString::fromLocal8Bit("雷达单元") << QString::fromLocal8Bit("惯导系统单元")
             << QString::fromLocal8Bit("飞控测试")<< QString::fromLocal8Bit("综合检查")<< QString::fromLocal8Bit("总线冗余检查") << QString::fromLocal8Bit("综合测试")
            << QString::fromLocal8Bit("舵机回零");
        ui.comboBox->addItems(lst);
        //ui.comboBox_3->addItems(XLManager::GetInstance()->m_lstAutoTestItems);
        //ui.comboBox_3->addItem(QString::fromLocal8Bit("所有项目"));
      //  m_at = new AutoTestWidget(ui.listItems);
       // ui.verticalLayout_16->addWidget(m_at);

        m_integratedlowerdisplay=new IntegratedLowerDisplay(ui.listItems);
        m_integratedlowerdisplay->close();
        ui.verticalLayout_16->addWidget(m_integratedlowerdisplay);
        connect(this,&AutoTestDlg12A::sig_displaylowend,m_integratedlowerdisplay,&IntegratedLowerDisplay::slot_displaylowend);
    }

   // m_itemsdlg = new TestItemsDlg();
    m_intergraeddialog = new IntegratedTestDialog();
    //GlobalManager::getInstance()->m_at = m_at;//供自动测试 -》单项测试用
    ui.comboBox_2->setDisabled(true);
    ui.comboBox_3->setDisabled(true);
    ui.toolButton_2->setDisabled(true);
   // ui.quit->setDisabled(true);

    //tablewiget水平表头
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

    m_reminderinformation=new QTimer();
    connect(m_reminderinformation, SIGNAL(timeout()), this, SLOT(slot_reminderinformation()));
    connect(this, SIGNAL(sig_reminderinformationupdate()), this, SLOT(slots_reminderinformation()));

    m_reminderinformation1=new QTimer();
    connect(m_reminderinformation1, SIGNAL(timeout()), this, SLOT(slot_reminderinformation1()));
    connect(this, SIGNAL(sig_reminderinformationupdate1()), this, SLOT(slots_reminderinformation1()));


    setWindowFlags(Qt::FramelessWindowHint);
    resize(WIDTH, HEIGHT);

    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move(0, 0);
    //connect(CK_Manager::getInstance(), SIGNAL(UpdateCheckResult(int,float)), this, SLOT(UpdateCheckResultCK(int, float)));
//	CreateExcel();
   // connect(this, SIGNAL(sig_testunit(int)), this, SLOT(SetTestUseTm()));
    _ck12amanager=CK_Manager12A::getInstance();
    _ck20tmanager=CK_Manager20T::getInstance();
    _spq12amanager=SPQ_Manager12A::getInstance();
    _zjmanager=ZJ_Manager::getInstance();
    _htmanager=HT_Manager::getInstance();
    _diagnosticpause=new DiagnosticPause;
    connect(_diagnosticpause, SIGNAL(sig_diagnosticpause()), this, SLOT(slots_diagnosticpause()));

}

AutoTestDlg12A::~AutoTestDlg12A()
{

}

//项目依次进行测试
void AutoTestDlg12A::MNLTDJC()
{
    ISysCheckItem12A* task1 = _lstTaskDataType.front();

    if (task1 != nullptr)
    {
        if (task1->is_stop())//已经结束 换下一个
        {
            _lstTaskDataType.pop_front();  //删除头节点
            if (_lstTaskDataType.size() > 0&&end_test==0)
            {               
                ISysCheckItem12A* task2 = _lstTaskDataType.front();
                task2->StartCheck();
            }
            else
            {
                killTimer(_tmid);
              //  ui.btnstart->setDisabled(false);
               // ui.toolButton_2->setDisabled(true);
                //ui.quit->setDisabled(false);
                killTimer(_tmid);
                m_tmTestUseTm->stop();
                int usetm = (GetTickCount() - _startTickCount) / 1000;
                excelOperate->SaveAs(usetm);
                _tcpClient->SendMsgID(eMsg_T_OnTestOver);
                slot_endTaskItem();

            }
        }
    }    
}


//项目依次进行测试
void AutoTestDlg12A::MNLTDJC1()
{
    IntegratedTesting* task1 = _lstTaskDataType1.front();

    if (task1 != nullptr)
    {
        if (task1->is_stop())//已经结束 换下一个
        {
            _lstTaskDataType1.pop_front();  //删除头节点
            if (_lstTaskDataType1.size() > 0&&end_test==0)
            {
                IntegratedTesting* task2 = _lstTaskDataType1.front();
                task2->StartCheck();
            }
            else
            {
                killTimer(_tmid_auto);
               // ui.btnstart->setDisabled(false);
                //ui.toolButton_2->setDisabled(false);
               // ui.quit->setDisabled(false);
                killTimer(_tmid_auto);
                m_tmTestUseTm->stop();
                int usetm = (GetTickCount() - _startTickCount) / 1000;
                excelOperate->SaveAs(usetm);
                _tcpClient->SendMsgID(eMsg_T_OnTestOver);
                slot_endTaskItem();

            }
        }
    }
}

void AutoTestDlg12A::CreateExcel()
{
    int unit = ui.comboBox->currentIndex();
    excelOperate->CreateExcel(_type,unit);
    excelOperate->_FileInfo.unitType = _type;
    excelOperate->_FileInfo.unitName = ui.comboBox->currentText();
    excelOperate->_FileInfo.modeType = ui.comboBox_2->currentIndex();
    excelOperate->_FileInfo.modeName = ui.comboBox_2->currentText();
}

//测试时间
void AutoTestDlg12A::SetTestUseTm()
{
    int usetm = (GetTickCount() - _startTickCount)/1000;

    //转化成00:00:00格式
    QString str = QString("%1:%2:%3").arg(usetm/3600, 2, 10, QLatin1Char('0'))
        .arg((usetm % 3600)/60, 2, 10, QLatin1Char('0'))
        .arg(usetm % 60, 2, 10, QLatin1Char('0'));
    ui.lineEdit_2->setText(str);
}

//添加表中各字段数据
void AutoTestDlg12A::AddTableWidget(AutoTestData& atd)
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

//添加表中各字段数据
void AutoTestDlg12A::AddAutoTestResult(AutoTestData& atd)
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
void AutoTestDlg12A::updateResult()
{
    QString str = QString("%1").arg(_correct_count);
    ui.lineEdit_3->setText(str);
    str = QString("%4").arg(_error_count);
    ui.lineEdit_4->setText(str);
}

void AutoTestDlg12A::timerEvent(QTimerEvent *event)
{
    int tmid = event->timerId();
    if (tmid == _tmid)  //系统自检
    {

        MNLTDJC();
        return;
    }
    if (_tmid_auto == tmid)
    {
        MNLTDJC1();
        return;       
    }   
}
void AutoTestDlg12A::DQ_Failed()//have not tested
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
void AutoTestDlg12A::on_quit_clicked()
{
//    if (PLCManager12A::getInstance()->ConnectPLC() == true)
//    {
//        PLCManager12A::getInstance()->DisConnectPLC();

//    }
    close();
}

   //开始按钮
void AutoTestDlg12A::on_btnstart_clicked()
{
    ui.label_2->setText(QString::fromLocal8Bit("测试开始"));
    bool bStartSuccess=false;  //是否可以开始执行
    _startTickCount = GetTickCount();  //读取系统时间
    _correct_count = 0;
    _error_count = 0;
      
    
    if (hearBeat_CK20T == 1)
    {
        MessageBoxDlg dlg(QString::fromLocal8Bit("20T程控已连接"));
      //  dlg.exec();
        _ck20tmanager->RequestPowerControl(1,1);    //暂定，后期确
    }else
    {
        MessageBoxDlg dlg(QString::fromLocal8Bit("20T程控未连接"));
        dlg.exec();
        return;
    }
    //先判断程控是否正常
    if (hearBeat_CK == 1)
    {
        MessageBoxDlg dlg(QString::fromLocal8Bit("程控已连接"));
     //   dlg.exec();
        _ck12amanager->RequestPowerControl(1,1);
        
    }else
    {
        MessageBoxDlg dlg(QString::fromLocal8Bit("程控未连接"));
        dlg.exec();
        return;
    }        
    //先判断适配器是否正常
    if (hearBeat_SPQ == 1)
    {
        MessageBoxDlg dlg(QString::fromLocal8Bit("适配器已连接"));
      //  dlg.exec();
    }else
    {
        MessageBoxDlg dlg(QString::fromLocal8Bit("适配器未连接"));
        dlg.exec();
        return;
    }       
    /*
    //先判断自检模拟器是否正常（暂时不用）
    if (hearBeat_ZJ == 1)
    {
        MessageBoxDlg dlg(QString::fromLocal8Bit("自检模拟器已连接"));
        dlg.exec();
    }else
    {
        MessageBoxDlg dlg(QString::fromLocal8Bit("自检模拟器未连接"));
        dlg.exec();
        return;
    }
    */
   
    //先判断滑台是否正常
   // if(1)
    if (hearBeat_HT == 1)
    {
        MessageBoxDlg dlg(QString::fromLocal8Bit("滑台已连接"));
       // dlg.exec();
        _htmanager->RequestPowerControl(1, 0, 1000);
        Sleep(25000);
        _htmanager->RequestPowerControl(1,1, 1000);       
       
        Sleep(25000);
        _htmanager->RequestPowerControl(2,1,2000);
        Sleep(25000);
        _htmanager->RequestPowerControl(2, 0, 2000);
    }else
    {
        MessageBoxDlg dlg(QString::fromLocal8Bit("滑台未连接"));
        dlg.exec();
        return;
    }
    


//系统自检
    if (_type == ATT_SYS)
    {
        int unit = ui.comboBox->currentIndex();

        _tcpClient->SendMsgID(eMsg_T_OnSelfCheck);

        if(unit==0)
       // if ((unit != SELF_TEST)&&(unit !=AIRTIGHTNESS_INSPECTION))
        {
          //  _lstTaskDataType.append(0);
            return;
        }else{
            //对用的类型需要变化一下
            _datatype = unit;
          //  _datatype = ui.comboBox_3->currentIndex();
            ui.comboBox->setDisabled(true);
            ui.comboBox_2->setDisabled(true);
           // ui.comboBox_3->setDisabled(true);
            ui.btnstart->setDisabled(true);
            ui.toolButton_2->setEnabled(true);
            ui.quit->setDisabled(true);
            _lstTaskDataType.clear();        //系统自检时 要自检的数据类型ID集合

        }

        /*
        //气密检查
        if(unit == AIRTIGHTNESS_INSPECTION)
        {            
            systemclass=0;
        }
        //系统自检
        if(unit == SELF_TEST)
        {
            systemclass=1;
        }
        */



        ui.tableWidget->setRowCount(0);

        if (_datatype == 7)//所有项目(测试项目）
        {
            for (int i = 1; i <= 7; i++)
            {
                /*
                if(i == 3)
                    _lstTaskDataType.push_back(new CK_Manager12A(this));
                else
                */
                _lstTaskDataType.push_back(new ISysCheckItem12A(i, this));
            }
        }
        //自检模拟器自检
        if (_datatype == 1)
        {
            _lstTaskDataType.push_back(new ISysCheckItem12A(1, this));
            _lstTaskDataType.push_back(new ISysCheckItem12A(7, this));
        }
        //气密检查
        if (_datatype == 2)
        {
            _lstTaskDataType.push_back(new ISysCheckItem12A(3, this));
            _lstTaskDataType.push_back(new ISysCheckItem12A(7, this));
        }
        //信号源自检
        if (_datatype == 3)
        {
            _lstTaskDataType.push_back(new ISysCheckItem12A(5, this));
            _lstTaskDataType.push_back(new ISysCheckItem12A(7, this));
        }
        //目标模拟器自检
        if (_datatype == 4)
        {
            _lstTaskDataType.push_back(new ISysCheckItem12A(2, this));
            _lstTaskDataType.push_back(new ISysCheckItem12A(7, this));
        }
        //高度表信号源自检
        if (_datatype == 5)
        {
            _lstTaskDataType.push_back(new ISysCheckItem12A(4, this));
            _lstTaskDataType.push_back(new ISysCheckItem12A(7, this));
        }
        //综合电源自检
        if (_datatype == 6)
        {
            _lstTaskDataType.push_back(new ISysCheckItem12A(6, this));
            _lstTaskDataType.push_back(new ISysCheckItem12A(7, this));
        }
       // _lstTaskDataType.push_back(new ISysCheckItem12A(_datatype, this));

        _lstindex = 0;
       // CreateExcel();
        _tmid = startTimer(50);

       // ui.label_2->setText(QString::fromLocal8Bit("测试开始"));
        _reminderinformation=0;
        m_reminderinformation->start(1000);


        bStartSuccess = true;


    }
    if (_type == ATT_AUTO)
    {
        /*
        if (PLCManager12A::getInstance()->ConnectPLC() == true)
        {
            PLCManager12A::getInstance()->SetSingleStart();          
            PLCManager12A::getInstance()->ReadPLC();
        }else
        {
            MessageBoxDlg dlg(QString::fromLocal8Bit("PLC未连接"));
            dlg.exec();
            return;
        }
*/
        int unit = ui.comboBox->currentIndex();

        if ((unit != INTEGRATED_TESTING)&&(unit !=ZERORETURN_STEERGEAR))
        {
           // _lstTaskDataType1.append(0);
            return;
        }else{

            _datatype = ui.comboBox_3->currentIndex();
            ui.comboBox->setDisabled(true);
            ui.comboBox_2->setDisabled(true);
            ui.comboBox_3->setDisabled(true);
            ui.btnstart->setDisabled(true);
            ui.toolButton_2->setEnabled(true);
            ui.quit->setDisabled(true);
            _lstTaskDataType1.clear();        //自动测试时 要自检的数据类型ID集合

        }

        //综合测试
        if(unit == INTEGRATED_TESTING)
        {
            automatictestingclass=0;
            //m_itemsdlg->exec();
            m_intergraeddialog->exec();
        }

        //舵机回零
        if(unit == ZERORETURN_STEERGEAR)
        {
            automatictestingclass=1;
        }

        ui.tableWidget->setRowCount(0);

        if (_datatype == 0)//所有项目(测试项目）
        {
            for (int i = 1; i <= 10; i++)
            {
                /*
                if(i == 3)
                    _lstTaskDataType.push_back(new CK_Manager(this));
                else
                    _lstTaskDataType.push_back(new ISysCheckItem12A(i, this));
                    */
                _lstTaskDataType1.push_back(new IntegratedTesting(i, this));
            }
        }
        /*
        if (_datatype == 3)  //程控项目
            _lstTaskDataType.push_back(new CK_Manager(this));
        else{

            _lstTaskDataType1.push_back(new IntegratedTesting(_datatype, this));
        }
*/
        _lstindex = 0;
        CreateExcel();
       _tmid_auto = startTimer(50);

       // ui.label_2->setText(QString::fromLocal8Bit("测试开始"));
        _reminderinformation1=0;
        m_reminderinformation1->start(1000);


        bStartSuccess = true;

    }
    if (bStartSuccess == true)
    {
        _tcpClient->SendMsgID(eMsg_T_OnTestStart);
        ui.quit->setEnabled(true);
        m_tmTestUseTm->start();          //测试时间开始
    }   
}

        //暂停按钮
void AutoTestDlg12A::on_toolButton_2_clicked()
{    
    _diagnosticpause->exec();
}
//测试单元项改变
void AutoTestDlg12A::on_comboBox_currentIndexChanged(int index)
{
    if (index > 0) {
        ui.comboBox_2->setDisabled(false);
    }    
    else
    {
        ui.comboBox_2->setCurrentIndex(0);
        ui.comboBox_2->setDisabled(true);
    }

}
//测试方式改变
void AutoTestDlg12A::on_comboBox_2_currentIndexChanged(int index)
{
    if (index > 0)
    {
      //  ui.comboBox_3->setDisabled(false);
    }

    else{
        ui.comboBox_3->setCurrentIndex(0);
        ui.comboBox_3->setDisabled(true);
    }
}

void AutoTestDlg12A::UpdateToolTip(QString str)
{
    if(str.isEmpty() == false)
        ui.label_2->setText(str);
}

void AutoTestDlg12A::RecvStopInsSlot()
{
    m_tmTestUseTm->stop();
    int usetm = (GetTickCount() - _startTickCount) / 1000;
    excelOperate->SaveAs(usetm);
    _tcpClient->SendMsgID(eMsg_T_OnTestOver);
    ui.quit->setEnabled(true);
}
/*
void AutoTestDlg12A::RecvStopMultiSlot()
{
    UpdateToolTip(QString::fromLocal8Bit("综合测试流程结束"));
    m_tmTestUseTm->stop();
    int usetm = (GetTickCount() - _startTickCount) / 1000;
    excelOperate->SaveAs(usetm);
    _tcpClient->SendMsgID(eMsg_T_OnTestOver);
    ui.quit->setEnabled(true);
}
*/

//更新程控结构
void AutoTestDlg12A::UpdateCheckResultCK(int datatype,int nId, float fVal)
{
    //从map 中找到 CK的 ID=3
    //QString str = QString("%1").arg(fVal);
    AutoTestData& atd = pXL->m_lstMNLTDJC[datatype][nId];// .val;// = str;
    //atd.val = str;

    //添加表格中数据
    AddTableWidget(pXL->m_lstMNLTDJC[datatype][nId]);
    AddAutoTestResult(atd);
}

//实时数据和时间
void AutoTestDlg12A::on_timeout()
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

void AutoTestDlg12A::slot_reminderinformation()
{
    _reminderinformation++;
    emit sig_reminderinformationupdate();
}

void AutoTestDlg12A::slots_reminderinformation()
{
    if(_reminderinformation==1)
    ui.label_2->setText(QString::fromLocal8Bit("继电器模块初始化中..."));
    if(_reminderinformation==2)
    ui.label_2->setText(QString::fromLocal8Bit("多路开关模块初始化中..."));
    if(_reminderinformation==3)
    ui.label_2->setText(QString::fromLocal8Bit("1553B模块初始化中..."));
    if(_reminderinformation==4)
    ui.label_2->setText(QString::fromLocal8Bit("IO模块初始化中..."));
    if(_reminderinformation==5)
    ui.label_2->setText(QString::fromLocal8Bit("数压表模块初始化中..."));
    if(_reminderinformation==6)
    ui.label_2->setText(QString::fromLocal8Bit("DA模块初始化中..."));

    if(_reminderinformation==10)
    {
        ISysCheckItem12A* task1 = _lstTaskDataType.front();
        task1->StartCheck();          //开始测试
    }
}

void AutoTestDlg12A::slot_reminderinformation1()
{
    _reminderinformation1++;
    emit sig_reminderinformationupdate1();
}

void AutoTestDlg12A::slots_reminderinformation1()
{
    if(_reminderinformation1==1)
    ui.label_2->setText(QString::fromLocal8Bit("继电器模块初始化中..."));
    if(_reminderinformation1==2)
    ui.label_2->setText(QString::fromLocal8Bit("多路开关模块初始化中..."));
    if(_reminderinformation1==3)
    ui.label_2->setText(QString::fromLocal8Bit("1553B模块初始化中..."));
    if(_reminderinformation1==4)
    ui.label_2->setText(QString::fromLocal8Bit("IO模块初始化中..."));
    if(_reminderinformation1==5)
    ui.label_2->setText(QString::fromLocal8Bit("数压表模块初始化中..."));
    if(_reminderinformation1==6)
    ui.label_2->setText(QString::fromLocal8Bit("DA模块初始化中..."));

    if(_reminderinformation1==10)
    {
        IntegratedTesting* task2 = _lstTaskDataType1.front();
        task2->StartCheck();          //开始测试
    }
}

void AutoTestDlg12A::slot_showAutoTestWidget()
{
  //  m_at->UpdateInsLables(1, 40);
    m_integratedlowerdisplay->show();
}
void AutoTestDlg12A::slot_showAutoTestWidget1()
{
   // m_at->UpdateInsLables(1, 40);
 //   m_at->close();
    //ui.listItems->clearMask();
}
//显示结束
void AutoTestDlg12A::slot_endTaskItem()
{
    ui.label_2->setText(QString::fromLocal8Bit("测试结束"));    
    m_reminderinformation->stop();
    m_reminderinformation1->stop();
    emit sig_displaylowend();
    ui.btnstart->setDisabled(false);
    ui.toolButton_2->setDisabled(true);
    ui.quit->setEnabled(true);
    int usetm = (GetTickCount() - _startTickCount) / 1000;
    excelOperate->SaveAs(usetm);
}

void AutoTestDlg12A::slots_diagnosticpause()
{
    emit sig_displaylowend();

    if (_type == ATT_SYS)//系统自检暂停
    {
        m_reminderinformation->stop();
        killTimer(_tmid);
        _tmid = 0;
        //各个未完成任务 都设置为已完成
        while (_lstTaskDataType.size() > 0)
        {
            ISysCheckItem12A* task1 = _lstTaskDataType.front();
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
//        if (PLCManager12A::getInstance()->ConnectPLC() == true)
//        {
//            PLCManager12A::getInstance()->SetSingleStop();
//            PLCManager12A::getInstance()->SetMulStop();
//        }
        m_reminderinformation1->stop();
        killTimer(_tmid_auto);
        _tmid_auto = 0;
        //各个未完成任务 都设置为已完成
        while (_lstTaskDataType1.size() > 0)
        {
            IntegratedTesting* task1 = _lstTaskDataType1.front();
            if (task1 != nullptr)
            {
                task1->StopCheck();
                task1->_stop = true;
                _lstTaskDataType1.pop_front();
            }
        }
        /*
        int unit = ui.comboBox->currentIndex();
        if (unit > MULT_TEST)
            return;
        if (unit == SIGNLE_TEST)//单项测试暂停
        {

            killTimer(_tmid_auto);
            _tmid_auto = 0;

            while (pXL->m_lstTasks.size() > 0)
            {
                ITask* task1 = pXL->m_lstTasks.front();
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
        */
    }

    m_tmTestUseTm->stop();
    int usetm = (GetTickCount() - _startTickCount) / 1000;
    excelOperate->SaveAs(usetm);
    _tcpClient->SendMsgID(eMsg_T_OnTestOver);
    ui.btnstart->setDisabled(false);
    ui.toolButton_2->setDisabled(true);
    ui.quit->setEnabled(true);
    //GlobalManager::getInstance()->ShowButtonTip(this);
}
