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
	//���������б�
	void UpdateTaskListSlot(TaskInfo& tsinfo);
	void on_replay_toolbutton_clicked();
	void on_list_toolbutton_clicked();
	void on_pushButton_clicked();//�����б�Ĳ�ѯ��ť
	void on_pushButton_2_clicked();//�����б�����ð�ť
	void on_pushButton_3_clicked();//�������̵Ĳ�ѯ��ť
	void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
	void on_tableWidget_itemClicked(QTableWidgetItem* item);
	void on_acDetail_triggered();
	void on_acStart_triggered();//��ʼ����
	void on_acStop_triggered();//��ֹ����
	void on_acPause_triggered();//��ͣ
	void on_acDelTask_triggered();//ɾ������
	void on_acEditTask_triggered();//�༭����
	void on_acReplay_triggered();
public:
	void refresh();
	void AddTaskLog(int msgid);
	void StopTask(QString task_id);
};
