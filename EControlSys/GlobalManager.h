#ifndef _GLOBAL_MANAGER_H
#define _GLOBAL_MANAGER_H
#pragma once

#include <QObject>
#include <QMap>
#include "Packet.h"
class GlobalManager : public QObject
{
	Q_OBJECT

public:
	GlobalManager(QObject *parent);
	~GlobalManager();

	
private:
	static GlobalManager* m_pInstance;
	void initId();
	void initSubjects();
	void initDeviceInfo();
	void initDeviceListInfo();
	void initStudentClass();
	void initWeight();//初始化打分权重 从数据库中读取
	void initSysService();//系统服务 
//	void AddAutoTask(CurrentTask);//添加自主任务
public:
	static GlobalManager* getInstance();
public:
	int _plan_id;//想定方案的id号 
	int _task_id;//任务id号 
	//科目信息
	QMap<QString,SubjectInfo> m_mapSubjects;//key 科目名称
	QMap<QString, CurrentTask> m_mapCurTask;//key 科目名称
	//
	QMap<int, DeviceOnline> m_mapDeviceOnline;//key 设备端口
	//班级map
	QMap<QString, StudentClass> m_mapStudentClass;//key=班级name
	//打分权重
	float _compuWeight;//计算机打分权重
	float _teachWeight;//老师打分权重
	//系统服务 
	QMap<int, SysService> m_mapSysService;
signals:
		//更新任务列表
	void UpdateTaskList(TaskInfo& tsinfo);
	//更新设备列表 设备列表通过global的数据 更新
	void UpdateDeviceList();
public:
	void ShowMessageBox(QString str);
	QString ConvertModeToString(int mode);
	QString ConvertTypeToString(int type);
	QString ConvertStateToString(int state);
	QString ConvertOnlineString(int state);
	//根据protobuf id 获取科目
	QString GetSubject(int msgid);
	//添加任务到DB
	bool AddTaskToDB(TaskInfo& tsinfo);
	//产生一个自主任务
	PCurrentTask GenerateOneTask(QString subject);
	//添加任务
	bool AddCurTask(CurrentTask curTask);
	//移除某个任务
	void RemoveCurTask(QString key);
	//根据protobuf id 查找属于哪个任务
	PCurrentTask GetCurTask(int msgid);
	//根据port 获取DeviceOnline
	PDeviceOnline GetDeviceOnline(int port);
	//设置设备的在线情况 port端口号 state：状态 1在线 0离线
	void SetDeviceOnline(int port, int state);
	//根据综合测控发来的各个心跳命令字 判断设备在线情况
	void SetUDPOnline(int cmd);
	//更新各个设备的最后一次使用时间
	void SaveDeviceOnlineTm();
	//保存权重
	void SaveWeight();
	//程序退出时，保存一些数据
	void SaveAll();
private:
	void UpdateUDPDeviceOnline(int cmd, int targetcmd);
};
#endif