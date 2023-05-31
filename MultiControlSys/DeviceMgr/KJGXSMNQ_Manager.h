#pragma once

#include <QObject>
#include "DeviceBase.h"
class KJGXSMNQ_Manager : public DeviceBase
{
	Q_OBJECT

public:
	KJGXSMNQ_Manager(QObject *parent);
	~KJGXSMNQ_Manager();
private:
	static KJGXSMNQ_Manager* m_pInstance;
public:
	int _imageNum = 0;//ͼƬ��� 1-5������ʾ5��ͼƬ
	int _illLevel = 0;//�նȵ�λ״̬ 0�͵�λ 1�ߵ�λ
public:
	static KJGXSMNQ_Manager* getInstance();
public:

	int ParseMsgPowerControl(PMsgData pPacket);//����ͼƬ����
	int ParseMsgPowerStatus(PMsgData pPacket);//��ȡ�նȵ�λ״̬
public:// ���󷽷�
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl(char num);//num ��� ����ͼƬ����
	void RequestPowerStatus();

};
