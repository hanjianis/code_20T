#pragma once

#include <QDialog>
#include "ui_MessageBoxDlg.h"
//��ʾ���� ������ϵͳ���� ��Ҫ����Ҫ��ʾ������
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
