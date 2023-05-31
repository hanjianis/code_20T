#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MultiControlSys.h"
#include <QTimer>
#include "TCPClient.h"
//主界面
class MultiControlSys : public QMainWindow
{
    Q_OBJECT

public:
    MultiControlSys(QWidget *parent = Q_NULLPTR);

private:
    Ui::MultiControlSysClass ui;
	QTimer* m_tmTimer;
	int _LoginId;

public:
	virtual void timerEvent(QTimerEvent *event);
	virtual void closeEvent(QCloseEvent *event);
public slots:
	void on_timeout();
    void on_quit_clicked();//退出
	void on_btnauto_test_clicked();//自动测试
			
	void on_btnself_check_clicked();//自检
	void on_btn_history_clicked();//数据处理
	//
	void on_btnparam_clicked();
	void on_btntest_clicked();
	void on_btn_help_clicked();
    void slot_pictureChange();
	
};
