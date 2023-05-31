#pragma once

#include <QObject>
#include <string>
//日志单体 处理日志 (目前无用)
//处理一些时间格式
using namespace std;
class LogMgr : public QObject
{
	Q_OBJECT

public:
	LogMgr(QObject *parent);
	~LogMgr();
	static LogMgr* m_pInstance;
	
public:
	//单体实例获取方法 唯一的对象指针
	static LogMgr* GetInstance();
public:
	void AddLog(QString str);
	void AddWarningLog(QString str);
	QString GetCurrentTimeString();
	QString GetCurrentTimeHMS();
	QString GetCurrentDate();
	QString GetCurrentTm();//时分秒
	QString FormatFloatNum(float dt);
signals:
	void AddLogSignal(QString str);
	void AddWarningLogSignal(QString str);
};
