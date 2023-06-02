#include "EditDeviceDlg.h"
#include "GlobalManager.h"
#include <QSqlQuery>
EditDeviceDlg::EditDeviceDlg(int devid, QWidget *parent)
	: QDialog(parent)
{
	m_devid = devid;
	ui.setupUi(this);
	QMap<int, DeviceOnline>::iterator it = GlobalManager::getInstance()->m_mapDeviceOnline.find(m_devid);
	if (it != GlobalManager::getInstance()->m_mapDeviceOnline.end())
	{
		ui.lineEdit->setText(it->strIp);
		ui.lineEdit_2->setText(it->strName);
		ui.lineEdit_3->setText(it->strMac);
		ui.lineEdit_4->setText(it->strVer);
	}
	
}

EditDeviceDlg::~EditDeviceDlg()
{
}

void EditDeviceDlg::on_ok_clicked()
{
	//
	QMap<int, DeviceOnline>::iterator it = GlobalManager::getInstance()->m_mapDeviceOnline.find(m_devid);
	if (it != GlobalManager::getInstance()->m_mapDeviceOnline.end())
	{
		it->strIp = ui.lineEdit->text();
		it->strName = ui.lineEdit_2->text();
		it->strMac = ui.lineEdit_3->text();
		it->strVer = ui.lineEdit_4->text();
	}
	else
	{
		GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("设备不存在！！！"));
		return;
	}
	//更新数据库
	QString sql = QString("update device set ip='%1',name='%2',mac='%3',version='%4' where port='%5';")
		.arg(it->strIp).arg(it->strName).arg(it->strMac).arg(it->strVer).arg(m_devid);
	QSqlQuery query;
	if (query.exec(sql))
	{
		GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("修改成功！！！"));
	
	}
	else
	{
		GlobalManager::getInstance()->ShowMessageBox(QString::fromLocal8Bit("修改失败！！！"));
	}

	QDialog::accept();
	close();
}

void EditDeviceDlg::on_cancel_clicked()
{
	QDialog::reject();
	close();
}
