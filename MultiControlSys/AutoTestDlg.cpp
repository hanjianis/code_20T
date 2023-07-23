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
//���Խ�� �����
#define COLUMN_VAL  3
#define COLUMN_UNIT  4
#define COLUMN_CONTENT  5
int systemclass;
int automatictestingclass;
AutoTestDlg::AutoTestDlg(int nType,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	pXL = XLManager::GetInstance();
	_tcpClient = TCPClient::GetInstance();
    //ʹ��udp
	_udpServer = UDPServer::getInstance();


    ui.progressBar->setTextVisible(false);
    ui.progressBar->setValue(10);

	excelOperate = new ExcelOperate(this);
	_type = nType;
    _tmid_auto = 0;            //�Զ����
    _tmid = 0;             //ϵͳ�Լ�
	ui.comboBox->clear();
	ui.comboBox_3->clear();
	ui.comboBox_3->addItem(QString::fromLocal8Bit("������Ŀ"));
	QStringList lst;
    lst << QString::fromLocal8Bit("ѡ����Ե�Ԫ");
	//����һ������������״̬ �ڵ����ʼ��ť��ʱ�� �ж�����
	SPQ_Manager::getInstance()->RequestPowerControl();

	if (_type == ATT_SYS)
	{
		
		ui.lineEdit->setText(QString::fromLocal8Bit("ϵͳ�Լ�״̬"));

        lst << QString::fromLocal8Bit("�Լ�ģ�����Լ�")
               << QString::fromLocal8Bit("���ܼ��")
                    << QString::fromLocal8Bit("�ź�Դ�Լ�")
                        << QString::fromLocal8Bit("Ŀ��ģ�����Լ�")
                           << QString::fromLocal8Bit("�߶ȱ��ź�Դ�Լ�")
                              << QString::fromLocal8Bit("�ۺϵ�Դ�Լ�")
                              << QString::fromLocal8Bit("ϵͳ�Լ�");
		ui.comboBox->addItems(lst);
		lst.clear();
        //cobobox�����Ŀ
		lst << QString::fromLocal8Bit("��������") << QString::fromLocal8Bit("ϵͳ�Լ�");
		//ui.listWidget->setVisible(false);
		ui.comboBox_3->addItems(XLManager::GetInstance()->m_lstSelfCheckItems);
	}
	else
	{
        ui.lineEdit->setText(QString::fromLocal8Bit("YJ-12ս����"));
        lst << QString::fromLocal8Bit("������Ԫ") << QString::fromLocal8Bit("��ϵͳ��Ԫ") << QString::fromLocal8Bit("��ѹ�߶ȱ�Ԫ")
            << QString::fromLocal8Bit("���ߵ�߶ȱ�Ԫ") << QString::fromLocal8Bit("�״ﵥԪ") << QString::fromLocal8Bit("�ߵ�ϵͳ��Ԫ")
             << QString::fromLocal8Bit("�ɿز���")<< QString::fromLocal8Bit("�ۺϼ��")<< QString::fromLocal8Bit("����������") << QString::fromLocal8Bit("�ۺϲ���")
            << QString::fromLocal8Bit("�������");
		ui.comboBox->addItems(lst);
		//ui.comboBox_3->addItems(XLManager::GetInstance()->m_lstAutoTestItems);
        //ui.comboBox_3->addItem(QString::fromLocal8Bit("������Ŀ"));
      //  m_at = new AutoTestWidget(ui.listItems);
       // ui.verticalLayout_16->addWidget(m_at);

        m_integratedlowerdisplay=new IntegratedLowerDisplay(ui.listItems);
        m_integratedlowerdisplay->close();
        ui.verticalLayout_16->addWidget(m_integratedlowerdisplay);


	}

    m_itemsdlg = new TestItemsDlg();
    m_intergraeddialog = new IntegratedTestDialog();
    //GlobalManager::getInstance()->m_at = m_at;//���Զ����� -�����������
	ui.comboBox_2->setDisabled(true);
    ui.comboBox_3->setDisabled(true);

    //tablewigetˮƽ��ͷ
	ui.tableWidget->setRowCount(0);
	ui.tableWidget->verticalHeader()->hide();
	ui.tableWidget->setColumnWidth(0, 80);
	ui.tableWidget->setColumnWidth(1, 300);
	ui.tableWidget->setColumnWidth(2, 140);
	ui.tableWidget->setColumnWidth(3, 140);
	ui.tableWidget->setColumnWidth(4, 130);
	ui.tableWidget->setColumnWidth(5, 130);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //�����
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //����ѡ��ģʽ

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

	QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();Ҳ����
	move(0, 0);
	//connect(CK_Manager::getInstance(), SIGNAL(UpdateCheckResult(int,float)), this, SLOT(UpdateCheckResultCK(int, float)));
//	CreateExcel();
   // connect(this, SIGNAL(sig_testunit(int)), this, SLOT(SetTestUseTm()));

}

