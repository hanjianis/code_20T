#include "ISysCheckItem.h"
#include "MessageBoxDlg.h"
#include "MyToolTipDlg.h"
#include "SXZPDY_Manager.h"
#include "LDGDB_Manager.h"
#include "ZHDY_Manager.h"
#include "KJGXSMNQ_Manager.h"
#include "CK_Manager.h"
#include "DeviceOnlineManage.h"
ISysCheckItem::ISysCheckItem(int datatype,QObject *parent)
    : QObject(parent)
{
    pUDPServer = UDPServer::getInstance();
    pXL = XLManager::GetInstance();
    _datatype = datatype;
    _stop = false;
    connect(this, SIGNAL(UpdateCheckResult(int, int, float)), parent, SLOT(UpdateCheckResultCK(int, int, float)),Qt::DirectConnection);
    connect(this, SIGNAL(AddTaskItem(AutoTestData&)), parent, SLOT(AddTableWidget(AutoTestData&)));

    connect(this, SIGNAL(AddTaskItemResult(AutoTestData&)), parent, SLOT(AddAutoTestResult(AutoTestData&)));
    m_tmCkOnline = new QTimer();
    connect(m_tmCkOnline, SIGNAL(timeout()), this, SLOT(CkOnlineTimeout()));
}

ISysCheckItem::~ISysCheckItem()
{
}

void ISysCheckItem::StartCheck()
{
    qDebug() << "ISysCheckItem::StartCheck";

    if (_datatype == 4)//�ۺϵ�Դ
    {
        ZHDY_Manager::getInstance()->RequestPowerControl(1, 1);
    }
    if (_datatype == 5)//������Ƶ��Դ
    {
        SXZPDY_Manager::getInstance()->RequestPowerStatus();
        Sleep(100);//�ȴ�100ms �ȴ�udp���ݷ��� ��Ϊ100ms��Ȼ����
    }

    _tmid = startTimer(50);
    _lstindex = 0;
}

void ISysCheckItem::timerEvent(QTimerEvent *event)
{
    int tmid = event->timerId();
    if (tmid == _tmid)
    {
        killTimer(_tmid);
        _tmid = 0;
        if (_lstindex >= pXL->m_lstMNLTDJC[_datatype].size())
        {
            return;
            _stop = true;
        }
        AutoTestData& atd = pXL->m_lstMNLTDJC[_datatype][_lstindex];
        emit AddTaskItem(atd);
        if (_datatype == 4)//�ۺϵ�Դ ��������
        {
            ZHDY_Special();
        }
        if (_datatype == 7 && atd.id == 127)//�״�߶ȱ�
        {

            LDGDB_Manager::getInstance()->RequsetSelfCheck();
            m_tmCkOnline->start(1000);//��ʼ����״�߶ȱ��Ƿ񿪻��ɹ�
            //�ȴ�������ɼ�⵽������ �ڿ���	_tmid_result = startTimer(50);
            return;
        }
        _tmid_result = startTimer(50);
        return;

    }
    if (tmid == _tmid_result)
    {
        killTimer(_tmid_result);
        _tmid_result = 0;
        AutoTestData& atd = pXL->m_lstMNLTDJC[_datatype][_lstindex];
        emit AddTaskItemResult(atd);
        if (atd.id == 1)
        {
            MessageBoxDlg dlg(QString::fromLocal8Bit("�������豸"));
            dlg.exec();
            if (PLCManager::getInstance()->ConnectPLC() == true)
            {
                PLCManager::getInstance()->SetDQ20TStart();
//                Sleep(10000);
//                if(PLCManager::getInstance()->ReadDQ20T())                {

//                }else{
//                    MessageBoxDlg dlg3(QString::fromLocal8Bit("�򿪴������ݲ����ʧ�ܣ������Դ"));
//                    dlg3.exec();
//                    StopCheck();
//                    end_test=1;
//                    return;
//                }
            }else{
                MessageBoxDlg dlg3(QString::fromLocal8Bit("�򿪴������ݲ����ʧ�ܣ������Դ"));
                dlg3.exec();
                StopCheck();
                end_test=1;
                return;
            }

        }
        if (atd.id == 133)
        {
            KJGXSMNQ_Manager::getInstance()->RequsetSelfCheck();

            MyToolTipDlg dlg(QString::fromLocal8Bit("��ʾ��Ϣ"),QString::fromLocal8Bit("����ģ�����Ƿ�������"));
            dlg.exec();
            _stop = true;
            return;
        }
        _lstindex++;
        if (_lstindex >= pXL->m_lstMNLTDJC[_datatype].size())
        {
            _stop = true;
            if (_datatype == 7)//�״�߶ȱ�
            {
                //�رճ̿ع����� ��10·
                //CK_Manager* ck = new CK_Manager(nullptr);
            //	ck->RequestPowerControl(10, 0);
            }
            if (_datatype == 4)//4:�ۺϵ�Դ
            {
                ZHDY_Manager::getInstance()->RequestPowerControl(1, 0);//1:�ۺϵ�Դ��һ·��0�µ� 1����
                Sleep(200);
                for (unsigned char i=2;i<=8 ;i++)
                {
                    ZHDY_Manager::getInstance()->RequestPowerControl(i, 0);
                    Sleep(200);
                }
            }
            return;
        }
        _tmid = startTimer(50);
        return;
    }
}

bool ISysCheckItem::is_stop()
{
    return _stop;
}

void ISysCheckItem::StopCheck()
{
    killTimer(_tmid);
    _tmid = 0;
    killTimer(_tmid_result);
    _tmid_result = 0;
    _stop = true;
}

void ISysCheckItem::ZHDY_Special()
{
    //��֪��Ϊʲô������ ֻ�� 1 2 3 4 5 6 8·
    AutoTestData& atd = pXL->m_lstMNLTDJC[_datatype][_lstindex];
    if (_lstindex == 6)
        //����_lstindex �ж��ǵڼ�· index+1
    {
        //��7 8 ��·����
        ZHDY_Manager::getInstance()->RequestPowerControl(_lstindex + 1, 1);//�ϵ�
        Sleep(200);
        ZHDY_Manager::getInstance()->RequestPowerControl(_lstindex + 2, 1);//�ϵ�
    }
    else
        ZHDY_Manager::getInstance()->RequestPowerControl(_lstindex + 1, 1);//�ϵ�
    Sleep(200);//sleep�Ժ� ��ѯ��Դ״̬
    ZHDY_Manager::getInstance()->RequestPowerStatus();
}

void ISysCheckItem::CkOnlineTimeout()
{
    int flag = (DeviceOnlineManage::getInstance()->m_nDeviceOnlineFlag);
    bool bb = flag & 0x100;
    if((flag & 0x100) )//�������
    {
        LDGDB_Manager::getInstance()->RequestPowerControl(1000, 80);//����
        m_tmCkOnline->stop();//ֹͣ��ʱ��
        _tmid_result = startTimer(100);

    }
}
