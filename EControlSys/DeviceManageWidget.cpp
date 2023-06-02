#include "DeviceManageWidget.h"
#include <QSqlQuery>
#include <QDebug>
#include "GlobalManager.h"
#include "EditDeviceDlg.h"
DeviceManageWidget::DeviceManageWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget->setAlternatingRowColors(true);
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	InitTable();
	//connect
	connect(GlobalManager::getInstance(), SIGNAL(UpdateDeviceList()), this, SLOT(InitTable()));
}

DeviceManageWidget::~DeviceManageWidget()
{
}

void DeviceManageWidget::EditItem(int devid)
{
	EditDeviceDlg dlg(devid);
	if (dlg.exec() == QDialog::Accepted)
	{
		//更新界面
		InitTable();
	}
}

void DeviceManageWidget::InitTable()
{
	QBrush bruship = QBrush(QColor(90, 90,255));
	QBrush brushop(QColor(83,158,216));

	int row = 0;
	QMap<int, DeviceOnline>::iterator it = GlobalManager::getInstance()->m_mapDeviceOnline.begin();
	while (it != GlobalManager::getInstance()->m_mapDeviceOnline.end())
	{
		DeviceOnline& dev = *it;
		int column = 0;
		ui.tableWidget->setRowCount(row + 1);

		QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row + 1));
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		item->setData(Qt::UserRole, it->heartcmd);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(dev.strIp);
		item->setForeground(bruship);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(dev.strName);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(dev.strMac);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		//QIcon ico = QIcon(str);
		//m_table->setItem(row, colum, new QTableWidgetItem(QIcon(str), text));'
		if (dev.state == ON_LINE)
		{
			item = new QTableWidgetItem(QIcon(":/EControlSys/res/green.png"), GlobalManager::getInstance()->ConvertOnlineString(dev.state));
		}
		else
			item = new QTableWidgetItem(QIcon(":/EControlSys/res/red.png"), GlobalManager::getInstance()->ConvertOnlineString(dev.state));
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(QString::fromLocal8Bit("编辑"));
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		item->setForeground(brushop);
		ui.tableWidget->setItem(row, column++, item);

		row++;
		it++;
	}

	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

void DeviceManageWidget::on_tableWidget_itemClicked(QTableWidgetItem* item)
{
	qDebug() << item->column();
	if (item->column() == 5)
	{
		//详情
		int devid = ui.tableWidget->item(item->row(), 0)->data(Qt::UserRole).toInt();
		EditItem(devid);
	}
}
