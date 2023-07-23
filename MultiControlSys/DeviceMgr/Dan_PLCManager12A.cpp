#include "Dan_PLCManager12A.h"
#include <QDebug>
Dan_PLCManager12A*  Dan_PLCManager12A::m_pInstance = nullptr;

Dan_PLCManager12A::Dan_PLCManager12A()
{
    ptrPLC = new TS7Client();
}

Dan_PLCManager12A* Dan_PLCManager12A::getInstance()
{
    if (m_pInstance == nullptr)
        m_pInstance = new Dan_PLCManager12A();
    return m_pInstance;
}

float Dan_PLCManager12A::GetFloat(byte *buf, int len)
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

bool Dan_PLCManager12A::GetBit(byte buf, int bit)
{
    if (((buf >> bit) &(0x1)) == 1)
        return true;
    else
        return false;
}

bool Dan_PLCManager12A::ConnectPLC()
{
    int cnt = 0;
    while (0 !=ptrPLC->ConnectTo("192.168.2.17", 0, 1)) {
        //qDebug() << "connect plc trying";
        cnt++;
        if (cnt > 10)
            return false;
    }
    //qDebug() << "connect plc success";
    return true;
}

bool Dan_PLCManager12A::DisConnectPLC()
{
    if (ptrPLC->Connected())
    {
        ptrPLC->Disconnect();
    }
    return true;
}

//启动弹翼动作信号
void Dan_PLCManager12A::SetDanStart( )
{
    //M100.0
    if (ptrPLC->Connected())
    {
        const int Len = 1;
        byte buff[Len] = { 0 };
        buff[0] = 0x1 << 0;
       // ptrPLC->DBWrite(1, 0, Len, buff);
        ptrPLC->MBWrite(100, Len, &buff[0]);   //或许不好使

    }

}

//12A都位置
bool Dan_PLCManager12A::ReadPLC()
{
    //	Q0.0
    if (ptrPLC->Connected())
    {
        const int Len = 1;
        byte buff[Len] = { 1 };

        ptrPLC->MBRead(0, Len, buff);          //或许不好使
        qDebug()<<"弹PLC读取  "<<buff[0];
        //return true;
        return GetBit(buff[0], 0);
    }
    return false;
}