AutoTestDlg::~AutoTestDlg()
{
}

//��Ŀ���ν��в���
void AutoTestDlg::MNLTDJC()
{
	ISysCheckItem* task1 = _lstTaskDataType.front();

	if (task1 != nullptr)
	{
		if (task1->is_stop())//�Ѿ����� ����һ��
		{
            _lstTaskDataType.pop_front();  //ɾ��ͷ�ڵ�
			if (_lstTaskDataType.size() > 0)
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
//				_tcpClient->SendMsgID(eMsg_T_OnTestOver);
				ui.quit->setEnabled(true);

			}
		}
	}
	//AutoTestData atd = pXL->m_lstMNLTDJC[_datatype].at(_lstindex);
	//AddTableWidget(atd);

	//_lstindex++;
	////����UDP ����
	//if (atd.type == AUTO_TYPE_UDP)
	//{
	//	//�������
	//	if (_datatype == 3)//�̿ع�����
	//	{

	//	}
	//}
	//if (_lstindex >= pXL->m_lstMNLTDJC[_datatype].count())
	//{
	//	//����һ��
	//	_lstindex = 0;
	//	_lstTaskDataType.pop_front();
	//	if (_lstTaskDataType.size() > 0)//����
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


//��Ŀ���ν��в���
void AutoTestDlg::MNLTDJC1()
{
    IntegratedTesting* task1 = _lstTaskDataType1.front();

    if (task1 != nullptr)
    {
        if (task1->is_stop())//�Ѿ����� ����һ��
        {
            _lstTaskDataType1.pop_front();  //ɾ��ͷ�ڵ�
            if (_lstTaskDataType1.size() > 0)
            {
                IntegratedTesting* task2 = _lstTaskDataType1.front();
                task2->StartCheck();
            }
            else
            {
                killTimer(_tmid_auto);
                ui.btnstart->setDisabled(false);
                ui.toolButton_2->setDisabled(false);
                ui.quit->setDisabled(false);
                killTimer(_tmid_auto);
                m_tmTestUseTm->stop();
                int usetm = (GetTickCount() - _startTickCount) / 1000;
                excelOperate->SaveAs(usetm);
//				_tcpClient->SendMsgID(eMsg_T_OnTestOver);
                ui.quit->setEnabled(true);

            }
        }
    }
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

//����ʱ��
void AutoTestDlg::SetTestUseTm()
{
	int usetm = (GetTickCount() - _startTickCount)/1000;

	//ת����00:00:00��ʽ
	QString str = QString("%1:%2:%3").arg(usetm/3600, 2, 10, QLatin1Char('0'))
		.arg((usetm % 3600)/60, 2, 10, QLatin1Char('0'))
		.arg(usetm % 60, 2, 10, QLatin1Char('0'));
	ui.lineEdit_2->setText(str);
}

//��ӱ��и��ֶ�����
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

//��ӱ��и��ֶ�����
void AutoTestDlg::AddAutoTestResult(AutoTestData& atd)
{
	
	int row = ui.tableWidget->rowCount()-1;
	QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(atd.val));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, COLUMN_VAL, item);
	//���½��
	if (atd.content == 1)
	{
		item = new QTableWidgetItem(QString::fromLocal8Bit("��"));
		_correct_count++;
	}
	else if (atd.content == 0)
	{
		item = new QTableWidgetItem(QString::fromLocal8Bit("��"));
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
	updateResult();//������ȷ ��������
}

