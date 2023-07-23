#pragma once

#include <QObject>
#include "DeviceBase.h"
//�ۺϵ�Դ
struct ZHDY_Data
{
	int nNum;//���
	int nFlag;//���ؿ��� 1�� 0��

	float fValueV;//��ѹֵ
	float fValueA;//����ֵ
};
class ZHDY_Manager : public DeviceBase
{
	Q_OBJECT

public:
	ZHDY_Manager(QObject *parent);
	~ZHDY_Manager();
private:
	static ZHDY_Manager* m_pInstance;
	

	QMap<int, ZHDY_Data> m_mapZHDY;	//��Դ״̬ 8· ��ѹ ���� 

private:
	void ResetMap();
public:
	static ZHDY_Manager* getInstance();
public:

	int ParseMsgPowerControl(PMsgData pPacket);
	int ParseMsgPowerStatus(PMsgData pPacket);
public:// ���󷽷�
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl(char num, char control);//num ��� control ���ؿ���
	void RequestPowerStatus();
};
