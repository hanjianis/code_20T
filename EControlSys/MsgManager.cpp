#include "MsgManager.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QSqlQuery>
MsgManager* MsgManager::m_pInstance = nullptr;
MsgManager::MsgManager(QObject *parent)
	: QObject(parent)
{
	InitMsg();         
	Supplement();
}

MsgManager::~MsgManager()
{
}

MsgManager* MsgManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MsgManager(nullptr);
	}
	return m_pInstance;
}

PMsgNetData MsgManager::getMsgNet(int msgId)
{
	QMap<int, MsgNetData>::iterator it = m_mapMsg.find(msgId);
	if (it != m_mapMsg.end())
	{
		return &(*it);
	}
	return nullptr;
}

void MsgManager::InitMsg()
{
	//�����ݿ��ж�ȡ
	QString sql = QString("select * from client_acs");
	QSqlQuery query(sql);
	while (query.next())
	{
		MsgNetData dd;
		dd.id = query.value("ac_id").toInt();
		dd.note = query.value("ac_note").toString();
		dd.soft = query.value("ac_soft").toString();
		dd.softid = query.value("ac_softid").toInt();
		m_mapMsg.insert(dd.id, dd);
	}
	
}

void MsgManager::Supplement()
{
	QMap<int, MsgNetData>::iterator it = m_mapMsg.begin();
	while (it != m_mapMsg.end())
	{
		if (it->id / 100 == 2)
		{
			it->soft = QString::fromLocal8Bit("��Ʒ������");
		}
		if (it->id / 100 == 1)
		{
			it->soft = QString::fromLocal8Bit("�ۺϲ�����");
		}
		it++;
	}
}
