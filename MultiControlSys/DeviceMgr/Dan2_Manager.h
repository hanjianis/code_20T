#pragma once

#include <QObject>
#include "DeviceBase.h"
struct UTC_TIME{
	short Year;//
	char Month;//
	char Day;
	char Hour;
	char Minu;
	char Secon;
};
struct SateLiteInfo// 卫星信息 5 字节
{
	char Num;//卫星编号
	char heading;//仰角
	short pitch;//方位角度
	char ratio;//信噪比
};
//必须按照顺序
struct  GPS_Info
{
	char state;//定位状态
	UTC_TIME UTC;
	char EW;//E or W E：东 W：西
	float lon;//经度 
	char NS;//N or S N：北 S:南
	float lat;//纬度
	float height;// 海拔高度
	char GpsCnt;//可见卫星数
	SateLiteInfo gpsSate[12];//最多可以12个
	char BeiDouCnt;//北斗卫星可见数
	SateLiteInfo BeiDouSate[12];//最多12个
	char validSate;//用于定位的卫星数
	char validSateCnt;//定位的卫星编号数量
	char validSateNum[12];//用于定位的卫星编号 最多12个
};

class Dan2_Manager : public DeviceBase
{
	Q_OBJECT

public:
	Dan2_Manager(QObject *parent);
	~Dan2_Manager();
private:
	static Dan2_Manager* m_pInstance;

public:
	static Dan2_Manager* getInstance();
public:
	int ParseMsgPowerControl(PMsgData pPacket);//卫星定位信息
	int ParseMsgPowerStatus(PMsgData pPacket);//景象图片识别信息
public:// 请求方法
	void RequestVersion();
	void RequsetSelfCheck();
	void RequestPowerControl();//
	void RequestPowerStatus();

public:
	int _imageFlag = 0;//图像识别标识景象图片识别标识（1字节）。景象图片识别标识；1：景象图片1，2：景象图片2，0：未匹配。
	GPS_Info _gpsInfo;
};
