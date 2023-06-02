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
#define M_PORT 9000  //�ۺϲ������˿�
#define E_PORT 9001  //��Ʒ�����Ƕ˿�
#define FUSE_PORT 9002 // ���Ų��Զ˿�
#define INS_PORT 9005 //�ߵ��˿�
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
//�༶��Ϣ
typedef struct StudentClass
{
	int id;
	QString name;
	QString remark;
	int state;
};
//��Ŀ��Ϣ
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
//��ǰִ���е�����
typedef struct CurrentTask
{
	int id;
	QString task_id;//������
	QString task_name;//��������
	QString subject;//��Ŀ
	QString user_login_name;//ѧԱ
	int state;
	int mode;
	int type;
}*PCurrentTask;

//�豸�������
#define ON_LINE  1
#define OFF_LINE 0
typedef struct DeviceOnline
{
	int id;
	int port;
	int state;//״̬ 1������ 0������
	int onlineflag;
	int heartcmd;
	int udportcp;//1:udp 2:tcp
	QString strName;
	QString strIp;//ip��ַ
	QString strTm;//����ʱ��
	QString strMac;//MAC��ַ
	QString strVer;//version �汾

}*PDeviceOnline;
//ϵͳ���� �ṹ
typedef struct SysService
{
	int id;
	int sys_id;
	int state;//״̬ 1������ 0������
	int start;//��ͣ�� 1������ 0��ͣ��
	QString sys_name;//ϵͳ����
	QString sys_txt;//��ע��Ϣ
}*PSysService;
#endif