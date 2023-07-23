#include "SelectMissleDlg.h"
#include "Packet.h"
#include <QDesktopWidget>
#include "GlobalManager.h"
#include "TCPClient.h"

int missiletype;
SelectMissleDlg::SelectMissleDlg(QWidget *parent)
	: QDialog(parent)
{    
    //showFullScreen();
	ui.setupUi(this);
    //ui.comboBox->setCurrentIndex(5);//ֱ��ѡ�����һ��20BD
    setWindowFlags(Qt::FramelessWindowHint);// (Qt::CustomizeWindowHint);
    resize(WIDTH, HEIGHT);


    //setWindowFlags (Qt::Window);
    //showFullScreen ();


	QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();Ҳ����
	
    move(0,0);




    //������ɫ
   // QPalette pa;
   // pa.setColor(QPalette::WindowText,Qt::Key_Blue);
  //  ui.label_2->setPalette(pa);





  ///  ui.label_2->setStyleSheet("color:#191970;"); // �����
  //  ui.label_2->setText(QString::fromLocal8Bit("�й�����ƹ����ŵ����о�Ժ������Ʋ�����"));
    //�����ֺ�
 //   QFont ft;
 //   ft.setPointSize(100);
   // ui.label_2->setFont(ft);

}

SelectMissleDlg::~SelectMissleDlg()
{
}

void SelectMissleDlg::on_pushButton_clicked()
{
    TCPClient::GetInstance()->SendMsgID(eMsg_T_OnSelectMissileType);
    if (ui.comboBox->currentIndex() == 4)//�������һ��
	{
        /*
        if (PLCManager::getInstance()->ConnectPLC() == true)
        {
            PLCManager::getInstance()->SetDQ12AStart();
           // DQ_PLCManager12A::getInstance()->SetDQ20TStart();
        }
        */
        missiletype=1;
        //�ı��������ó�12A ��Ƶ����ôд��
        GlobalManager::getInstance()->_missileType = QString("YJ-12");
        QDialog::accept();   //��������
        close();


    } else if (ui.comboBox->currentIndex() == 3)//�������һ��
    {
        /*
        if (PLCManager::getInstance()->ConnectPLC() == true)
        {
            PLCManager::getInstance()->SetDQ20TStart();
           // DQ_PLCManager12A::getInstance()->SetDQ20TStart();
        }
        */
        missiletype=2;
        //�ı��������ó�k/akd20 ��Ƶ����ôд��
        GlobalManager::getInstance()->_missileType = QString("K/AKD20");
        QDialog::accept();   //��������
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
	//�ػ� shutdown
}
