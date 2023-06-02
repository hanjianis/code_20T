#ifndef PACKET_H__
#define PACKET_H__
#include "../inc/T20_NetMsg.pb.h"
#include <windows.h>
#include <string>
#include <QObject>
using namespace std;
using namespace NetMsg;
#pragma comment(lib,"ws2_32.lib")
#pragma once
#define PACKET_HEADER_DATALENGTH_SIZE     4
#define PACKET_HEADER_VERIFYCODE_SIZE     2
#define PACKET_HEADER_MSGID_SIZE          4
#define PACKET_HEADER_SIZE                10


#define MAX_BUFFER  20480
#define M_PORT 9000  //综合测控软件端口
#define E_PORT 9001  //火工品测试仪端口
#define FUSE_PORT 9002 // 引信测试端口
#define INS_PORT 9005 //惯导端口
#ifndef _SELECT_STYLE
#define _SELECT_STYLE

#endif
typedef struct MsgData
{
	int MsgId;
	int MsgLen;
	char* msgBuf;
}*PMsgData;
typedef struct MsgNetData
{
	int id;
	int softid;
	QString soft;
	QString note;
}*PMsgNetData;
//班级信息
typedef struct StudentClass
{
	int id;
	QString name;
	QString remark;
	int state;
};
//科目信息
typedef struct SubjectInfo
{
	int id;
	QString subject_name;
	QString remark;
	bool state;
	QString protobuf_ids;
}*PSubjectInfo;

typedef struct TaskInfo
{
	int id;
	QString task_id;
	QString plan_id;
	QString task_name;
	QString subject;
	int mode;
	int type;
	QString user_login_name;
	QString startTm1;
	QString startTm2;
	QString endTm;
	int state;
	QString note;

};
//当前执行中的任务
typedef struct CurrentTask
{
	int id;
	QString task_id;//任务编号
	QString task_name;//任务名称
	QString subject;//科目
	QString user_login_name;//学员
	int state;
	int mode;
	int type;
}*PCurrentTask;

//设备在线情况
#define ON_LINE  1
#define OFF_LINE 0
typedef struct DeviceOnline
{
	int id;
	int port;
	int state;//状态 1：在线 0：离线
	int onlineflag;
	int heartcmd;
	int udportcp;//1:udp 2:tcp
	QString strName;
	QString strIp;//ip地址
	QString strTm;//在线时间
	QString strMac;//MAC地址
	QString strVer;//version 版本

}*PDeviceOnline;
//系统服务 结构
typedef struct SysService
{
	int id;
	int sys_id;
	int state;//状态 1：正常 0：离线
	int start;//启停用 1：启用 0：停用
	QString sys_name;//系统名称
	QString sys_txt;//备注信息
}*PSysService;
#endif