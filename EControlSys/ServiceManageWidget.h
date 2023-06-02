#pragma once

#include <QWidget>
#include "ui_ServiceManageWidget.h"

class ServiceManageWidget : public QWidget
{
	Q_OBJECT

public:
	ServiceManageWidget(QWidget *parent = Q_NULLPTR);
	~ServiceManageWidget();

private:
	Ui::ServiceManageWidget ui;
private:
	//к╫сп
	QString ConvertStateToString(int state);
	//
	QString ConvertStartToString(int state);
};
