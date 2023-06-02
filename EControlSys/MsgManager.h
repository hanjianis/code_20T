#pragma once

#include <QObject>
#include <QMap>
#include "Packet.h"
typedef map<int, QString>  MAP_STRING;
typedef map<int, QString>::iterator MAP_STRING_IT;
class MsgManager : public QObject
{
	Q_OBJECT

public:
	MsgManager(QObject *parent);
	~MsgManager();

	static MsgManager* m_pInstance;
	QMap<int, MsgNetData> m_mapMsg;
public:
	//单体实例获取方法 唯一的对象指针
	static MsgManager* GetInstance();
public:
	PMsgNetData getMsgNet(int msgId);
private:
	void InitMsg();
	void Supplement();
};
