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

#define UDP_HEADER_CRC_SIZE 4//crc 4个字节
#define UDP_HEADER_CMD_SIZE 4//命令字 4个字节
#define UDP_HEADER_LEN  8


#define  WIDTH 1280
#define  HEIGHT 1024
#define  DLG_WIDTH 514
#define  DLG_HEIGHT 425
#define  DLG_WIDTH2 400
#define  DLG_HEIGHT2 320
#define MAX_BUFFER  20480

#define M_PORT 9000  //综合测控软件端口
typedef struct  MsgData
{
	int MsgId;
	int MsgLen;
	char* msgBuf;
}*PMsgData;
enum TestType
{
	ATT_SYS = 1,//系统自检
	ATT_AUTO=2,//自动测试
};

//系统自检类型
enum SysteSelfTest
{
    SELF_TEST=7,
    AIRTIGHTNESS_INSPECTION=2,
};

//自动测试的类型
enum AutoTestType
{
    SIGNLE_TEST = 1,//单项测试
    INS_TEST = 2,//惯导测试
    MULT_TEST = 3,//综合测试
    INTEGRATED_TESTING=10,
    ZERORETURN_STEERGEAR=11, //舵机回零
};
struct AutoTestFileInfo
{
	int unitType;//测试单元 系统自检 单项测试 综合测试 惯导测试
	QString unitName;//
	int modeType;//测试方式 连续测试 单项测试
	QString modeName;//测试方式
	QString filetm;//yyyyMMddhhmmss
	QString startDt;//开始日期 年月日
	QString startTm;//开始时间 时分秒
	QString endTm;//结束时间 
	QString missileType;//导弹型号
	QString missileName;//弹号
};
enum AUTO_DATA_TYPE
{
	AUTO_TYPE_SIMULATOR = 1,//自我模拟
	AUTO_TYPE_UDP = 2,//udp获取
};

struct AutoTestData
{
	int id;
	int num;
	int datatype;//数据类型 对应于下拉表的索引
	int type;//1 自我模拟 2:udp获取
	QString name;
	QString standardname;
	int standardtype;//数据类型 1：范围值 2：固定值
	float standardval;
	float min;
	float max;
	QString val;
	QString unit;
	int tm;//延时的时间间隔 单位是s
	int content;
	QString tip;
};
struct AutoTestList
{
	int id;
	QString note;
	QString autoVal;//默认值 从数据库读取
	int type;//类型 1：模拟 2：真实

	QLabel* val;
};

//各个硬件设备的ip port的序列号 对应于表DeviceList的id
enum DEV_ID
{
	DEV_CK = CK_CMD_HEARD_BEAT,//程控
	DEV_ZHDY = ZHDY_CMD_HEARD_BEAT,//综合电源
	DEV_HEC = HEC_CMD_HEARD_BEAT,//九轴传感器
	DEV_RYJCY = RYJCY_CMD_HEARD_BEAT,//燃油检测仪
	DEV_SXZPDY= SXZPDY_CMD_HEARD_BEAT,//三相中频电源
	DEV_SPQ=SPQ_CMD_HEARD_BEAT,//适配器
	DEV_DHXHMNQ=DHXHMNQ_CMD_HEARD_BEAT,//导航信号模拟器
	DEV_KJGXSMNQ=KJGXSMNQ_CMD_HEARD_BEAT,//可见光下视模拟器
	DEV_LDGDB=LDGDB_CMD_HEARD_BEAT,//雷达高度表
	DEV_Dan2=Dan2_CMD_HEARD_BEAT,//弹2
	DEV_Dan = Dan_CMD_HEARD_BEAT,//弹
    DEV_ZJ=ZJ_CMD_HEARD_BEAT,  //自检模拟器
    DEV_HT=HT_CMD_HEARD_BEAT,       //滑台
    DEV_CK12A=CK12A_CMD_HEARD_BEAT,       //12A程控
    DEV_SPQ12A=SPQ12A_CMD_HEARD_BEAT       //12A适配器
};
struct DeviceInfo//设备ip port
{
	int id;
	QString ip;
	int port;
	QString note;//备注
	int onlineflag;//在线标识 给导调发送使用 保证所有设备onlineflag用| & 能够区分
	int heartcmd;//心跳的命令字
};

//区分系统自检类和自动测试类
// extern int systemclass;
 extern int automatictestingclass;
 extern int missiletype;          //导弹类型

 extern int hearBeat_CK;       //识别程控心跳包
 extern int hearBeat_CK20T;       //识别另一个程控心跳包
 extern int hearBeat_SPQ;      //识别适配器心跳包
 extern int hearBeat_HT;       //识别滑台心跳包
 extern int hearBeat_ZJ;       //识别自检模拟器心跳包
 extern int end_test;          //结束循环测试

#endif
