#include "InsConfigDlg.h"
#include "Packet.h"
#include <QDesktopWidget>
#include <QApplication>
#include "MyMessageBox.h"
#include "GlobalManager.h"
InsConfigDlg::InsConfigDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//设置经纬度 海拔高度
	GlobalManager* pGlobal = GlobalManager::getInstance();

	ui.lineEdit->setText(QString("%1").arg(pGlobal->_lat_degree));
	ui.lineEdit_2->setText(QString("%1").arg(pGlobal->_lat_sec));
	ui.lineEdit_3->setText(QString("%1").arg(pGlobal->_lon_degree));
	ui.lineEdit_4->setText(QString("%1").arg(pGlobal->_lon_sec));
	ui.lineEdit_5->setText(QString("%1").arg(pGlobal->_height));

	setWindowFlags(Qt::FramelessWindowHint);
	resize(DLG_WIDTH, DLG_HEIGHT);
	QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
	//move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
	move((WIDTH - this->width()) / 2, (desktop->height() - this->height()) / 2);
}

InsConfigDlg::~InsConfigDlg()
{
}

void InsConfigDlg::on_btnok_clicked()
{
	
	//设置到Global里
	GlobalManager* pGlobal = GlobalManager::getInstance();
	pGlobal->_lat_degree = ui.lineEdit->text().toInt();
	pGlobal->_lat_sec = ui.lineEdit_2->text().toFloat();
	pGlobal->_lon_degree = ui.lineEdit_3->text().toInt();
	pGlobal->_lon_sec = ui.lineEdit_4->text().toFloat();
	pGlobal->_height = ui.lineEdit_5->text().toInt();

	//二次确认
	QString str = QString::fromLocal8Bit("当前纬度:%1度%2分，经度:%3度%4分，海拔高度:%5米")
		.arg(pGlobal->_lat_degree)
		.arg(pGlobal->_lat_sec)
		.arg(pGlobal->_lon_degree)
		.arg(pGlobal->_lon_sec)
		.arg(pGlobal->_height);
	//QMessageBox::setStyleSheet("");
	/*if (QMessageBox::information(nullptr, QString::fromLocal8Bit("再次确认"), str, QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
	{

	}
	else
	{
		return;
	}*/
	MyMessageBox dlg(QString::fromLocal8Bit("再次确认"), str,this);
	if (dlg.exec() == QDialog::Rejected)
		return;
	QDialog::accept();
	close();
}
