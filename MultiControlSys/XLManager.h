#ifndef XLMANAGER_HEADER_H
#define XLMANAGER_HEADER_H
#pragma once
#include <QObject>
#include <QMap>
#include "Packet.h"
#include "ITask.h"
//sqlite ���ݹ���
class XLManager : public QObject
{
    Q_OBJECT

public:
    XLManager(QObject *parent);
    ~XLManager();

public:
    static XLManager* m_pInstance;

    //����ʵ����ȡ���� Ψһ�Ķ���ָ��
    static XLManager* GetInstance();

private:
    void LoadXL();
    void LoadItems();
    void LoadDevice();
public:
    QList<ITask*> m_lstTasks;//testitemsdlg��ѡ���������list

    //ϵͳ�Լ�->ϵͳ�Լ�
    QMap<int,QList<AutoTestData>> m_lstSystemselftest;//���ݿ�Systemselftest��
    //ϵͳ�Լ�->���ܼ��
    QMap<int,QList<AutoTestData>> m_lstAirtightnessinspection;//���ݿ�Airtightnessinspection��
    //ϵͳ�Լ���
    QMap<int,QList<AutoTestData>> m_lstMNLTDJC;//���ݿ�mnltdjc�� �ֵ��value��list ϵͳ�Լ�ʱ ���������±�������ʾ������
    //ϵͳ�Լ���Ŀ
    QList<QString> m_lstSelfCheckItems;
    //�Զ�����->�ۺϲ���
     QMap<int, QList< AutoTestData>> m_lstIntegratedtesting;
     //�Զ�����->�������
      QMap<int, QList< AutoTestData>> m_lstZeroreturnsteeringgear;
    //�Զ�������Ŀ
    QList<QString> m_lstAutoTestItems;
    //�Զ�����ʱ �����listwidget��
    QMap<int, AutoTestList> m_mapAutoTestList;
    //�Զ�����ʱ  �������-�������� ������
    QMap<int, QList< AutoTestData>> m_mapSINGLE_TEST;
    //�ߵ�����������
    QMap<int,AutoTestData> m_mapINS;//key�����ݿ��е�id
    //�Զ����� �ۺϲ���-���� ������
    QMap<int, QList<AutoTestData>> m_mapMULT_TEST;
    //����Ӳ���豸��ip��ַ keyֵ����������
    QMap<int, DeviceInfo> m_mapDevice;    

};
#endif
