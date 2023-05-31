#include "LogMgr.h"
#include <QDateTime>
#include <QDebug>
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
	qDebug() << str;
	emit AddLogSignal(str);
}

void LogMgr::AddWarningLog(QString str)
{
	emit AddWarningLogSignal(str);
}

QString LogMgr::GetCurrentTimeString()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyyMMddhhmmss");
	
	return current_date;
}

QString LogMgr::GetCurrentTimeHMS()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("hh:mm:ss");

	return current_date;
}

QString LogMgr::GetCurrentDate()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = QString::fromLocal8Bit("%1年%2月%3日")
		.arg(current_date_time.date().year(),4,10, QLatin1Char('0'))
		.arg(current_date_time.date().month(), 2, 10, QLatin1Char('0'))
		.arg(current_date_time.date().day(), 2, 10, QLatin1Char('0'));////current_date_time.toString("yyyy年MM月dd日");

	return current_date;
}

QString LogMgr::GetCurrentTm()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = QString::fromLocal8Bit("%1时%2分%3秒")
		.arg(current_date_time.time().hour(), 2, 10, QLatin1Char('0'))
		.arg(current_date_time.time().minute(), 2, 10, QLatin1Char('0'))
		.arg(current_date_time.time().second(), 2, 10, QLatin1Char('0'));////current_date_time.toString("yyyy年MM月dd日");

	return current_date;
}

QString LogMgr::FormatFloatNum(float dt)
{
	QString str = QString::number(dt, 'f', 2);
	return str;
}
