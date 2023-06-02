#include "VersionManageWidget.h"
#include <QSqlQuery>
#include "GlobalManager.h"
VersionManageWidget::VersionManageWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget->setAlternatingRowColors(true);
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	InitTable();
	connect(GlobalManager::getInstance(), SIGNAL(UpdateDeviceList()), this, SLOT(InitTable()));
}

VersionManageWidget::~VersionManageWidget()
{
}
void VersionManageWidget::InitTable()
{

	QBrush bruship = QBrush(QColor(90, 90, 255));
	QBrush brushop(QColor(83, 158, 216));
	QString sql = QString("select * from version;");
	QSqlQuery query(sql);
	int row = 0;
	QMap<int, DeviceOnline>::iterator it = GlobalManager::getInstance()->m_mapDeviceOnline.begin();
	while (it != GlobalManager::getInstance()->m_mapDeviceOnline.end())
	{
		DeviceOnline dev = *it;
	
		int column = 0;
		ui.tableWidget->setRowCount(row + 1);

		QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row + 1));
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);


		item = new QTableWidgetItem(dev.strIp);
		item->setForeground(bruship);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(dev.strName);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(dev.strVer);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		item = new QTableWidgetItem(dev.strTm);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(row, column++, item);

		//item = new QTableWidgetItem(QString::fromLocal8Bit("±à¼­"));
		//item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		//item->setForeground(brushop);
		//ui.tableWidget->setItem(row, column++, item);


		row++;
		it++;
	}

	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}
		
