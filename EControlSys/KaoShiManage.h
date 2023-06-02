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
	void on_acStart_triggered();//��ʼ����
	void on_acStop_triggered();//��ֹ����
	void on_acPause_triggered();//��ͣ
	void on_acDelTask_triggered();//ɾ������
	void on_acEditTask_triggered();//�༭����
	void on_acReplay_triggered();
	void on_acTeacherScore_triggered();//��ʦ���
	void on_tableWidget_itemClicked(QTableWidgetItem* item);
	void on_query_clicked();
};
