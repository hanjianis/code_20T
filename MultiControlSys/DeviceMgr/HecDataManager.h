#pragma once

#include <QObject>
#include "../Packet.h"
class HecDataManager : public QObject
{
	Q_OBJECT

public:
	HecDataManager(QObject *parent);
	~HecDataManager();
private:
	static HecDataManager* m_pInstance ;
public:
	static HecDataManager* getInstance();
	//���з���
public:
	void GetHecData(int tm);//��ȡ�������� tm��ʱ
	void SetVal(int lableid, double val);
	int ParseHecData(PMsgData pPacket);//������������ ��������ص�
};