//������ȷ ��������
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
    if (tmid == _tmid)  //ϵͳ�Լ�
	{
		
		MNLTDJC();
		return;
	}
	if (_tmid_auto == tmid)
	{
        MNLTDJC1();
        return;
        /*
		ITask* task1 = pXL->m_lstTasks.front();
		if (task1 != nullptr)
		{
			
			if (task1->is_stop())//�Ѿ����� ����һ��
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
					UpdateToolTip(QString::fromLocal8Bit("����������̽���"));
					int usetm = (GetTickCount() - _startTickCount) / 1000;
					excelOperate->SaveAs(usetm);
                //	_tcpClient->SendMsgID(eMsg_T_OnTestOver);
					ui.quit->setEnabled(true);
				}
			}
		}
        */
		//AutoSingle();
	}
	/*
	//�ۺ�
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
			
			//ֹͣ
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
	UpdateToolTip(QString::fromLocal8Bit("����������̽���"));
	int usetm = (GetTickCount() - _startTickCount) / 1000;
	excelOperate->SaveAs(usetm);
//	_tcpClient->SendMsgID(eMsg_T_OnTestOver);
	ui.quit->setEnabled(true);
}
void AutoTestDlg::on_quit_clicked()
{
	close();
}

   //��ʼ��ť
void AutoTestDlg::on_btnstart_clicked()
{
	bool bStartSuccess = false;//�Ƿ���Կ�ʼִ��
    _startTickCount = GetTickCount();  //��ȡϵͳʱ��
	_correct_count = 0;
	_error_count = 0;
//ϵͳ�Լ�
	if (_type == ATT_SYS)
	{
		//���ж��������Ƿ�����

		if (SPQ_Manager::getInstance()->CheckLineConnected() == false)
		{
			MessageBoxDlg dlg(QString::fromLocal8Bit("��������Ƿ�������ȷ"));
			dlg.exec();
			return;
		}

        int unit = ui.comboBox->currentIndex();

//		_tcpClient->SendMsgID(eMsg_T_OnSelfCheck);

        if ((unit != SELF_TEST)&&(unit !=AIRTIGHTNESS_INSPECTION))
        {
           // _lstTaskDataType.append(0);
            return;
        }else{

            _datatype = ui.comboBox_3->currentIndex();
            ui.comboBox->setDisabled(true);
            ui.comboBox_2->setDisabled(true);
            ui.btnstart->setDisabled(true);
            ui.toolButton_2->setEnabled(true);
            ui.quit->setDisabled(true);
            _lstTaskDataType.clear();        //ϵͳ�Լ�ʱ Ҫ�Լ����������ID����

        }

        //���ܼ��
        if(unit == AIRTIGHTNESS_INSPECTION)
        {
            systemclass=0;
        }
        //ϵͳ�Լ�
        if(unit == SELF_TEST)
        {
            systemclass=1;
        }



		ui.tableWidget->setRowCount(0);

        if (_datatype == 0)//������Ŀ(������Ŀ��
		{
			for (int i = 1; i <= 9; i++)
			{
                /*
				if(i == 3)
                    _lstTaskDataType.push_back(new CK_Manager(this));
				else
					_lstTaskDataType.push_back(new ISysCheckItem(i, this));
                    */
                _lstTaskDataType.push_back(new ISysCheckItem(i, this));
			}
		}

        /*
        if (_datatype == 3)  //�̿���Ŀ
			_lstTaskDataType.push_back(new CK_Manager(this));
		else{

			_lstTaskDataType.push_back(new ISysCheckItem(_datatype, this));
		}
*/

		_lstindex = 0;
		CreateExcel();
        _tmid = startTimer(50);

        ui.label_2->setText(QString::fromLocal8Bit("���Կ�ʼ"));
        _reminderinformation=0;
        m_reminderinformation->start(1000);


		bStartSuccess = true;


	}
	if (_type == ATT_AUTO)
	{
		int unit = ui.comboBox->currentIndex();

        if ((unit != INTEGRATED_TESTING)&&(unit !=ZERORETURN_STEERGEAR))
        {
           // _lstTaskDataType1.append(0);
            return;
        }else{

            _datatype = ui.comboBox_3->currentIndex();
            ui.comboBox->setDisabled(true);
            ui.comboBox_2->setDisabled(true);
            ui.btnstart->setDisabled(true);
            ui.toolButton_2->setEnabled(true);
            ui.quit->setDisabled(true);
            _lstTaskDataType1.clear();        //�Զ�����ʱ Ҫ�Լ����������ID����

        }

        //�ۺϲ���
        if(unit == INTEGRATED_TESTING)
        {
            automatictestingclass=0;
            //m_itemsdlg->exec();
            m_intergraeddialog->exec();
        }

        //�������
        if(unit == ZERORETURN_STEERGEAR)
        {
            automatictestingclass=1;
        }

        ui.tableWidget->setRowCount(0);

        if (_datatype == 0)//������Ŀ(������Ŀ��
        {
            for (int i = 1; i <= 9; i++)
            {
                /*
                if(i == 3)
                    _lstTaskDataType.push_back(new CK_Manager(this));
                else
                    _lstTaskDataType.push_back(new ISysCheckItem(i, this));
                    */
                _lstTaskDataType1.push_back(new IntegratedTesting(i, this));
            }
        }
        /*
        if (_datatype == 3)  //�̿���Ŀ
            _lstTaskDataType.push_back(new CK_Manager(this));
        else{

            _lstTaskDataType1.push_back(new IntegratedTesting(_datatype, this));
        }
*/
        _lstindex = 0;
        CreateExcel();
       _tmid_auto = startTimer(50);

        ui.label_2->setText(QString::fromLocal8Bit("���Կ�ʼ"));
        _reminderinformation1=0;
        m_reminderinformation1->start(1000);


        bStartSuccess = true;






        /*
		if (unit > MULT_TEST)
			return;

		if (unit == SIGNLE_TEST)//�������
		{
//			_tcpClient->SendMsgID(eMsg_T_OnItemTest);
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
		if (unit == INS_TEST)// �ߵ�����
		{
//			_tcpClient->SendMsgID(eMsg_T_OnINS);
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
		if (unit == MULT_TEST)//�ۺϲ���
		{
//			_tcpClient->SendMsgID(eMsg_T_OnComprehensiveTest);
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
        */

	}
	if (bStartSuccess == true)
	{
//		_tcpClient->SendMsgID(eMsg_T_OnTestStart);
		ui.quit->setEnabled(false);
        m_tmTestUseTm->start();          //����ʱ�俪ʼ
	}
}

        //��ͣ��ť
