#include "MultiControlSys.h"
#include "LogMgr.h"
#include "AutoTestDlg.h"
#include "AutoTestDlg12A.h"
#include "LoginDlg.h"

#include "XLManager.h"
#include <QDebug>

#include <QDesktopWidget>
#include "HistoryDlg.h"
#include "GlobalManager.h"
MultiControlSys::MultiControlSys(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

   // setWindowFlags (Qt::Window | Qt::FramelessWindowHint);
    //showFullScreen();
    //setWindowState(Qt::WindowMaximized);
	XLManager::GetInstance();
	TCPClient::GetInstance();
	//
	on_timeout();
	m_tmTimer = new QTimer();
	connect(m_tmTimer, SIGNAL(timeout()), this, SLOT(on_timeout()));
	m_tmTimer->start(1000);
	_LoginId = startTimer(100);
	
	//?????????
	/*QPushButton *btnparam;
	QPushButton *btntest;
	QPushButton *btnself_check;
	QPushButton *btnauto_test;
	QPushButton *btn_history;
	QPushButton *btn_manage;
	QPushButton *btn_qiangding;
	QPushButton *btn_help;*/
	ui.btnparam->setEnabled(true);
	ui.btntest->setEnabled(false);
	ui.btnself_check->setEnabled(false);
	ui.btnauto_test->setEnabled(false);
	ui.btn_history->setEnabled(false);
	ui.btn_manage->setEnabled(false);
	ui.btn_qiangding->setEnabled(false);
    ui.btn_help->setEnabled(false);
    setWindowFlags(Qt::FramelessWindowHint);// (Qt::CustomizeWindowHint);
    resize(WIDTH, HEIGHT);

    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();?????
   // move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
	//showMaximized();
    move(0,0);
    //setWindowFlags (Qt::Window | Qt::FramelessWindowHint);
//	ui.label_3->setMargin((rc.width() - ui.label_3->geometry().width()) / 2);
    //border-image: url(:/MultiControlSys/res/timg.jpg);
    ui.label_2->setPixmap(QPixmap(":/MultiControlSys/res/timg.jpg"));

    if(missiletype==1)
    {
        ui.label_6->setText("YJ_12");
    }
    if(missiletype==2)
    {
        ui.label_6->setText("K/AKD20");
    }
}

void MultiControlSys::timerEvent(QTimerEvent *event)
{
	int tmid = event->timerId();
	if (tmid == _LoginId)
	{
		killTimer(tmid);
		LoginDlg dlg;
        connect(&dlg,&LoginDlg::sig_pictureChange,this,&MultiControlSys::slot_pictureChange);
        if (dlg.exec() == QDialog::Accepted)   //��ʾ��½����
		{
			ui.btnparam->setEnabled(true);
            ui.btntest->setEnabled(false);
			ui.btnself_check->setEnabled(true);
			ui.btnauto_test->setEnabled(true);
			ui.btn_history->setEnabled(true);
			ui.btn_manage->setEnabled(false);
			ui.btn_qiangding->setEnabled(false);
            //��������
            if(missiletype==1)
            {
                ui.label_7->setText(QString::fromLocal8Bit("ս����"));
            }
            if(missiletype==2)
            {
                ui.label_7->setText(QString::fromLocal8Bit("����"));
            }            
            ui.label_9->setText(GlobalManager::getInstance()->_missileName);  //����          


		}
	}
}

//����ͼƬ�ı�ۺ���
void MultiControlSys::slot_pictureChange()
{
    ui.label_2->setPixmap(QPixmap("://MultiControlSys/res/missile.png"));
}
void MultiControlSys::closeEvent(QCloseEvent *event)      //��������رյ�һЩ����
{
    TCPClient::GetInstance()->SendMsgID(eMsg_T_OnCloseApp);
	GlobalManager::getInstance()->SaveIni();
}

void MultiControlSys::on_timeout()
{
	LogMgr* pLog = LogMgr::GetInstance();
	ui.lable_date->setText(pLog->GetCurrentDate());
	ui.lable_time->setText(pLog->GetCurrentTimeHMS());
}

void MultiControlSys::on_quit_clicked()
{
    TCPClient::GetInstance()->SendMsgID(eMsg_T_OnCloseApp);
	GlobalManager::getInstance()->SaveIni();
    exit(0);   //�ж��¼�ѭ��
}

    //�Զ�����
void MultiControlSys::on_btnauto_test_clicked()
{
    if(missiletype==1)
    {
        AutoTestDlg12A* dlg = new AutoTestDlg12A(ATT_AUTO);
        dlg->exec();
    }
    if(missiletype==2)
    {
        AutoTestDlg* dlg = new AutoTestDlg(ATT_AUTO);
        dlg->exec();
    }
}
    //ϵͳ�Լ�
void MultiControlSys::on_btnself_check_clicked()
{
    if(missiletype==1)
    {
        AutoTestDlg12A* dlg=new AutoTestDlg12A(ATT_SYS);
        dlg->exec();
    }
    if(missiletype==2)
    {
        AutoTestDlg* dlg=new AutoTestDlg(ATT_SYS);
        dlg->exec();
    }
}
     //���ݴ���
void MultiControlSys::on_btn_history_clicked()
{
	HistoryDlg* dlg = new HistoryDlg();
	dlg->exec();
}

void MultiControlSys::on_btnparam_clicked()
{
	GlobalManager::getInstance()->ShowButtonTip(this);
}

void MultiControlSys::on_btntest_clicked()
{
	GlobalManager::getInstance()->ShowButtonTip(this);
}

void MultiControlSys::on_btn_help_clicked()
{
	GlobalManager::getInstance()->ShowButtonTip(this);
}
