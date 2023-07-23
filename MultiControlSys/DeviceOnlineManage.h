#ifndef _DEVICE_ONLINE_MANAGE_H
#define _DEVICE_ONLINE_MANAGE_H

#pragma once

#include <QObject>
#include "Packet.h"
#include <QTimer>
//�豸����״̬�Ĺ��� udp�豸 ���ڼ�������udp�豸������ ���ϱ�������ʹ�õ�
//�߼��� ����������UDP���� �����ݿ��ҵ���Ӧ�����߱�ʶ ���͸����� �����������߱�ʶ�����豸
//���߱�ʶ ���豸�ǲ�ͬ�� �ǰ��ո�ռbitλ����� ����&����Ϳ��Խ�������

class DeviceOnlineManage : public QObject
{
	Q_OBJECT

public:
	DeviceOnlineManage(QObject *parent);
	~DeviceOnlineManage();
public:
	int m_nDeviceOnlineFlag;//���߱�ʶ �����豸���߱�ʶ��|����Ľ��
	int m_nPreDeviceOnlineFlag = 0;//��һ״̬ ��Ϊudp�豸�Ǹ��������ж��Ƿ����ߵ� ���Ա�����һ��״̬ ��״̬��һ��ʱ ���ϱ�������
	QTimer* m_Timer;//������������״̬�Ķ�ʱ��
private:
	static DeviceOnlineManage* m_pInstance;//��̬����
public:
	static DeviceOnlineManage* getInstance();//��ȡ����ʵ��
public:
	int ParseMsgHeartBeat(PMsgData pPacket);//��������
public slots:
	void on_timeout();//��ʱ���ص�
};
#endif
