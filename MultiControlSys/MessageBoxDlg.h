#pragma once

#include <QDialog>
#include "ui_MessageBoxDlg.h"
//提示界面 背景是系统背景 需要传递要显示的内容
class MessageBoxDlg : public QDialog
{
	Q_OBJECT

public:
	MessageBoxDlg(QString str, QWidget *parent = Q_NULLPTR);
	~MessageBoxDlg();

private:
	Ui::MessageBoxDlg ui;
public slots:
	void on_pushButton_clicked();
};
