#ifndef SPQ_MANAGER12A_H
#define SPQ_MANAGER12A_H

//适配器
#include <QObject>
#include "DeviceBase.h"
class SPQ_Manager12A: public DeviceBase
{
public:
    SPQ_Manager12A(QObject *parent);
    ~SPQ_Manager12A();
private:
    static SPQ_Manager12A* m_pInstance;
public:
    /*//使用了2-10位 0连接好 1没连接好   2---- X151   3---- X152
    //4---- 13X3
    //5---- X154
    //6---- X119
    //7---- X145
    //8---- X100-3X3
    //9---- X100-3X5
    //10---- X100-3X6
    */
    int _lineState = 0xFFC;//线路状态

public:
    static SPQ_Manager12A* getInstance();
public:
    int ParseMsgHeartBeat(PMsgData pPacket);
    int ParseMsgVersion(PMsgData pPacket);
    int ParseMsgPowerControl(PMsgData pPacket);
    bool CheckLineConnected();//检测适配器线连接状态  //2-10位 全部是0 返回true

public:// 请求方法
    void RequestVersion();
    void RequsetSelfCheck();
    //void RequestPowerControl();//num 编号 control 开关控制
  //  void RequestPowerControl(char num, char control);//num 编号 control 开关控制
};

#endif // SPQ_MANAGER12A_H
