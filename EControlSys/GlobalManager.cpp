#include "GlobalManager.h"
#include <QVariant>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include "LogMgr.h"
#include "../inc/UDPCmd.h"
GlobalManager* GlobalManager::m_pInstance = nullptr;

void GlobalManager::initId()
{
	QString sql = QString("select max(id) as id from think_plan;");
	QSqlQuery query(sql);
	while (query.next())
	{
		_plan_id = query.value("id").toInt() + 1;
	}

	sql = QString("select max(id) as id from tasks_list;");
	query.exec(sql);
	while (query.next())
	{
		_task_id = query.value("id").toInt() + 1;
	}

}

void GlobalManager::initSubjects()
{
	QString sql = QString("select * from subject;");
	QSqlQuery query(sql);
	int row = 0;
	while (query.next())
	{
		SubjectInfo si;
		si.id = query.value("id").toInt();
		si.subject_name = query.value("subject_name").toString();
		si.remark = query.value("remark").toString();
		si.state = query.value("state").toBool();
		si.protobuf_ids = query.value("protobuf_id").toString();
		m_mapSubjects[si.subject_name] = si;
	}
}

void GlobalManager::initDeviceInfo()
{
	QString sql = QString("select * from device;");
	QSqlQuery query(sql);
	int row = 0;
	while (query.next())
	{
		DeviceOnline dev;
		dev.id = query.value("id").toInt();
		dev.strIp = query.value("ip").toString();
		dev.port = query.value("port").toInt();
		dev.strMac = query.value("mac").toString();
		dev.strName = query.value("name").toString();
		dev.strTm = query.value("lastTm").toString();
		dev.state = 0;
		dev.strVer = query.value("version").toString();

		m_mapDeviceOnline[dev.port] = dev;
	}
}

void GlobalManager::initDeviceListInfo()
{
	QString sql = QString("select * from deviceList where udportcp = 2;");
	QSqlQuery query(sql);
	int row = 0;
	while (query.next())
	{
		DeviceOnline dev;
		dev.id = query.value("id").toInt();
		dev.strIp = query.value("ip").toString();
		dev.port = query.value("port").toInt();
		dev.strMac = query.value("mac").toString();
		dev.strName = query.value("note").toString();
		dev.strTm = query.value("lastTm").toString();
		dev.state = 0;
		dev.strVer = query.value("version").toString();
		dev.heartcmd = query.value("heartcmd").toInt();
		dev.onlineflag = query.value("onlineflag").toInt();
		m_mapDeviceOnline[dev.heartcmd] = dev;
	}
}

void GlobalManager::initStudentClass()
{
	QString sql = QString("select * from student_class;");
	QSqlQuery query(sql);
	int row = 0;
	while (query.next())
	{
		StudentClass dev;
		dev.id = query.value("id").toInt();
		dev.name = query.value("name").toString();
		dev.remark = query.value("remark").toInt();
		dev.state = query.value("state").toInt();
		
		m_mapStudentClass[dev.name] = dev;
	}
}

void GlobalManager::initWeight()
{
	QString sql = QString("select * from weight;");
	QSqlQuery query(sql);
	int row = 0;
	while (query.next())
	{
		_compuWeight = query.value("compu").toFloat();
		_teachWeight = query.value("teacher").toFloat();
	
	}
}

void GlobalManager::initSysService()
{
	QString sql = QString("select * from service;");
	QSqlQuery query(sql);
	int row = 0;
	while (query.next())
	{
		SysService sys;
		sys.id = query.value("id").toInt();
		sys.state = query.value("state").toInt();
		sys.start = query.value("start").toInt();
		sys.sys_name = query.value("sys_name").toString();
		sys.sys_txt = query.value("txt").toInt();
		m_mapSysService.insert(sys.id, sys);
	}
}

