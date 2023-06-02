#pragma once

#include <QWidget>
#include "ui_VersionManageWidget.h"

class VersionManageWidget : public QWidget
{
	Q_OBJECT

public:
	VersionManageWidget(QWidget *parent = Q_NULLPTR);
	~VersionManageWidget();
public slots:
	void InitTable();
private:
	Ui::VersionManageWidget ui;
};
