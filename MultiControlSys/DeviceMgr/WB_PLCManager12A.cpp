#include "WB_PLCManager12A.h"
#include <QDebug>
WB_PLCManager12A*  WB_PLCManager12A::m_pInstance = nullptr;
WB_PLCManager12A::WB_PLCManager12A()
{
    ptrPLC = new TS7Client();
}

WB_PLCManager12A* WB_PLCManager12A::getInstance()
{
    if (m_pInstance == nullptr)
        m_pInstance = new WB_PLCManager12A();
    return m_pInstance;
}

float WB_PLCManager12A::GetFloat(byte *buf, int len)
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

bool WB_PLCManager12A::GetBit(byte buf, int bit)
{
    if (((buf >> bit) &(0x1)) == 1)
        return true;
    else
        return false;
}

bool WB_PLCManager12A::ConnectPLC()
{
    int cnt = 0;
    while (0 !=ptrPLC->ConnectTo("192.168.2.18", 0, 1)) {
        //qDebug() << "connect plc trying";
        cnt++;
        if (cnt > 10)
            return false;
    }
    //qDebug() << "connect plc success";
    return true;    
}

bool WB_PLCManager12A::DisConnectPLC()
{
    if (ptrPLC->Connected())
    {
        ptrPLC->Disconnect();
    }
    return true;
}

//启动微波
void WB_PLCManager12A::SetWBStart( )
{

    //DB10.DBX0.7
    if (ptrPLC->Connected())
    {
        const int Len = 1;
        byte buff[Len] = { 0 };
        buff[0] = 0x1 << 7;
        ptrPLC->DBWrite(10, 0, Len, buff);

    }
}

//12A都位置
bool WB_PLCManager12A::ReadPLC()
{
    //	DB10.DBX1.0
    if (ptrPLC->Connected())
    {
        const int Len = 1;
        byte buff[Len] = { 1 };

        ptrPLC->DBRead(10, 1, Len, buff);
        qDebug()<<"微波PLC读取  "<<buff[0];
       // return true;
        return GetBit(buff[0], 0);
    }
    return false;
}