GlobalManager::GlobalManager(QObject *parent)
	: QObject(parent)
{
	int flg = RYJCY_CMD_HEARD_BEAT;// CK_CMD_HEARD_BEAT | ZHDY_CMD_HEARD_BEAT |
	int a = flg & ZHDY_CMD_HEARD_BEAT;
	initId();
	initSubjects();
	//initDeviceInfo();
	initDeviceListInfo();
	initStudentClass();
	initWeight();
	initSysService();
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

void GlobalManager::ShowMessageBox(QString str)
{
	QMessageBox::information(nullptr, QString::fromLocal8Bit("提示"), str, QMessageBox::Ok);
}

QString GlobalManager::ConvertModeToString(int mode)
{
	QString str;
	if (mode == 1)
		str = QString::fromLocal8Bit("训练模式");
	if (mode == 2)
		str = QString::fromLocal8Bit("考核模式");

	return str;
}

QString GlobalManager::ConvertTypeToString(int type)
{
	QString str;
	if (type == 1)
		str = QString::fromLocal8Bit("想定任务");
	if (type == 2)
		str = QString::fromLocal8Bit("自主任务");

	return str;
}

QString GlobalManager::ConvertStateToString(int state)
{
	QString str;
	if (state == 0)
		str = QString::fromLocal8Bit("待执行");
	if (state == 1)
		str = QString::fromLocal8Bit("训练中");
	if (state == 2)
		str = QString::fromLocal8Bit("已完成");
	if (state == 3)
		str = QString::fromLocal8Bit("暂停中");
	return str;
}

QString GlobalManager::ConvertOnlineString(int state)
{
	QString str;
	if (state == 1)
		str = QString::fromLocal8Bit("在线");
	if (state == 0)
		str = QString::fromLocal8Bit("离线");

	return str;
}

bool GlobalManager::AddTaskToDB(TaskInfo& tsinfo)
{
	QString str = QString("TASK_%1").arg(tsinfo.id, 3, 10, QLatin1Char('0'));
	tsinfo.task_id = str;

	int paramindex = 0;
	QSqlQuery query;
	query.prepare("exec [dbo].[AddTask] ?,?, ?, ?, ?, ?, ?, ?, ?,?,?,? output");

	query.bindValue(paramindex++, tsinfo.task_id);//
	query.bindValue(paramindex++, tsinfo.plan_id);
	query.bindValue(paramindex++, tsinfo.task_name);//名称 与想定的任务名称一致
	query.bindValue(paramindex++, tsinfo.mode);
	query.bindValue(paramindex++, tsinfo.type);// type 任务分类 属于想定任务
	query.bindValue(paramindex++, tsinfo.state);//state
	query.bindValue(paramindex++, tsinfo.subject);//科目
	query.bindValue(paramindex++, tsinfo.user_login_name);//学员
	query.bindValue(paramindex++, tsinfo.startTm1);//时间
	query.bindValue(paramindex++, tsinfo.startTm2);//时间
	//query.bindValue(paramindex++, ui.lineEdit_3->text());
	query.bindValue(paramindex++, tsinfo.note);
	query.bindValue(paramindex, 0, QSql::Out);
	bool bFlag = query.exec();
	if (bFlag)
	{
		int taskid = query.boundValue(paramindex).toInt();
		if (taskid < 0)
			bFlag = false;
		else
		{
			GlobalManager::getInstance()->_task_id = taskid + 1;
		}
	}
	return bFlag;
}

PCurrentTask GlobalManager::GenerateOneTask(QString subject)
{
	//如果为空 添加一个自主任务
	TaskInfo tsinfo;
	tsinfo.id = _task_id ;
	tsinfo.task_name = QString::fromLocal8Bit("自主训练");
	tsinfo.subject = subject;
	tsinfo.mode = 1;
	tsinfo.type = 2;//自主任务
	tsinfo.state = 1;//直接进行中
	tsinfo.startTm1 = LogMgr::GetInstance()->GetCurrentTimeString();
	tsinfo.startTm2 = tsinfo.startTm1;
	AddTaskToDB(tsinfo);
	//需要通知添加到页面
	emit UpdateTaskList(tsinfo);

	CurrentTask curTask;
	curTask.id = tsinfo.id;
	QString str = QString("TASK_%1").arg(tsinfo.id, 3, 10, QLatin1Char('0'));
	curTask.task_id = str;
	curTask.task_name = tsinfo.task_name;
	curTask.subject = subject;
	
	curTask.user_login_name = tsinfo.user_login_name;
	m_mapCurTask[subject] = curTask;
	return &m_mapCurTask[subject];
}

bool GlobalManager::AddCurTask(CurrentTask curTask)
{
	//判断是否存在
	QMap<QString, CurrentTask>::iterator it = m_mapCurTask.find(curTask.subject);

	if (it != m_mapCurTask.end())
	{
		//已经存在同样科目的任务
		ShowMessageBox(QString::fromLocal8Bit("已经存在同样科目的任务!!"));
		return false;
	}
	m_mapCurTask[curTask.subject] = curTask;
	return true;
}

void GlobalManager::RemoveCurTask(QString key)
{
	//判断是否存在
	QMap<QString, CurrentTask>::iterator it = m_mapCurTask.find(key);

	if (it != m_mapCurTask.end())
	{
		m_mapCurTask.erase(it);
		qDebug() << "remove success";
		return;
	}
}
QString GlobalManager::GetSubject(int msgid)
{
	int mainid = msgid / 100;
	QMap<QString, SubjectInfo>::iterator it = m_mapSubjects.begin();
	while (it != m_mapSubjects.end())
	{
		QStringList strlst = it->protobuf_ids.split(";");
		for (int i = 0; i < strlst.size(); i++)
		{
			if (mainid == strlst[i].toInt())
			{
				return it->subject_name;
		
			}
		}
		it++;
	}
	return "";
}


PCurrentTask GlobalManager::GetCurTask(int msgid)
{
	QString subject = GetSubject(msgid);
	int mainid = msgid / 100;
	QMap<QString, CurrentTask>::iterator it = m_mapCurTask.find(subject);
	while (it != m_mapCurTask.end())
	{
		return &(*it);
	}
	return nullptr;
}

PDeviceOnline GlobalManager::GetDeviceOnline(int port)
{
	QMap<int, DeviceOnline>::iterator it = m_mapDeviceOnline.find(port);
	if (it != m_mapDeviceOnline.end())
		return &(*it);
	return nullptr;
}

void GlobalManager::SetDeviceOnline(int port, int state)
{
	PDeviceOnline pDevice = GetDeviceOnline(port);
	if (pDevice != nullptr)
	{
		pDevice->state = state;
		if (state == ON_LINE)
		{
			pDevice->strTm = LogMgr::GetInstance()->GetCurrentTimeString();
		}
	}

	emit UpdateDeviceList();
}

void GlobalManager::SetUDPOnline(int cmd)
{
	UpdateUDPDeviceOnline(cmd, CK_CMD_HEARD_BEAT);//程控
	//以后继续加
	emit UpdateDeviceList();
}

void GlobalManager::SaveDeviceOnlineTm()
{
	QString sql;
	QSqlQuery query;
	QMap<int, DeviceOnline>::iterator it = m_mapDeviceOnline.begin();
	while (it != m_mapDeviceOnline.end())
	{
		sql = QString("update device set lastTm='%1' where heartcmd = %2").arg(it->strTm).arg(it->heartcmd);
		query.exec(sql);
		it++;
	}
}

void GlobalManager::SaveWeight()
{
	//QString sql = QString("select * from weight;");
	QString sql = QString("update weight set compu=%1,teacher=%2 where id=2" ).arg(_compuWeight).arg(_teachWeight);
	QSqlQuery query;
	if (query.exec(sql))
	{
		qDebug() << "SaveWeigh success";
	}
	else
	{
		qDebug() << "SaveWeigh failed";
	}
	
}

void GlobalManager::SaveAll()
{
	SaveDeviceOnlineTm();
	SaveWeight();
}

void GlobalManager::UpdateUDPDeviceOnline(int cmd, int targetcmd)
{
	PDeviceOnline pDevice = GetDeviceOnline(targetcmd);
	
	if (pDevice != nullptr)
	{
		if((cmd&targetcmd) != 0)
			pDevice->state = ON_LINE;
		else
			pDevice->state = OFF_LINE;

		pDevice->strTm = LogMgr::GetInstance()->GetCurrentTimeString();

	}
}
