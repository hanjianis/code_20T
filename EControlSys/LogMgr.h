#pragma once

#include <QObject>
#include <string>
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
	QString FormatFloatNum(float dt);
signals:
	void AddLogSignal(QString str);
	void AddWarningLogSignal(QString str);
};
