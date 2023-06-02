#pragma once

#include <QDialog>
#include "ui_EditTaskDlg.h"
#include "GlobalManager.h"
#include "Packet.h"
class EditTaskDlg : public QDialog
{
	Q_OBJECT

public:
	EditTaskDlg(QWidget *parent = Q_NULLPTR);
	~EditTaskDlg();

private:
	Ui::EditTaskDlg ui;
public:
	TaskInfo m_curTask;
public slots:
	void on_ok_clicked();
	void on_cancel_clicked();
	void on_select_btn_clicked();
	//
	void AddUserListSlot(QString str);
public:
	void SetCurTask(TaskInfo& curTask);
};
