#pragma once

#include <QDialog>
#include "ui_MyMessageBox.h"
//提示界面 无背景 yes no按钮 需要传递标题 内容
class MyMessageBox : public QDialog
{
	Q_OBJECT

public:
	MyMessageBox(QString title, QString content, QWidget *parent = Q_NULLPTR);
	~MyMessageBox();

private:
	Ui::MyMessageBox ui;
public slots:
	void on_btnyes_clicked();
	void on_btnno_clicked();
};
