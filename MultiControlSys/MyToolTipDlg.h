#pragma once

#include <QDialog>
#include "ui_MyToolTipDlg.h"
//��ʾ���� ok��ť ��Ҫ���ݱ��� ����
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
