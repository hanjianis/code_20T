#pragma once

#include <QDialog>
#include "ui_HistoryDlg.h"
#include <QTimer>
//历史数据处理界面 
//查询时 从数据库查询所有 sqlite history_file
class HistoryDlg : public QDialog
{
	Q_OBJECT

public:
	HistoryDlg(QWidget *parent = Q_NULLPTR);
	~HistoryDlg();

private:
	Ui::HistoryDlg ui;
	QTimer* m_tmTimer;
	void QueryAll();
public slots:
	void on_timeout();//更新界面上的系统时间
	void on_query_clicked();//查询按钮
	void on_quit_clicked();//返回按钮
	void on_checkBox_clicked();//全选按钮
	void on_btn_del_clicked();//删除文件
	void on_printf_clicked();//打印按钮
	//未实现的按钮
	void on_btn_close_clicked();//关闭按钮
	void on_btn_open_clicked();//打开
	void on_btn_compare_clicked();//对比
	void on_btn_other_clicked();//其他
	void on_btn_pailie_clicked();//排列
	void on_btn_export_clicked();//导出
	void on_btn_printf_clicked();//打印
};
