#include "ServiceManageWidget.h"
#include "GlobalManager.h"
#include <QDebug>
#include "QSwitchButton.h"
ServiceManageWidget::ServiceManageWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//ui.tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget_2->setAlternatingRowColors(true);
	//初始化
	int row = 0;
	int column = 0;
	QMap<int, SysService>::iterator it = GlobalManager::getInstance()->m_mapSysService.begin();
	while (it != GlobalManager::getInstance()->m_mapSysService.end())
	{

		column = 0;
		//ui.tableWidget_2->insertRow(0);
		row = ui.tableWidget_2->rowCount();
		ui.tableWidget_2->setRowCount(row+1);

		QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row + 1));
		
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget_2->setItem(row, column++, item);

		item = new QTableWidgetItem(it->sys_name);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget_2->setItem(row, column++, item);

		if (it->state == ON_LINE)
		{
			item = new QTableWidgetItem(QIcon(":/EControlSys/res/green.png"), ConvertStateToString(it->state));
		}
		else
			item = new QTableWidgetItem(QIcon(":/EControlSys/res/red.png"), ConvertStateToString(it->state));
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget_2->setItem(row, column++, item);

		
		SwitchButton* btn = new  SwitchButton(this);
		btn->setChecked(it->start);
		ui.tableWidget_2->setCellWidget(row, column++, btn);

		
		it++;
	}
}

ServiceManageWidget::~ServiceManageWidget()
{
}
//int state;//状态 1：正常 0：离线

QString ServiceManageWidget::ConvertStateToString(int state)
{
	QString str;
	if (state == 0)
		str = QString::fromLocal8Bit("禁用");
	if (state == 1)
		str = QString::fromLocal8Bit("启用");
	return str;
}
//int start;//启停用 1：启用 0：停用
QString ServiceManageWidget::ConvertStartToString(int state)
{
	QString str;
	if (state == 0)
		str = QString::fromLocal8Bit("停用");
	if (state == 1)
		str = QString::fromLocal8Bit("启用");
	return str;
}