void AutoTestDlg::on_toolButton_2_clicked()
{
    /*
    MessageBoxDlg dlg(QString::fromLocal8Bit("��������Ƿ�������ȷ"));
    dlg.exec();
    */
	if (_type == ATT_SYS)//ϵͳ�Լ���ͣ
	{
        m_reminderinformation->stop();
		killTimer(_tmid);
		_tmid = 0;
		//����δ������� ������Ϊ�����
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
        m_reminderinformation1->stop();
        killTimer(_tmid_auto);
        _tmid_auto = 0;
        //����δ������� ������Ϊ�����
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
		if (unit == SIGNLE_TEST)//���������ͣ
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
			UpdateToolTip(QString::fromLocal8Bit("����������̽���"));
		}
		if (unit == INS_TEST)//�ߵ�������ͣ
		{
			_insTest->StopCheck();
			return;
		}
		if (unit == MULT_TEST)//�ߵ�������ͣ
		{
			_multTest->StopCheck();
			return;
		}
        */
	}
	
	m_tmTestUseTm->stop();
	int usetm = (GetTickCount() - _startTickCount) / 1000;
	excelOperate->SaveAs(usetm);
//	_tcpClient->SendMsgID(eMsg_T_OnTestOver);
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
//	_tcpClient->SendMsgID(eMsg_T_OnTestOver);
	ui.quit->setEnabled(true);
}

