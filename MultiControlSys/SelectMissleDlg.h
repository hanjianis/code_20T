#pragma once

#include <QDialog>
#include "ui_SelectMissleDlg.h"
#include "DeviceMgr/PLCManager.h"

//选择弹号界面 整个入口
class SelectMissleDlg : public QDialog
{
	Q_OBJECT

public:
	SelectMissleDlg(QWidget *parent = Q_NULLPTR);
	~SelectMissleDlg();

private:
	Ui::SelectMissleDlg ui;
public slots:
	void on_pushButton_clicked();
	void on_quit_clicked();//退出软件
	void on_pushButton_3_clicked();//关机

signals:
   // void sig_missiletype();
};
