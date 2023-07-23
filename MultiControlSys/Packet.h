#ifndef PACKET_H__
#define PACKET_H__
#pragma once
#include "../inc/T20_NetMsg.pb.h"
#include "../inc/UDPCmd.h"
#include <windows.h>
//#include <rpcndr.h>
#include <string>

#include <QObject>
#include <QString>
#include <QLabel>
#include "libxl/libxl.h"
#pragma comment(lib,"libxl/libxl.lib")
#pragma comment(lib,"ws2_32.lib")
using namespace libxl;
using namespace std;
typedef unsigned char byte;
using namespace NetMsg;
#define MOVE_0 1
#define PACKET_HEADER_DATALENGTH_SIZE     4
#define PACKET_HEADER_VERIFYCODE_SIZE     2
#define PACKET_HEADER_MSGID_SIZE          4
#define PACKET_HEADER_SIZE                10

#define UDP_HEADER_CRC_SIZE 4//crc 4���ֽ�
#define UDP_HEADER_CMD_SIZE 4//������ 4���ֽ�
#define UDP_HEADER_LEN  8


#define  WIDTH 1280
#define  HEIGHT 1024
#define  DLG_WIDTH 514
#define  DLG_HEIGHT 425
#define  DLG_WIDTH2 400
#define  DLG_HEIGHT2 320
#define MAX_BUFFER  20480

#define M_PORT 9000  //�ۺϲ������˿�
typedef struct  MsgData
{
	int MsgId;
	int MsgLen;
	char* msgBuf;
}*PMsgData;
enum TestType
{
	ATT_SYS = 1,//ϵͳ�Լ�
	ATT_AUTO=2,//�Զ�����
};

//ϵͳ�Լ�����
enum SysteSelfTest
{
    SELF_TEST=7,
    AIRTIGHTNESS_INSPECTION=2,
};

//�Զ����Ե�����
enum AutoTestType
{
    SIGNLE_TEST = 1,//�������
    INS_TEST = 2,//�ߵ�����
    MULT_TEST = 3,//�ۺϲ���
    INTEGRATED_TESTING=10,
    ZERORETURN_STEERGEAR=11, //�������
};
struct AutoTestFileInfo
{
	int unitType;//���Ե�Ԫ ϵͳ�Լ� ������� �ۺϲ��� �ߵ�����
	QString unitName;//
	int modeType;//���Է�ʽ �������� �������
	QString modeName;//���Է�ʽ
	QString filetm;//yyyyMMddhhmmss
	QString startDt;//��ʼ���� ������
	QString startTm;//��ʼʱ�� ʱ����
	QString endTm;//����ʱ�� 
	QString missileType;//�����ͺ�
	QString missileName;//����
};
enum AUTO_DATA_TYPE
{
	AUTO_TYPE_SIMULATOR = 1,//����ģ��
	AUTO_TYPE_UDP = 2,//udp��ȡ
};

struct AutoTestData
{
	int id;
	int num;
	int datatype;//�������� ��Ӧ�������������
	int type;//1 ����ģ�� 2:udp��ȡ
	QString name;
	QString standardname;
	int standardtype;//�������� 1����Χֵ 2���̶�ֵ
	float standardval;
	float min;
	float max;
	QString val;
	QString unit;
	int tm;//��ʱ��ʱ���� ��λ��s
	int content;
	QString tip;
};
struct AutoTestList
{
	int id;
	QString note;
	QString autoVal;//Ĭ��ֵ �����ݿ��ȡ
	int type;//���� 1��ģ�� 2����ʵ

	QLabel* val;
};

//����Ӳ���豸��ip port�����к� ��Ӧ�ڱ�DeviceList��id
enum DEV_ID
{
	DEV_CK = CK_CMD_HEARD_BEAT,//�̿�
	DEV_ZHDY = ZHDY_CMD_HEARD_BEAT,//�ۺϵ�Դ
	DEV_HEC = HEC_CMD_HEARD_BEAT,//���ᴫ����
	DEV_RYJCY = RYJCY_CMD_HEARD_BEAT,//ȼ�ͼ����
	DEV_SXZPDY= SXZPDY_CMD_HEARD_BEAT,//������Ƶ��Դ
	DEV_SPQ=SPQ_CMD_HEARD_BEAT,//������
	DEV_DHXHMNQ=DHXHMNQ_CMD_HEARD_BEAT,//�����ź�ģ����
	DEV_KJGXSMNQ=KJGXSMNQ_CMD_HEARD_BEAT,//�ɼ�������ģ����
	DEV_LDGDB=LDGDB_CMD_HEARD_BEAT,//�״�߶ȱ�
	DEV_Dan2=Dan2_CMD_HEARD_BEAT,//��2
	DEV_Dan = Dan_CMD_HEARD_BEAT,//��
    DEV_ZJ=ZJ_CMD_HEARD_BEAT,  //�Լ�ģ����
    DEV_HT=HT_CMD_HEARD_BEAT,       //��̨
    DEV_CK12A=CK12A_CMD_HEARD_BEAT,       //12A�̿�
    DEV_SPQ12A=SPQ12A_CMD_HEARD_BEAT       //12A������
};
struct DeviceInfo//�豸ip port
{
	int id;
	QString ip;
	int port;
	QString note;//��ע
	int onlineflag;//���߱�ʶ ����������ʹ�� ��֤�����豸onlineflag��| & �ܹ�����
	int heartcmd;//������������
};

//����ϵͳ�Լ�����Զ�������
// extern int systemclass;
 extern int automatictestingclass;
 extern int missiletype;          //��������

 extern int hearBeat_CK;       //ʶ��̿�������
 extern int hearBeat_CK20T;       //ʶ����һ���̿�������
 extern int hearBeat_SPQ;      //ʶ��������������
 extern int hearBeat_HT;       //ʶ��̨������
 extern int hearBeat_ZJ;       //ʶ���Լ�ģ����������
 extern int end_test;          //����ѭ������

#endif
