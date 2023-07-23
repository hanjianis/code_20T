#ifndef _ISYS_CHECK_ITEM_H_
#define _ISYS_CHECK_ITEM_H_
#pragma once
//ϵͳ�Լ��� ��������� һ�����������һ��
#include <QObject>
#include "UDPServer.h"
#include "XLManager.h"
#include <QTimer>
#include "PLCManager.h"
#include "Packet.h"
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
public slots:
    void CkOnlineTimeout();
};
#endif
