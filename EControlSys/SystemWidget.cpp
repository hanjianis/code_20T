#include "SystemWidget.h"
#include <QDebug>
#include "DeviceManageWidget.h"
#include "ServiceManageWidget.h"
#include "SubjectManageWidget.h"
#include "WeightManageWidget.h"
#include "UserManageWidget.h"
#include "VersionManageWidget.h"
SystemWidget::SystemWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(on_listwidget_itemClicked(QListWidgetItem *)));
	//ui.listWidget->clear();
	//QListWidgetItem* item = new QListWidgetItem(QString::fromLocal8Bit("�豸����"));
	//ui.listWidget->addItem(item);
	//item = new QListWidgetItem(QString::fromLocal8Bit("��Ŀ����"));
	//ui.listWidget->addItem(item);
	//�豸����
	QWidget* wd = new DeviceManageWidget(this);
	ui.horizontalLayout->addWidget(wd, 1);
	m_lstWidget.push_back(wd);
	//��Ŀ����
	wd = new SubjectManageWidget(this);
	ui.horizontalLayout->addWidget(wd, 1);
	m_lstWidget.push_back(wd);

	wd = new UserManageWidget(this);
	ui.horizontalLayout->addWidget(wd, 1);
	m_lstWidget.push_back(wd);

	wd = new WeightManageWidget(this);
	ui.horizontalLayout->addWidget(wd, 1);
	m_lstWidget.push_back(wd);

	wd = new VersionManageWidget(this);
	ui.horizontalLayout->addWidget(wd, 1);
	m_lstWidget.push_back(wd);

	wd = new ServiceManageWidget(this);
	ui.horizontalLayout->addWidget(wd, 1);
	m_lstWidget.push_back(wd);

	SetWdVisible(0);
}

SystemWidget::~SystemWidget()
{
}

void SystemWidget::SetWdVisible(int wdindex)
{
	if (wdindex > m_lstWidget.count())
		return;
	for (int i = 0; i < m_lstWidget.count(); i++)
		m_lstWidget[i]->setVisible(false);

	m_lstWidget[wdindex]->setVisible(true);
}

void SystemWidget::on_listwidget_itemClicked(QListWidgetItem *item)
{
	SetWdVisible(ui.listWidget->row(item));
}
