#pragma once

#include <QWidget>
#include "ui_UserManageWidget.h"

class UserManageWidget : public QWidget
{
	Q_OBJECT

public:
	UserManageWidget(QWidget *parent = Q_NULLPTR);
	~UserManageWidget();

	void InitTable(QString sql);
private:
	Ui::UserManageWidget ui;
public slots:
	void on_query_clicked();
	void on_reset_clicked();
};
