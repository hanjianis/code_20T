#pragma once

#include <QDialog>
#include "ui_SelectUserDlg.h"

class SelectUserDlg : public QDialog
{
	Q_OBJECT

public:
	SelectUserDlg(QWidget *parent = Q_NULLPTR);
	~SelectUserDlg();

	void InitTable(QString sql);
	void InitCombox();
private:
	Ui::SelectUserDlg ui;
signals:
	void AddUserList(QString str);
public slots:
	void on_all_clicked();
	void on_ok_clicked();
	void on_cancel_clicked();
	void on_comboBox_currentTextChanged(const QString &);
};
