#pragma once

#include <QObject>
#include <QUdpSocket>
#include "Packet.h"
//udp server ???????
class UDPServer : public QObject
{
    Q_OBJECT

public:
    UDPServer(int port, QObject *parent);
    ~UDPServer();
private:
    static UDPServer* m_pInstance;
public:
    static UDPServer* getInstance();
private:
    MsgData m_msg;
    QUdpSocket* m_udpSocket;
    map<int, function<int(PMsgData)>> m_mapBusinessFunc;
public:
    void RegisterEvent(int msgid, function<int(PMsgData)> func);//??????
    //ip和端口号已经完成
    void WriteData(int msgid, char* buf,int buflen, QString strIp=QString("192.168.2.54"), int port=8089);//??????? ?????54 ?????豸????udp???? ???????????е?ip??????
    void WriteData(int msgid, QString strIp = QString("192.168.2.54"), int port=8089);
public slots:
    void udpRead();//读取数据
};
