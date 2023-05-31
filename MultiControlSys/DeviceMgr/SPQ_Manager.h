#pragma once
//������
#include <QObject>
#include "DeviceBase.h"
class SPQ_Manager : public DeviceBase
{
	Q_OBJECT

public:
	SPQ_Manager(QObject *parent);
	~SPQ_Manager();
private:
	static SPQ_Manager* m_pInstance;
public:
	/*//ʹ����2-10λ 0���Ӻ� 1û���Ӻ�   2---- X151   3---- X152
	//4---- 13X3
	//5---- X154
	//6---- X119
	//7---- X145
	//8---- X100-3X3
	//9---- X100-3X5
	//10---- X100-3X6
	*/
	int _lineState = 0xFFC;//��·״̬

public:
	static SPQ_Manager* getInstance();
public:
	int ParseMsgPowerControl(PMsgData pPacket);
	bool CheckLineConnected();//���������������״̬  //2-10λ ȫ����0 ����true
public:// ���󷽷�
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl();//num ��� control ���ؿ���

};
