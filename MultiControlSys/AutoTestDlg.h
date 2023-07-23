#ifndef AUTO_TEST_DLG_H_
#define  AUTO_TEST_DLG_H_
#pragma once

#include <QDialog>
#include "ui_AutoTestDlg.h"
#include "Packet.h"
#include "XLManager.h"
#include "ITask.h"
#include "TestItemsDlg.h"
#include "ExcelOperate.h"
#include "TCPClient.h"
#include "ISysCheckItem.h"
#include "UDPServer.h"
#include <QTimer>
#include "INSTestOBJ.h"
#include "AutoTestWidget.h"
#include "MultTestOBJ.h"
class AutoTestDlg : public QDialog
{
    Q_OBJECT
public:
    AutoTestDlg(int nType, QWidget *parent = Q_NULLPTR);
    ~AutoTestDlg();

private:
    Ui::AutoTestDlg ui;
    AutoTestWidget* m_at = nullptr;//����������widget
    int _type;
    int _tmid;//ϵͳ�Լ�Ķ�ʱ��
    int _tmid_auto;//�Զ����ԵĶ�ʱ��
    //

    INSTestOBJ* _insTest = nullptr;//�ߵ������� �Լ������Լ����߼�
    MultTestOBJ* _multTest = nullptr;

    int _lstindex;//������
    int _startTickCount;//���ڲ���ʱ ʹ��ʱ��ĸ���
    int _correct_count = 0;//��ȷ����
    int _error_count = 0;// ��������
    int _datatype;//�������� ���ڲ���ʱ ��ͬ���Ե��������
    QList<ISysCheckItem*> _lstTaskDataType;//ϵͳ�Լ�ʱ Ҫ�Լ����������ID����
    XLManager* pXL;//������ ����sqlite������ ��һЩ��������
    TestItemsDlg* m_itemsdlg;//�Զ�����->������Ե�������ѡ��Ի��� TestItemDlg.ui
    ExcelOperate* excelOperate;//excel�Ĳ���
    TCPClient* _tcpClient;//tcp client ���ں͵���ͨ�� ������
    UDPServer* _udpServer;//udp server ������
    QTimer* m_tmTimer;//����ϵͳʱ�����
    QTimer* m_tmTestUseTm;//���ڲ���ʹ��ʱ��


public:
    virtual void timerEvent(QTimerEvent *event);//��ʱ���Ļص�
public slots:
    void AddTableWidget(AutoTestData& atd);//��������tabelwidget
    void AddAutoTestResult(AutoTestData& atd);//�������������tabelwidget
    void on_quit_clicked();//fanhui
    void on_btnstart_clicked();//��ʼ��ť
    void on_toolButton_2_clicked();//��ͣ
    void on_comboBox_currentIndexChanged(int index);//���Ե�Ԫ��ѡ��
    void on_comboBox_2_currentIndexChanged(int index);//������Ŀ��ѡ��
    void UpdateToolTip(QString str);//������ʾ��Ϣ
    void RecvStopInsSlot();//�ߵ����Խ���
    void RecvStopMultiSlot();//�ۺϲ��Խ���
    void on_testBtn_clicked();
    void on_testBtn2_clicked();
    void on_testBtn3_clicked();
    void on_testBtn4_clicked();
public slots:
    void UpdateCheckResultCK(int datatype, int nId, float fVal);//���³̿ؽ��
    void on_timeout();//��ʱ���ص�
    void SetTestUseTm();//���ò���ʹ��ʱ���

public slots://����Ŀ�����������жϡ�ʹ��
    void DQ_Failed();
private:
    void MNLTDJC();//ϵͳ�Լ�ķ���
    void CreateExcel();//����ʱ���ɱ���
    void InsertSheet(AutoTestData atd);//���һ����excel

    void updateResult();//���½��
};
#endif
