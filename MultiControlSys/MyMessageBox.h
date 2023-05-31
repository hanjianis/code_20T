#pragma once

#include <QDialog>
#include "ui_MyMessageBox.h"
//��ʾ���� �ޱ��� yes no��ť ��Ҫ���ݱ��� ����
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
