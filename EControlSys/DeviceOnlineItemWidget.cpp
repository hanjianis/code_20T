#include "DeviceOnlineItemWidget.h"
#include "GlobalManager.h"
DeviceOnlineItemWidget::DeviceOnlineItemWidget(DeviceOnline& device, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_devicePort = device.port;
	ui.label_3->setText(device.strName);
	//setStyleSheet(QString::fromUtf8("image: url(:/EControlSys/res/red.png);"));
	if (device.state == ON_LINE)
	{
		ui.label_2->setStyleSheet(QString::fromUtf8("image: url(:/EControlSys/res/green.png);"));
	}
	else
		ui.label_2->setStyleSheet(QString::fromUtf8("image: url(:/EControlSys/res/red.png);"));

	connect(GlobalManager::getInstance(), SIGNAL(UpdateDeviceList()), this, SLOT(UpdateDeviceOnlineSlot()));
}

DeviceOnlineItemWidget::~DeviceOnlineItemWidget()
{
}

void DeviceOnlineItemWidget::UpdateDeviceOnlineSlot()
{
	QMap<int, DeviceOnline>::iterator it = GlobalManager::getInstance()->m_mapDeviceOnline.find(m_devicePort);//key Éè±¸¶Ë¿Ú
	if (it != GlobalManager::getInstance()->m_mapDeviceOnline.end())
	{
		if (it->state == ON_LINE)
		{
			ui.label_2->setStyleSheet(QString::fromUtf8("image: url(:/EControlSys/res/green.png);"));
		}
		else
			ui.label_2->setStyleSheet(QString::fromUtf8("image: url(:/EControlSys/res/red.png);"));
	}
}
