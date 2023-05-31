#pragma once

#include <QDialog>
#include "ui_MakeSureDlg.h"
//确定对话框
class MakeSureDlg : public QDialog
{
	Q_OBJECT

public:
	MakeSureDlg(QWidget *parent = Q_NULLPTR);
	~MakeSureDlg();

private:
	Ui::MakeSureDlg ui;
public slots:
	void on_ok_clicked();
	void on_cancel_clicked();
};
