#ifndef INTEGRATEDTESTING_H
#define INTEGRATEDTESTING_H


#pragma once
//自动检查
#include <QObject>
#include "UDPServer.h"
#include "XLManager.h"
#include <QTimer>

class IntegratedTesting : public QObject
{
    Q_OBJECT
public:
    IntegratedTesting(int datatype, QObject *parent);
    ~IntegratedTesting();

public:
    int _datatype = 0;//数据类型
    int _lstindex = 0;
    int _stop;
    int _tmid;
    int _tmid_result;
   // int _tmid_mult_result;
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
    void sig_showAutoTestWidget();  //显示下面表格
    void sig_showAutoTestWidget1();  //取消显示下面表格
    void sig_endTaskItem();  //测试结束

public slots:
    void CkOnlineTimeout();

};

#endif // INTEGRATEDTESTING_H



