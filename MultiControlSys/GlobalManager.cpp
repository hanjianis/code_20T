#include "GlobalManager.h"
#include "MyToolTipDlg.h"
GlobalManager* GlobalManager::m_pInstance = nullptr;

void GlobalManager::ReadIni()
{
	m_Settings = new QSettings("ini/Config.ini", QSettings::IniFormat);
	m_Settings->setIniCodec("GBK");

	m_Settings->beginGroup("LastConfig");
	_lat_degree = m_Settings->value("lat_degree").toInt();
	_lat_sec = m_Settings->value("lat_sec").toFloat();
	_lon_degree = m_Settings->value("lon_degree").toInt();
	_lon_sec = m_Settings->value("lon_sec").toFloat();
	_height = m_Settings->value("height").toInt();
	m_Settings->endGroup();
	
}

void GlobalManager::SaveIni()
{
	m_Settings->beginGroup("LastConfig");
	 m_Settings->setValue("lat_degree",_lat_degree);
	 m_Settings->setValue("lat_sec", _lat_sec);
	 m_Settings->setValue("lon_degree", _lon_degree);
	 m_Settings->setValue("lon_sec", _lon_sec);
	 m_Settings->setValue("height", _height);
	m_Settings->endGroup();
}

void GlobalManager::ShowButtonTip(QWidget* parent)
{
	MyToolTipDlg dlg(QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("暂未实现"), parent);
	dlg.exec();
}

GlobalManager::GlobalManager(QObject *parent)
	: QObject(parent)
{
	ReadIni();
}

GlobalManager::~GlobalManager()
{
}

GlobalManager* GlobalManager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GlobalManager(nullptr);
	}
	return m_pInstance;
}
