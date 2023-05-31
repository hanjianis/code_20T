#pragma once

#include <QObject>
#include "../Packet.h"
#include "../ISysCheckItem.h"
struct SYS_Data
{
	int nNum;//���
	int nFlag;//���ؿ��� 1�� 0��
	int nValue;//int ��ֵ
	float fValue;//��ѹֵ
};
class CK_Manager : public ISysCheckItem
{
	Q_OBJECT

public:
    CK_Manager(QObject *parent);
	~CK_Manager();
private:
	//static CK_Manager* m_pInstance;
	//UDPServer* pUDPServer;
	//�̿ع����豸 ϵͳ�Լ����� list
	QList<SYS_Data> m_lstSys;
	int _curIndex = 0;//��ǰ����id ��m_lstSys�е�λ��
	//int _datatype = 3;
	bool _bCheck;
	
public:
	//static CK_Manager* getInstance();
public:
	int ParseMsgHeartBeat(PMsgData pPacket);
	int ParseMsgVersion(PMsgData pPacket);
	int ParseMsgSelfCheck(PMsgData pPacket);
	int ParseMsgPowerControl(PMsgData pPacket);
	int ParseMsgPowerStatus(PMsgData pPacket);
	int ParseMsgTestIO(PMsgData pPacket);
	//������Ϣ
	//void RequestHeartBeat();
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl(char num, char control);//num ��� control ���ؿ���
	void RequestPowerStatus();
	void RequestTestIO();
	//��ʼ���
	void StartCheck();
signals:
	void UpdateCheckResultCKSignle(int datatype,int nId, float fVal);
};
