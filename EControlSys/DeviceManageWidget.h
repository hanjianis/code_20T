#pragma once

#include <QWidget>
#include "ui_DeviceManageWidget.h"

class DeviceManageWidget : public QWidget
{
	Q_OBJECT

public:
	DeviceManageWidget(QWidget *parent = Q_NULLPTR);
	~DeviceManageWidget();

private:
	Ui::DeviceManageWidget ui;
private: 
	void EditItem(int devid);
public slots:
	void InitTable();
	void on_tableWidget_itemClicked(QTableWidgetItem* item);
};
