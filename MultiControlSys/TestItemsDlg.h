#pragma once

#include <QDialog>
#include "ui_TestItemsDlg.h"
//�Զ�����->������ԵĲ�����Ŀ��ѡ����� ���ݹ�ѡ�Ĳ�ͬ ������ͬdatatype��ITask
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
