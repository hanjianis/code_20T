#include "LogMgr.h"
#include <QDateTime>
LogMgr* LogMgr::m_pInstance = nullptr;
LogMgr::LogMgr(QObject *parent)
	: QObject(parent)
{
}

LogMgr::~LogMgr()
{
}
LogMgr* LogMgr::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new LogMgr(nullptr);
	}
	return m_pInstance;
}
void LogMgr::AddLog(QString str)
{
	emit AddLogSignal(str);
}

void LogMgr::AddWarningLog(QString str)
{
	emit AddWarningLogSignal(str);
}

QString LogMgr::GetCurrentTimeString()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
	
	return current_date;
}

QString LogMgr::FormatFloatNum(float dt)
{
	QString str = QString::number(dt, 'f', 2);
	return str;
}
