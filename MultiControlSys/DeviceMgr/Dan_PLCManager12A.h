#ifndef DAN_PLCMANAGER12A_H
#define DAN_PLCMANAGER12A_H

#include <qobject.h>
#include "snap7.h"
//弹12APLC
class Dan_PLCManager12A : public QObject
{
    Q_OBJECT
public:
    explicit Dan_PLCManager12A();
private:
    static Dan_PLCManager12A* m_pInstance;
    TS7Client *ptrPLC;
public:
    static Dan_PLCManager12A* getInstance();
private:
    float GetFloat(unsigned char *buf,int len=4);
    bool GetBit(unsigned char buf, int bit);
public:
    bool ConnectPLC();
    bool DisConnectPLC();
    void SetDanStart( );   //启动导弹尾翼
    bool ReadPLC();      //读plc数据

signals:

};

#endif // DAN_PLCMANAGER12A_H
