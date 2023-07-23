#pragma once
#include <qobject.h>
#include "snap7.h"
class PLCManager :
	public QObject
{
public:
	PLCManager();
private:
	static PLCManager* m_pInstance;
	TS7Client* ptrPLC;
public:
	static PLCManager* getInstance();
private:
	float GetFloat(unsigned char* buf, int len = 4);
	bool GetBit(unsigned char buf, int bit);
public:
	bool ConnectPLC();
	bool DisConnectPLC();
	void SetSingleStart();//设置单项测试启动
	void SetSingleStop();
	void SetMulStart();//设置综合测试开始
	void SetMulStop();//设置综合测试结束
	bool Read100KPaIsEnd();//单项测试时 100kpa测试结束标识
	bool Read60KPaIsEnd();//单项测试时 80kpa测试结束标识
	bool Read20KPaIsEnd();//单项测试时 20kpa测试结束标识
	bool Read1MinValid();//1分钟泄漏合格true
	bool Read1MinUnValid();//1分钟泄漏不合格true
	float ReadDongYa();//动压
	float ReadJingYa();//静压
	float ReadZongYa();//总压
	bool ReadMulIsEnd();//综合测试是否结束
    void SetDQ20TStart( );   //20T大气
    void SetDQ12AStart( );  //12A大气
    bool ReadDQ12A();
    bool ReadDQ20T();
};