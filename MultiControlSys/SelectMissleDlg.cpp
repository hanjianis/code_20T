#include "SelectMissleDlg.h"
#include "Packet.h"
#include <QDesktopWidget>
#include "GlobalManager.h"
#include "TCPClient.h"
SelectMissleDlg::SelectMissleDlg(QWidget *parent)
	: QDialog(parent)
{    
    //showFullScreen();
	ui.setupUi(this);
    //ui.comboBox->setCurrentIndex(5);//直接选择最后一个20BD
    setWindowFlags(Qt::FramelessWindowHint);// (Qt::CustomizeWindowHint);
    resize(WIDTH, HEIGHT);


    //setWindowFlags (Qt::Window);
    //showFullScreen ();


	QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
	
    move(0,0);




    //设置颜色
   // QPalette pa;
   // pa.setColor(QPalette::WindowText,Qt::Key_Blue);
  //  ui.label_2->setPalette(pa);





  ///  ui.label_2->setStyleSheet("color:#191970;"); // 代码简单
  //  ui.label_2->setText(QString::fromLocal8Bit("中国航天科工集团第三研究院总体设计部研制"));
    //设置字号
 //   QFont ft;
 //   ft.setPointSize(100);
   // ui.label_2->setFont(ft);

}

SelectMissleDlg::~SelectMissleDlg()
{
}

void SelectMissleDlg::on_pushButton_clicked()
{
//	TCPClient::GetInstance()->SendMsgID(eMsg_T_OnSelectMissileType);
    if (ui.comboBox->currentIndex() == 4)//等于最后一个
	{
		//文本内容设置成k/akd20 视频上这么写的

        GlobalManager::getInstance()->_missileType = QString("YJ-12");
        QDialog::accept();   //窗口隐藏
        close();
	}
	else
		GlobalManager::getInstance()->_missileType = ui.comboBox->currentText();


}

void SelectMissleDlg::on_quit_clicked()
{
	close();
}

void SelectMissleDlg::on_pushButton_3_clicked()
{
	//关机 shutdown
}
