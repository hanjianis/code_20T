#ifndef _ISYS_CHECK_ITEM_H_
#define _ISYS_CHECK_ITEM_H_
#pragma once
//系统自检项 单项测试里 一个下拉表就是一个
#include <QObject>
#include "UDPServer.h"
#include "XLManager.h"
#include <QTimer>
class ISysCheckItem : public QObject
{
	Q_OBJECT

public:
	ISysCheckItem(int datatype, QObject *parent);
	~ISysCheckItem();
public:
	int _datatype = 0;//数据类型
	int _lstindex = 0;
	int _stop;
	int _tmid;
	int _tmid_result;
    //int _tmid_mult_result;
	UDPServer* pUDPServer;
	XLManager* pXL;
	QTimer* m_tmCkOnline = nullptr;//检测心跳的    
public: 
	//开始检测
	virtual void StartCheck();//开始测试
	virtual void timerEvent(QTimerEvent *event);
	bool is_stop();//是否停止标识 主界面会不断检测该标识
	virtual void StopCheck();//结束测试
private:
	void ZHDY_Special();//综合电源的特殊处理
signals:
	void UpdateCheckResult(int datatype, int nId, float fVal);//更新测试结果
	void AddTaskItem(AutoTestData& data);//更新数据项
	void AddTaskItemResult(AutoTestData& data);//更新测试结果
/*
    void sig_reminderinformation1(QString);
    void sig_reminderinformation2(QString);
    void sig_reminderinformation3(QString);
    void sig_reminderinformation4(QString);
    void sig_reminderinformation5(QString);
    void sig_reminderinformation6(QString);
    */
    void sig_endTaskItem();  //测试结束
public slots:
	void CkOnlineTimeout();    
};
#endif
