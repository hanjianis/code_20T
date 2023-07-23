#include "MultiControlSys.h"
#include "LogMgr.h"
#include "AutoTestDlg.h"
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

   // QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();?????
   // move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
	//showMaximized();
    move(0,0);
    //setWindowFlags (Qt::Window | Qt::FramelessWindowHint);
//	ui.label_3->setMargin((rc.width() - ui.label_3->geometry().width()) / 2);
    //border-image: url(:/MultiControlSys/res/timg.jpg);
    ui.label_2->setPixmap(QPixmap(":/MultiControlSys/res/timg.jpg"));


}

void MultiControlSys::timerEvent(QTimerEvent *event)
{
	int tmid = event->timerId();
	if (tmid == _LoginId)
	{
		killTimer(tmid);
		LoginDlg dlg;
        connect(&dlg,&LoginDlg::sig_pictureChange,this,&MultiControlSys::slot_pictureChange);
        if (dlg.exec() == QDialog::Accepted)   //显示登陆界面
		{
			ui.btnparam->setEnabled(true);
            ui.btntest->setEnabled(false);
			ui.btnself_check->setEnabled(true);
			ui.btnauto_test->setEnabled(true);
			ui.btn_history->setEnabled(true);
			ui.btn_manage->setEnabled(false);
			ui.btn_qiangding->setEnabled(false);
			//????????????????????
            ui.label_7->setText(QString::fromLocal8Bit("战斗弹"));
            ui.label_9->setText(GlobalManager::getInstance()->_missileName);  //弹号          


		}
	}
}

//界面图片改变槽函数
void MultiControlSys::slot_pictureChange()
{
    ui.label_2->setPixmap(QPixmap("://MultiControlSys/res/missile.png"));
}
void MultiControlSys::closeEvent(QCloseEvent *event)      //顶级窗体关闭的一些设置
{
//	TCPClient::GetInstance()->SendMsgID(eMsg_T_OnCloseApp);
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
    //TCPClient::GetInstance()->SendMsgID(eMsg_T_OnCloseApp);
	GlobalManager::getInstance()->SaveIni();
    exit(0);   //中断事件循环
}

    //自动测试
void MultiControlSys::on_btnauto_test_clicked()
{
	AutoTestDlg* dlg = new AutoTestDlg(ATT_AUTO);
	dlg->exec();
}
    //系统自检
void MultiControlSys::on_btnself_check_clicked()
{
	AutoTestDlg* dlg=new AutoTestDlg(ATT_SYS);
	dlg->exec();
}
     //数据处理
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
