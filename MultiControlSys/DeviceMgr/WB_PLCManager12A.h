#ifndef WB_PLCMANAGER12A_H
#define WB_PLCMANAGER12A_H

#include <qobject.h>
#include "snap7.h"
//微波12APLC
class WB_PLCManager12A : public QObject
{
    Q_OBJECT
public:
    explicit WB_PLCManager12A();
private:
    static WB_PLCManager12A* m_pInstance;
    TS7Client *ptrPLC;
public:
    static WB_PLCManager12A* getInstance();
private:
    float GetFloat(unsigned char *buf,int len=4);
    bool GetBit(unsigned char buf, int bit);
public:
    bool ConnectPLC();
    bool DisConnectPLC();
    void SetWBStart( ); //设置微波测试启动
    bool ReadPLC();      //读plc数据

signals:

};

#endif // WB_PLCMANAGER12A_H

