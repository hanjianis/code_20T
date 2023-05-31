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
	TS7Client *ptrPLC;
public:
	static PLCManager* getInstance();
private:
    float GetFloat(unsigned char *buf,int len=4);
    bool GetBit(unsigned char buf, int bit);
public:
	bool ConnectPLC();
	bool DisConnectPLC();
	void SetSingleStart();//���õ����������
	void SetSingleStop();
	void SetMulStart();//�����ۺϲ��Կ�ʼ
	void SetMulStop();//�����ۺϲ��Խ���
	bool Read100KPaIsEnd();//�������ʱ 100kpa���Խ�����ʶ
	bool Read60KPaIsEnd();//�������ʱ 80kpa���Խ�����ʶ
	bool Read20KPaIsEnd();//�������ʱ 20kpa���Խ�����ʶ
	bool Read1MinValid();//1����й©�ϸ�true
	bool Read1MinUnValid();//1����й©���ϸ�true
	float ReadDongYa();//��ѹ
	float ReadJingYa();//��ѹ
	float ReadZongYa();//��ѹ
	bool ReadMulIsEnd();//�ۺϲ����Ƿ����

};

