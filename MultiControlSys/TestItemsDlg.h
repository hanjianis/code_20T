#pragma once

#include <QDialog>
#include "ui_TestItemsDlg.h"
//自动测试->单项测试的测试项目的选择界面 根据勾选的不同 创建不同datatype的ITask
class TestItemsDlg : public QDialog
{
	Q_OBJECT

public:
	TestItemsDlg(QWidget *parent = Q_NULLPTR);
	~TestItemsDlg();

private:
	Ui::TestItemsDlg ui;
	QWidget* m_parent;
	void AddTask(int param1);
public slots:
	void on_btnok_clicked();
	void on_all_clicked();
};
