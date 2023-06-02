#pragma once

#include <QWidget>
#include "ui_SubjectManageWidget.h"

class SubjectManageWidget : public QWidget
{
	Q_OBJECT

public:
	SubjectManageWidget(QWidget *parent = Q_NULLPTR);
	~SubjectManageWidget();

	void InitTable();
private:
	Ui::SubjectManageWidget ui;
public slots:
	void on_tableWidget_itemClicked(QTableWidgetItem* item);
};
