#pragma once

#include <QDialog>
#include "ui_EditDeviceDlg.h"

class EditDeviceDlg : public QDialog
{
	Q_OBJECT

public:
	EditDeviceDlg(int devid,QWidget *parent = Q_NULLPTR);
	~EditDeviceDlg();

private:
	Ui::EditDeviceDlg ui;
	int m_devid;
public slots:
	void on_ok_clicked();
	void on_cancel_clicked();
};
