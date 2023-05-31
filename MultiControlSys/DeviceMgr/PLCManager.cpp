#include "PLCManager.h"
#include <QDebug>
PLCManager*  PLCManager::m_pInstance = nullptr;
PLCManager::PLCManager()
{
	ptrPLC = new TS7Client();

}

PLCManager* PLCManager::getInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new PLCManager();
	return m_pInstance;
}

float PLCManager::GetFloat(byte *buf, int len)
{
	QByteArray array;
	array.resize(len);
	for (int i = 0; i < array.size(); i++)
	{
		array[i] = buf[len - 1 - i];
	}
	float aa;

	memcpy(&aa, array, 4);
	return aa;
}

bool PLCManager::GetBit(byte buf, int bit)
{
	if (((buf >> bit) &(0x1)) == 1)
		return true;
	else
		return false;
}

bool PLCManager::ConnectPLC()
{
	int cnt = 0;
	while (0 !=ptrPLC->ConnectTo("192.168.2.12", 0, 1)) {
		//qDebug() << "connect plc trying";
		cnt++;
		if (cnt > 10)
			return false;
	}
	//qDebug() << "connect plc success";
	return true;



	//int res = ptrPLC->ConnectTo("192.168.2.12", 0, 1);
	//if (res == 0)//success
	//{
	//	qDebug() << "connect plc success";
	//	return true;
	//}
	//return false;
}

bool PLCManager::DisConnectPLC()
{
	if (ptrPLC->Connected())
	{
		ptrPLC->Disconnect();
	}
	return true;
}

void PLCManager::SetSingleStart( )
{
	
	//DB6.DBX161.0
	if (ptrPLC->Connected())
	{
		const int Len = 1;
		byte buff[Len] = { 0 };
		buff[0] = 0x1 << 0;
		ptrPLC->DBWrite(6, 161, Len, buff);

	}
}

void PLCManager::SetSingleStop()
{
	//DB6.DBX161.4
	if (ptrPLC->Connected())
	{
		const int Len = 1;
		byte buff[Len] = { 0 };
		buff[0] = 0x1 << 4;
		ptrPLC->DBWrite(6, 161, Len, buff);
		
	}
}

void PLCManager::SetMulStart()
{
	//DB6.DBX161.3
	if (ptrPLC->Connected())
	{
		const int Len = 1;
		byte buff[Len] = { 0 };
		buff[0] = 0x1 << 3;
		ptrPLC->DBWrite(6, 161, Len, buff);

	}
}

void PLCManager::SetMulStop()
{
	//DB6.DBX161.5
	if (ptrPLC->Connected())
	{
		const int Len = 1;
		byte buff[Len] = { 0 };
		buff[0] = 0x1 << 5;
		ptrPLC->DBWrite(6, 161, Len, buff);

	}
}

bool PLCManager::Read100KPaIsEnd()
{
	//DB6.DBX78.0
	if (ptrPLC->Connected())
	{
		const int Len = 1;
		byte buff[Len] = { 0 };

		ptrPLC->DBRead(6,78, Len, buff);
		return GetBit(buff[0],0);
	}
	return false;
}

bool PLCManager::Read60KPaIsEnd()
{
	//DB6.DBX90.0
	if (ptrPLC->Connected())
	{
		const int Len = 1;
		byte buff[Len] = { 0 };

		ptrPLC->DBRead(6, 90, Len, buff);
		return GetBit(buff[0], 0);
	}
	return false;

}

bool PLCManager::Read20KPaIsEnd()
{
	//DB6.DBX166.2
	if (ptrPLC->Connected())
	{
		const int Len = 1;
		byte buff[Len] = { 0 };

		ptrPLC->DBRead(6, 166, Len, buff);
		return GetBit(buff[0], 2);
	}
	return false;
}

bool PLCManager::Read1MinValid()
{
	//DB6.DBX161.1
	if (ptrPLC->Connected())
	{
		const int Len = 1;
		byte buff[Len] = { 0 };

		ptrPLC->DBRead(6, 161, Len, buff);
		return GetBit(buff[0], 1);
	}
	return false;
}

bool PLCManager::Read1MinUnValid()
{
	//DB6.DBX161.2
	if (ptrPLC->Connected())
	{
		const int Len = 1;
		byte buff[Len] = { 0 };

		ptrPLC->DBRead(6, 161, Len, buff);
		return GetBit(buff[0], 2);
	}
	return false;
}

float PLCManager::ReadDongYa()
{
	//DB3.DBD66
	if (ptrPLC->Connected())
	{
		const int Len = 4;
		byte buff[Len] = { 0 };

		ptrPLC->DBRead(3, 66, Len, buff);
		
		return GetFloat(buff);
	}
	return 0.0;
}

float PLCManager::ReadJingYa()
{
	//DB3.DBD58
	if (ptrPLC->Connected())
	{
		const int Len = 4;
		byte buff[Len] = { 0 };

		ptrPLC->DBRead(3, 58, Len, buff);

		return GetFloat(buff);
	}
	return 0.0;
}

float PLCManager::ReadZongYa()
{
	//	DB3.DBD74

	if (ptrPLC->Connected())
	{
		const int Len = 4;
		byte buff[Len] = { 0 };

		ptrPLC->DBRead(3, 74, Len, buff);

		return GetFloat(buff);
	}
	return 0.0;
}

bool PLCManager::ReadMulIsEnd()
{
	//DB6.DBX154.3
	if (ptrPLC->Connected())
	{
		const int Len = 1;
		byte buff[Len] = { 0 };

		ptrPLC->DBRead(6, 154, Len, buff);
		return GetBit(buff[0], 3);
	}
	return false;
}
