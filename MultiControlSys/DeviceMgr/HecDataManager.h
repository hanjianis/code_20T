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
	//公有方法
public:
	void GetHecData(int tm);//获取九轴数据 tm定时
	void SetVal(int lableid, double val);
	int ParseHecData(PMsgData pPacket);//解析九轴数据 接收网络回调
};
