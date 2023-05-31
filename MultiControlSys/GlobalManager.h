#ifndef _GLOBAL_MANAGER_H
#define _GLOBAL_MANAGER_H
#pragma once

#include <QObject>
#include <QSettings>
#include "AutoTestWidget.h"
//全局参数的管理 是ini文件的管理 ini/config.ini
//一些经纬度 海拔高度
//输入的弹号 导弹型号进行保存，整个过程中公用的一些数据 都可以在这里
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
	QString _missileType;//导弹型号
	QString _missileName;//弹号
	QString _user;//用户
	int _lat_degree;//纬度 度
	float _lat_sec;//纬度 分
	int _lon_degree;//经度 度
	float _lon_sec;//经度 分
	int _height;//海拔

	float _currentTemp=0;//综合测试时 输入的当前温度

	AutoTestWidget* m_at = nullptr;//下面的栏  autotestdlg设置 供Task使用
public:
	void SaveIni();//程序退出时 用于保存 
	void ShowButtonTip(QWidget* parent);//提示功能暂未实现
};
#endif