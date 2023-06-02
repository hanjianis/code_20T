#ifndef _DEVICE_ONLINE_ITEM_WIDGET_H_
#define _DEVICE_ONLINE_ITEM_WIDGET_H_
#pragma once

#include <QWidget>
#include "ui_DeviceOnlineItemWidget.h"
#include "Packet.h"
class DeviceOnlineItemWidget : public QWidget
{
	Q_OBJECT

public:
	DeviceOnlineItemWidget(DeviceOnline& device,QWidget *parent = Q_NULLPTR);
	~DeviceOnlineItemWidget();

private:
	Ui::DeviceOnlineItemWidget ui;
	int m_devicePort;
public slots:
	void UpdateDeviceOnlineSlot();
};
#endif