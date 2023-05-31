#pragma once

#include <QObject>
#include "DeviceBase.h"
struct SXZPDY_Data
{
	int nNum;//���
	int nFlag;//���ؿ��� 1�� 0��

	float fValueV;//��ѹֵ
	float fValueA;//����ֵ
};
class SXZPDY_Manager : public DeviceBase
{
	Q_OBJECT

public:
	SXZPDY_Manager(QObject *parent);
	~SXZPDY_Manager();
private:
	static SXZPDY_Manager* m_pInstance;
	QMap<int, SXZPDY_Data> m_mapSXZPDY;	//��Դ״̬ 3· ��ѹ ����  A B C
public:
	static SXZPDY_Manager* getInstance();

private:
	void ResetMap();
public:
	int ParseMsgPowerStatus(PMsgData pPacket);
public:// ���󷽷�
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerStatus();
};
