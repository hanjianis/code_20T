#pragma once

#include <QDialog>
#include "ui_LoginDlg.h"
//µÇÂ¼½çÃæ 
class LoginDlg : public QDialog
{
	Q_OBJECT

public:
	LoginDlg(QWidget *parent = Q_NULLPTR);
	~LoginDlg();

private:
	Ui::LoginDlg ui;
	int _InitID;
public:
	virtual void timerEvent(QTimerEvent *event);
public slots:
	void on_btnok_clicked();

 signals:
    void sig_pictureChange();


};
