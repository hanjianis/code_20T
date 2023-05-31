#ifndef _ISYS_CHECK_ITEM_H_
#define _ISYS_CHECK_ITEM_H_
#pragma once
//ϵͳ�Լ��� ��������� һ�����������һ��
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
	int _datatype = 0;//��������
	int _lstindex = 0;
	int _stop;
	int _tmid;
	int _tmid_result;
    //int _tmid_mult_result;
	UDPServer* pUDPServer;
	XLManager* pXL;
	QTimer* m_tmCkOnline = nullptr;//���������    
public: 
	//��ʼ���
	virtual void StartCheck();//��ʼ����
	virtual void timerEvent(QTimerEvent *event);
	bool is_stop();//�Ƿ�ֹͣ��ʶ ������᲻�ϼ��ñ�ʶ
	virtual void StopCheck();//��������
private:
	void ZHDY_Special();//�ۺϵ�Դ�����⴦��
signals:
	void UpdateCheckResult(int datatype, int nId, float fVal);//���²��Խ��
	void AddTaskItem(AutoTestData& data);//����������
	void AddTaskItemResult(AutoTestData& data);//���²��Խ��
/*
    void sig_reminderinformation1(QString);
    void sig_reminderinformation2(QString);
    void sig_reminderinformation3(QString);
    void sig_reminderinformation4(QString);
    void sig_reminderinformation5(QString);
    void sig_reminderinformation6(QString);
    */
    void sig_endTaskItem();  //���Խ���
public slots:
	void CkOnlineTimeout();    
};
#endif
