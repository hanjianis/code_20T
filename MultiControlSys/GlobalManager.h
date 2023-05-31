#ifndef _GLOBAL_MANAGER_H
#define _GLOBAL_MANAGER_H
#pragma once

#include <QObject>
#include <QSettings>
#include "AutoTestWidget.h"
//ȫ�ֲ����Ĺ��� ��ini�ļ��Ĺ��� ini/config.ini
//һЩ��γ�� ���θ߶�
//����ĵ��� �����ͺŽ��б��棬���������й��õ�һЩ���� ������������
class GlobalManager : public QObject
{
	Q_OBJECT

public:
	GlobalManager(QObject *parent);
	~GlobalManager();
private:
	static GlobalManager* m_pInstance;
	void ReadIni();

public:
	static GlobalManager* getInstance();
public:

	QSettings* m_Settings;
	QString _missileType;//�����ͺ�
	QString _missileName;//����
	QString _user;//�û�
	int _lat_degree;//γ�� ��
	float _lat_sec;//γ�� ��
	int _lon_degree;//���� ��
	float _lon_sec;//���� ��
	int _height;//����

	float _currentTemp=0;//�ۺϲ���ʱ ����ĵ�ǰ�¶�

	AutoTestWidget* m_at = nullptr;//�������  autotestdlg���� ��Taskʹ��
public:
	void SaveIni();//�����˳�ʱ ���ڱ��� 
	void ShowButtonTip(QWidget* parent);//��ʾ������δʵ��
};
#endif