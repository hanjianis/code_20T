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
	void initWeight();//��ʼ�����Ȩ�� �����ݿ��ж�ȡ
	void initSysService();//ϵͳ���� 
//	void AddAutoTask(CurrentTask);//�����������
public:
	static GlobalManager* getInstance();
public:
	int _plan_id;//�붨������id�� 
	int _task_id;//����id�� 
	//��Ŀ��Ϣ
	QMap<QString,SubjectInfo> m_mapSubjects;//key ��Ŀ����
	QMap<QString, CurrentTask> m_mapCurTask;//key ��Ŀ����
	//
	QMap<int, DeviceOnline> m_mapDeviceOnline;//key �豸�˿�
	//�༶map
	QMap<QString, StudentClass> m_mapStudentClass;//key=�༶name
	//���Ȩ��
	float _compuWeight;//��������Ȩ��
	float _teachWeight;//��ʦ���Ȩ��
	//ϵͳ���� 
	QMap<int, SysService> m_mapSysService;
signals:
		//���������б�
	void UpdateTaskList(TaskInfo& tsinfo);
	//�����豸�б� �豸�б�ͨ��global������ ����
	void UpdateDeviceList();
public:
	void ShowMessageBox(QString str);
	QString ConvertModeToString(int mode);
	QString ConvertTypeToString(int type);
	QString ConvertStateToString(int state);
	QString ConvertOnlineString(int state);
	//����protobuf id ��ȡ��Ŀ
	QString GetSubject(int msgid);
	//�������DB
	bool AddTaskToDB(TaskInfo& tsinfo);
	//����һ����������
	PCurrentTask GenerateOneTask(QString subject);
	//�������
	bool AddCurTask(CurrentTask curTask);
	//�Ƴ�ĳ������
	void RemoveCurTask(QString key);
	//����protobuf id ���������ĸ�����
	PCurrentTask GetCurTask(int msgid);
	//����port ��ȡDeviceOnline
	PDeviceOnline GetDeviceOnline(int port);
	//�����豸��������� port�˿ں� state��״̬ 1���� 0����
	void SetDeviceOnline(int port, int state);
	//�����ۺϲ�ط����ĸ������������� �ж��豸�������
	void SetUDPOnline(int cmd);
	//���¸����豸�����һ��ʹ��ʱ��
	void SaveDeviceOnlineTm();
	//����Ȩ��
	void SaveWeight();
	//�����˳�ʱ������һЩ����
	void SaveAll();
private:
	void UpdateUDPDeviceOnline(int cmd, int targetcmd);
};
#endif