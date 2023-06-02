#pragma once

#include <QDialog>
#include "ui_PlanThinkDlg.h"

class PlanThinkDlg : public QDialog
{
	Q_OBJECT

public:
	PlanThinkDlg(QWidget *parent = Q_NULLPTR);
	~PlanThinkDlg();

private:
	Ui::PlanThinkDlg ui;
	void AddThinkPlan();
	void AddTask();
public slots:
	void on_select_btn_clicked();
	void on_ok_clicked();
	void on_cancel_clicked();
	void initSubjects();
	//
	void AddUserListSlot(QString str);
};
