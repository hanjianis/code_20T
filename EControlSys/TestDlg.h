#pragma once

#include <QDialog>
#include "ui_TestDlg.h"

class TestDlg : public QDialog
{
	Q_OBJECT

public:
	TestDlg(QWidget *parent = Q_NULLPTR);
	~TestDlg();

private:
	Ui::TestDlg ui;
};
