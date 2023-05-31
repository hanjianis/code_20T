#pragma once

#include <QObject>

#include "DeviceBase.h"
//ȼ�ͼ����
class RYJCY_Manager : public DeviceBase
{
	Q_OBJECT

public:
	RYJCY_Manager(QObject *parent);
	~RYJCY_Manager();
private:
	static RYJCY_Manager* m_pInstance;
	
public:
	//����״̬ 0���� 1����
	int _MYFlag=0;//���Ϳ���
	int _KYFlag=0;//���Ϳ���
	int _GBGDFlag = 0;//���ù��翪��
	int _DKDSFlag = 0;//�Ͽ����Ͽ���
	int _CJFlag = 0;//�������
public:
	static RYJCY_Manager* getInstance();
public:
	int ParseMsgPowerControl(PMsgData pPacket);
public:// ���󷽷�
	void RequestVersion();
	void RequsetSelfCheck();
	void RequsetPowerControl();
};