void AutoTestDlg::RecvStopMultiSlot()
{
	UpdateToolTip(QString::fromLocal8Bit("�ۺϲ������̽���"));
	m_tmTestUseTm->stop();
	int usetm = (GetTickCount() - _startTickCount) / 1000;
	excelOperate->SaveAs(usetm);
//	_tcpClient->SendMsgID(eMsg_T_OnTestOver);
	ui.quit->setEnabled(true);
}

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
//���³̿ؽṹ
void AutoTestDlg::UpdateCheckResultCK(int datatype,int nId, float fVal)
{
	//��map ���ҵ� CK�� ID=3
	//QString str = QString("%1").arg(fVal);
	AutoTestData& atd = pXL->m_lstMNLTDJC[datatype][nId];// .val;// = str;
	//atd.val = str;
	
    //��ӱ��������
	AddTableWidget(pXL->m_lstMNLTDJC[datatype][nId]);
	AddAutoTestResult(atd);
}

//ʵʱ���ݺ�ʱ��
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

void AutoTestDlg::slot_reminderinformation()
{
    _reminderinformation++;
    emit sig_reminderinformationupdate();
}

void AutoTestDlg::slots_reminderinformation()
{
    if(_reminderinformation==1)
    ui.label_2->setText(QString::fromLocal8Bit("�̵���ģ���ʼ����..."));
    if(_reminderinformation==2)
    ui.label_2->setText(QString::fromLocal8Bit("��·����ģ���ʼ����..."));
    if(_reminderinformation==3)
    ui.label_2->setText(QString::fromLocal8Bit("1553Bģ���ʼ����..."));
    if(_reminderinformation==4)
    ui.label_2->setText(QString::fromLocal8Bit("IOģ���ʼ����..."));
    if(_reminderinformation==5)
    ui.label_2->setText(QString::fromLocal8Bit("��ѹ��ģ���ʼ����..."));
    if(_reminderinformation==6)
    ui.label_2->setText(QString::fromLocal8Bit("DAģ���ʼ����..."));

    if(_reminderinformation==10)
    {
        ISysCheckItem* task1 = _lstTaskDataType.front();
        task1->StartCheck();          //��ʼ����
    }
}

void AutoTestDlg::slot_reminderinformation1()
{
    _reminderinformation1++;
    emit sig_reminderinformationupdate1();
}

void AutoTestDlg::slots_reminderinformation1()
{   
    if(_reminderinformation1==1)
    ui.label_2->setText(QString::fromLocal8Bit("�̵���ģ���ʼ����..."));
    if(_reminderinformation1==2)
    ui.label_2->setText(QString::fromLocal8Bit("��·����ģ���ʼ����..."));
    if(_reminderinformation1==3)
    ui.label_2->setText(QString::fromLocal8Bit("1553Bģ���ʼ����..."));
    if(_reminderinformation1==4)
    ui.label_2->setText(QString::fromLocal8Bit("IOģ���ʼ����..."));
    if(_reminderinformation1==5)
    ui.label_2->setText(QString::fromLocal8Bit("��ѹ��ģ���ʼ����..."));
    if(_reminderinformation1==6)
    ui.label_2->setText(QString::fromLocal8Bit("DAģ���ʼ����..."));

    if(_reminderinformation1==10)
    {        
        IntegratedTesting* task2 = _lstTaskDataType1.front();
        task2->StartCheck();          //��ʼ����
    }
}

void AutoTestDlg::slot_showAutoTestWidget()
{
  //  m_at->UpdateInsLables(1, 40);
    m_integratedlowerdisplay->show();
}
void AutoTestDlg::slot_showAutoTestWidget1()
{
   // m_at->UpdateInsLables(1, 40);
 //   m_at->close();
    //ui.listItems->clearMask();
}
//��ʾ����
void AutoTestDlg::slot_endTaskItem()
{
    ui.label_2->setText(QString::fromLocal8Bit("���Խ���"));
    ui.btnstart->setDisabled(false);
    ui.toolButton_2->setDisabled(false);
    ui.quit->setEnabled(true);
    m_reminderinformation->stop();
    m_reminderinformation1->stop();

}
