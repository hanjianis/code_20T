#pragma once

#include <QDialog>
#include "ui_TaskDetailDlg.h"

class TaskDetailDlg : public QDialog
{
	Q_OBJECT

public:
	TaskDetailDlg(QString task_id,QWidget *parent = Q_NULLPTR);
	~TaskDetailDlg();

private:
	Ui::TaskDetailDlg ui;
	QString _task_id;
	void InitTable();
public slots:
	void on_toolButton_clicked();
public:
	virtual bool eventFilter(QObject *obj, QEvent *event);
};
