#pragma once

#include <QDialog>
#include "ui_MyToolTipDlg.h"
//提示界面 ok按钮 需要传递标题 内容
class MyToolTipDlg : public QDialog
{
	Q_OBJECT

public:
	MyToolTipDlg(QString strTitle, QString content, QWidget *parent = Q_NULLPTR);
	~MyToolTipDlg();

private:
	Ui::MyToolTipDlg ui;
public slots:
	void on_pushButton_clicked();
};
