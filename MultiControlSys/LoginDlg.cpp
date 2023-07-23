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
	QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();Ҳ����
	
	move((WIDTH - this->width()) / 2, (desktop->height() - this->height()) / 2);
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
    if(ui.comboBox->currentIndex()==0)
    {

    }else{
        return;
    }
    //TCPClient::GetInstance()->SendMsgID(eMsg_T_OnInputDCCode);
	GlobalManager::getInstance()->_user = ui.lineEdit->text();
	GlobalManager::getInstance()->_missileName = ui.lineEdit_3->text();
	MakeSureDlg dlg;
    if (dlg.exec() == QDialog::Accepted)  //dlg��
	{
		//��ʼ���豸
		ui.btnok->setEnabled(false);
		ui.btncancel->setEnabled(false);
		_InitID = startTimer(2000);
		ui.tips->setText(QString::fromLocal8Bit("���ڳ�ʼ���豸�����Ժ�......"));
        emit sig_pictureChange();         //����ı����ͼƬ���ź�
	}
}
