#pragma once

#include <QDialog>
#include "ui_HistoryDlg.h"
#include <QTimer>
//��ʷ���ݴ������ 
//��ѯʱ �����ݿ��ѯ���� sqlite history_file
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
	void on_timeout();//���½����ϵ�ϵͳʱ��
	void on_query_clicked();//��ѯ��ť
	void on_quit_clicked();//���ذ�ť
	void on_checkBox_clicked();//ȫѡ��ť
	void on_btn_del_clicked();//ɾ���ļ�
	void on_printf_clicked();//��ӡ��ť
	//δʵ�ֵİ�ť
	void on_btn_close_clicked();//�رհ�ť
	void on_btn_open_clicked();//��
	void on_btn_compare_clicked();//�Ա�
	void on_btn_other_clicked();//����
	void on_btn_pailie_clicked();//����
	void on_btn_export_clicked();//����
	void on_btn_printf_clicked();//��ӡ
};
