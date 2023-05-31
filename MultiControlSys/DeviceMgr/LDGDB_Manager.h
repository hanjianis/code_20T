#pragma once
//�״�߶ȱ�
#include <QObject>
#include "DeviceBase.h"
class LDGDB_Manager : public DeviceBase
{
	Q_OBJECT

public:
	LDGDB_Manager(QObject *parent);
	~LDGDB_Manager();
private:
	static LDGDB_Manager* m_pInstance;

public:
	static LDGDB_Manager* getInstance();
public:
	int ParseMsgVersion(PMsgData pPacket);
	int ParseMsgSelfCheck(PMsgData pPacket);
	int ParseMsgPowerControl(PMsgData pPacket);//�״����ݿ���
	int ParseMsgPowerStatus(PMsgData pPacket);//�״�״̬
public:// ���󷽷�
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl(int  height,int shuaijian);//height �߶� �״����ݿ���
	void RequestPowerStatus();
	bool CheckConneced();//20210604 _lineState ������·����״̬
public:
	int _height = 0;//�״�߶� 2�ֽ� ��λ��
	int _shuaijian = 0;//˥��ֵ
	char _lineState = 0;//�״�״̬ λ0��1ʱ���������� λ1��1ʱ����������
	bool _bConnectSuccess = false;//�ϵ��Ƿ�ɹ��ı�ʶ �ȴ�����
};
