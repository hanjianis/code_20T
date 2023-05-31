#pragma once

#include <QDialog>
#include "ui_InputTemperatureDlg.h"
//输入温度的界面
class InputTemperatureDlg : public QDialog
{
	Q_OBJECT

public:
	InputTemperatureDlg(QWidget *parent = Q_NULLPTR);
	~InputTemperatureDlg();

private:
	Ui::InputTemperatureDlg ui;
public slots:
	void on_pushButton_clicked();
};
