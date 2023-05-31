#pragma once

#include <QDialog>
#include "ui_InsConfigDlg.h"
//惯导经纬度海拔高度 配置界面
//从globalmanager获取 并更新
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
