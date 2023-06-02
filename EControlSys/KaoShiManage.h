#pragma once

#include <QWidget>
#include "ui_KaoShiManage.h"

class KaoShiManage : public QWidget
{
	Q_OBJECT

public:
	KaoShiManage(QWidget *parent = Q_NULLPTR);
	~KaoShiManage();

	void CreateMenus();
private:
	Ui::KaoShiManage ui;
	void InitTable();
public:
	void refresh();
public slots:
	void on_acDetail_triggered();
	void on_acStart_triggered();//开始任务
	void on_acStop_triggered();//终止任务
	void on_acPause_triggered();//暂停
	void on_acDelTask_triggered();//删除任务
	void on_acEditTask_triggered();//编辑任务
	void on_acReplay_triggered();
	void on_acTeacherScore_triggered();//教师打分
	void on_tableWidget_itemClicked(QTableWidgetItem* item);
	void on_query_clicked();
};
