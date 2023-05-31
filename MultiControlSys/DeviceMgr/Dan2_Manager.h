#pragma once

#include <QObject>
#include "DeviceBase.h"
struct UTC_TIME{
	short Year;//
	char Month;//
	char Day;
	char Hour;
	char Minu;
	char Secon;
};
struct SateLiteInfo// ������Ϣ 5 �ֽ�
{
	char Num;//���Ǳ��
	char heading;//����
	short pitch;//��λ�Ƕ�
	char ratio;//�����
};
//���밴��˳��
struct  GPS_Info
{
	char state;//��λ״̬
	UTC_TIME UTC;
	char EW;//E or W E���� W����
	float lon;//���� 
	char NS;//N or S N���� S:��
	float lat;//γ��
	float height;// ���θ߶�
	char GpsCnt;//�ɼ�������
	SateLiteInfo gpsSate[12];//������12��
	char BeiDouCnt;//�������ǿɼ���
	SateLiteInfo BeiDouSate[12];//���12��
	char validSate;//���ڶ�λ��������
	char validSateCnt;//��λ�����Ǳ������
	char validSateNum[12];//���ڶ�λ�����Ǳ�� ���12��
};

class Dan2_Manager : public DeviceBase
{
	Q_OBJECT

public:
	Dan2_Manager(QObject *parent);
	~Dan2_Manager();
private:
	static Dan2_Manager* m_pInstance;

public:
	static Dan2_Manager* getInstance();
public:
	int ParseMsgPowerControl(PMsgData pPacket);//���Ƕ�λ��Ϣ
	int ParseMsgPowerStatus(PMsgData pPacket);//����ͼƬʶ����Ϣ
public:// ���󷽷�
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl();//
	void RequestPowerStatus();

public:
	int _imageFlag = 0;//ͼ��ʶ���ʶ����ͼƬʶ���ʶ��1�ֽڣ�������ͼƬʶ���ʶ��1������ͼƬ1��2������ͼƬ2��0��δƥ�䡣
	GPS_Info _gpsInfo;
};
