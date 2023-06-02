#pragma once

#include <QWidget>
#include "ui_ControlWidget.h"
#include "Packet.h"
class ControlWidget : public QWidget
{
	Q_OBJECT

public:
	ControlWidget(QWidget *parent = Q_NULLPTR);
	~ControlWidget();

private:
	Ui::ControlWidget ui;
	bool m_bUpOrDown;
	void InitTable();
	void InitTable(QString sql);
	void InitTable2(QString sql);
	void CreateMenus();
	void AddTableWidget(TaskInfo tsinfo);
	void InitUI();
public slots:
	void sortTableByCol(int col);
	//更新任务列表
	void UpdateTaskListSlot(TaskInfo& tsinfo);
	void on_replay_toolbutton_clicked();
	void on_list_toolbutton_clicked();
	void on_pushButton_clicked();//任务列表的查询按钮
	void on_pushButton_2_clicked();//任务列表的重置按钮
	void on_pushButton_3_clicked();//操作回盘的查询按钮
	void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
	void on_tableWidget_itemClicked(QTableWidgetItem* item);
	void on_acDetail_triggered();
	void on_acStart_triggered();//开始任务
	void on_acStop_triggered();//终止任务
	void on_acPause_triggered();//暂停
	void on_acDelTask_triggered();//删除任务
	void on_acEditTask_triggered();//编辑任务
	void on_acReplay_triggered();
public:
	void refresh();
	void AddTaskLog(int msgid);
	void StopTask(QString task_id);
};
