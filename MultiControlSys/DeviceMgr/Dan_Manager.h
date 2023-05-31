#pragma once

#include <QObject>
#include "DeviceBase.h"
struct AtmosInfo//������Ϣ
{
	float staticPressure;//��ѹ
	float dynamicPressure1;//��ѹ1
	float dynamicPressure2;//��ѹ1
};
class Dan_Manager : public DeviceBase
{
	Q_OBJECT

public:
	Dan_Manager(QObject *parent);
	~Dan_Manager();
private:
	static Dan_Manager* m_pInstance;

public:
	static Dan_Manager* getInstance();
public:
	int ParseMsgPowerControl(PMsgData pPacket);//�¶���Ϣ
	int ParseMsgPowerStatus(PMsgData pPacket);//������Ϣ
	int ParseMsgLampControl(PMsgData pPacket); //�������Ϣ
	int ParseMsgSoundControl(PMsgData pPacket);//��������;
	int ParseMsgTailControl(PMsgData pPacket); //β�����
	int ParseMsgLineInfo(PMsgData pPacket);//��·����״̬
	int ParseMsgEedInfo(PMsgData pPacket);	  //��Ʒ����
	bool CheckLineConnected();//�ж���·����״̬
	bool CheckLeiDaGaoDu();//20210604�ж��״�߶ȱ������״̬
public:// ���󷽷�
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl();//
	void RequestPowerStatus();
	void RequestSound(int val);//���� 1����2 ��������
	void RequestLineInfo();//��ȡ��·����״̬
	void RequsetLamControl(int val);//��������ƴ򿪺͹ر� val��1 �� 0���ر� ����2�ֽ� δ����Ƭ���ĳ�1�ֽ� Ҫ�ĳ�1�ֽ�
public:
	float _temp = 0;//�¶�
	AtmosInfo _atmosInfo;//������Ϣ
	int _lamp;//����� 1��
	int _sound;//������ʶ
	int _tailState;//β��
	int _guanminDianZu;//����������Ϣ �����ж��״������״̬
	unsigned short _lineState = 0;//��·״̬ 0-31λ
	//��Ʒ���� �Զ��� n ��ȷ��
};
