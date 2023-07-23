#pragma once

#include <QDialog>
#include "ui_SelectMissleDlg.h"
#include "DeviceMgr/PLCManager.h"

//ѡ�񵯺Ž��� �������
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
	void on_quit_clicked();//�˳����
	void on_pushButton_3_clicked();//�ػ�

signals:
   // void sig_missiletype();
};
