#include "LoginDlg.h"
#include "MakeSureDlg.h"
#include "Packet.h"
#include <QDesktopWidget>
#include "GlobalManager.h"
#include "TCPClient.h"
LoginDlg::LoginDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	resize(DLG_WIDTH, DLG_HEIGHT);
	QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
	
	move((WIDTH - this->width()) / 2, (desktop->height() - this->height()) / 2);

    if(missiletype==1)
    {
        ui.comboBox->setCurrentIndex(0);
    }
    if(missiletype==2)
    {
        ui.comboBox->setCurrentIndex(4);
    }
}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::timerEvent(QTimerEvent *event)
{
	int tmid = event->timerId();
	if (tmid == _InitID)
	{
		killTimer(tmid);
		QDialog::accept();
		close();
	}
}

void LoginDlg::on_btnok_clicked()
{    

    if(ui.comboBox->currentIndex()==0||ui.comboBox->currentIndex()==4)
    {

    }else{
        return;
    }
    TCPClient::GetInstance()->SendMsgID(eMsg_T_OnInputDCCode);
	GlobalManager::getInstance()->_user = ui.lineEdit->text();
	GlobalManager::getInstance()->_missileName = ui.lineEdit_3->text();
	MakeSureDlg dlg;
    if (dlg.exec() == QDialog::Accepted)  //dlg打开
	{
		//初始化设备
		ui.btnok->setEnabled(false);
		ui.btncancel->setEnabled(false);
		_InitID = startTimer(2000);
		ui.tips->setText(QString::fromLocal8Bit("正在初始化设备，请稍后......"));
        emit sig_pictureChange();         //发射改变界面图片的信号
	}
}
