#pragma once

#include <QObject>
#include <string>
//��־���� ������־ (Ŀǰ����)
//����һЩʱ���ʽ
using namespace std;
class LogMgr : public QObject
{
	Q_OBJECT

public:
	LogMgr(QObject *parent);
	~LogMgr();
	static LogMgr* m_pInstance;
	
public:
	//����ʵ����ȡ���� Ψһ�Ķ���ָ��
	static LogMgr* GetInstance();
public:
	void AddLog(QString str);
	void AddWarningLog(QString str);
	QString GetCurrentTimeString();
	QString GetCurrentTimeHMS();
	QString GetCurrentDate();
	QString GetCurrentTm();//ʱ����
	QString FormatFloatNum(float dt);
signals:
	void AddLogSignal(QString str);
	void AddWarningLogSignal(QString str);
};
