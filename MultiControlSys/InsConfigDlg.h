#pragma once

#include <QDialog>
#include "ui_InsConfigDlg.h"
//�ߵ���γ�Ⱥ��θ߶� ���ý���
//��globalmanager��ȡ ������
class InsConfigDlg : public QDialog
{
	Q_OBJECT

public:
	InsConfigDlg(QWidget *parent = Q_NULLPTR);
	~InsConfigDlg();

private:
	Ui::InsConfigDlg ui;
public slots:
	void on_btnok_clicked();
};
