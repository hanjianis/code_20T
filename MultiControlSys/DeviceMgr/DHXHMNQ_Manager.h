#pragma once

#include <QObject>
#include "DeviceBase.h"
//�����ź�ģ����
class DHXHMNQ_Manager : public DeviceBase
{
	Q_OBJECT

public:
	DHXHMNQ_Manager(QObject *parent);
	~DHXHMNQ_Manager();
private:
	static DHXHMNQ_Manager* m_pInstance;//aaaaaa
	//�������ݿ���
public:
	static DHXHMNQ_Manager* getInstance();
public:
	int ParseMsgPowerControl(PMsgData pPacket);//�������ݿ���
	int ParseMsgPowerStatus(PMsgData pPacket);//����״̬
public:// ���󷽷�
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl(char num, char control);//n�������ݿ��� �Զ���
	void RequestPowerStatus();
};
