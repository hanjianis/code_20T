#ifndef AUTO_TEST_DLG_H_
#define  AUTO_TEST_DLG_H_
#pragma once

#include <QDialog>
#include "ui_AutoTestDlg.h"
#include "Packet.h"
#include "XLManager.h"
#include "ITask.h"
#include "TestItemsDlg.h"
#include "ExcelOperate.h"
#include "TCPClient.h"
#include "ISysCheckItem.h"
#include "UDPServer.h"
#include <QTimer>
#include "INSTestOBJ.h"
#include "AutoTestWidget.h"
#include "MultTestOBJ.h"
#include "integratedtesting.h"
#include "integratedtestdialog.h"
#include "IntegratedLowerDisplay.h"
class AutoTestDlg : public QDialog
{
	Q_OBJECT
public:
	AutoTestDlg(int nType, QWidget *parent = Q_NULLPTR);
	~AutoTestDlg();

private:
	Ui::AutoTestDlg ui;
	AutoTestWidget* m_at = nullptr;//下面数据栏widget
	int _type;
	int _tmid;//系统自检的定时器
	int _tmid_auto;//自动测试的定时器
	//

	INSTestOBJ* _insTest = nullptr;//惯导测试类 自己管理自己的逻辑
	MultTestOBJ* _multTest = nullptr;

	int _lstindex;//不用了
	int _startTickCount;//用于测试时 使用时间的更新
	int _correct_count = 0;//正确数量
	int _error_count = 0;// 错误数量
	int _datatype;//数据类型 用于测试时 不同测试单项的区分
	QList<ISysCheckItem*> _lstTaskDataType;//系统自检时 要自检的数据类型ID集合 
    QList<IntegratedTesting*> _lstTaskDataType1;//系统自检时 要自检的数据类型ID集合
	XLManager* pXL;//单体类 管理sqlite的数据 和一些公用配置
	TestItemsDlg* m_itemsdlg;//自动测试->单项测试的数据项选择对话框 TestItemDlg.ui
    IntegratedTestDialog* m_intergraeddialog;  //自动测试->综合测试的数据项选择对话框 IntegratedTestDialog.ui
    IntegratedLowerDisplay* m_integratedlowerdisplay;    //数据显示到78行出现下部的参数数据
	ExcelOperate* excelOperate;//excel的操作
	TCPClient* _tcpClient;//tcp client 用于和导调通信 单体类
	UDPServer* _udpServer;//udp server 单体类
	QTimer* m_tmTimer;//用于系统时间更新
	QTimer* m_tmTestUseTm;//用于测试使用时间
    QTimer* m_reminderinformation;  //数据显示前的提示信息
    QTimer* m_reminderinformation1;  //数据显示前的提示信息

    int _reminderinformation;
    int _reminderinformation1;


signals:
     void sig_reminderinformationupdate();
     void sig_reminderinformationupdate1();

public:
	virtual void timerEvent(QTimerEvent *event);//定时器的回调
public slots:
	void AddTableWidget(AutoTestData& atd);//添加数据项到tabelwidget 
	void AddAutoTestResult(AutoTestData& atd);//添加数据项结果到tabelwidget
    void on_quit_clicked();//返回
	void on_btnstart_clicked();//开始按钮
	void on_toolButton_2_clicked();//暂停
	void on_comboBox_currentIndexChanged(int index);//测试单元的选择
	void on_comboBox_2_currentIndexChanged(int index);//测试项目的选择
	void UpdateToolTip(QString str);//更新提示信息
	void RecvStopInsSlot();//惯导测试结束
	void RecvStopMultiSlot();//综合测试结束
	void on_testBtn_clicked();
	void on_testBtn2_clicked();
	void on_testBtn3_clicked();
	void on_testBtn4_clicked();
public slots:
	void UpdateCheckResultCK(int datatype, int nId, float fVal);//更新程控结果
	void on_timeout();//定时器回调
	void SetTestUseTm();//设置测试使用时间槽

public slots://子项目【大气测试中断】使用
	void DQ_Failed();
private:
	void MNLTDJC();//系统自检的方法
    void MNLTDJC1();//自动测试的方法
	void CreateExcel();//测试时生成报告
	void InsertSheet(AutoTestData atd);//添加一条到excel

	void updateResult();//更新结果

public slots:
    void slot_reminderinformation1();
    void slots_reminderinformation1();
    void slot_reminderinformation();
    void slots_reminderinformation();
    //显示下面的表格
    void slot_showAutoTestWidget();
    //取消显示下面的表格
    void slot_showAutoTestWidget1();
    //结束显示
    void slot_endTaskItem();
};
#endif
