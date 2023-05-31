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
    //������ӱ������
	connect(this, SIGNAL(AddTaskItem(AutoTestData&)), parent, SLOT(AddTableWidget(AutoTestData&)));

	connect(this, SIGNAL(AddTaskItemResult(AutoTestData&)), parent, SLOT(AddAutoTestResult(AutoTestData&)));
	m_tmCkOnline = new QTimer();
	connect(m_tmCkOnline, SIGNAL(timeout()), this, SLOT(CkOnlineTimeout()));   
/*
    connect(this, SIGNAL(sig_reminderinformation1(QString)), parent, SLOT(slot_reminderinformation1(QString)));
    connect(this, SIGNAL(sig_reminderinformation2(QString)), parent, SLOT(slot_reminderinformation2(QString)));
    connect(this, SIGNAL(sig_reminderinformation3(QString)), parent, SLOT(slot_reminderinformation3(QString)));
    connect(this, SIGNAL(sig_reminderinformation4(QString)), parent, SLOT(slot_reminderinformation4(QString)));
    connect(this, SIGNAL(sig_reminderinformation5(QString)), parent, SLOT(slot_reminderinformation5(QString)));
    connect(this, SIGNAL(sig_reminderinformation6(QString)), parent, SLOT(slot_reminderinformation6(QString)));
*/    
    connect(this, SIGNAL(sig_endTaskItem()), parent, SLOT(slot_endTaskItem()));
}

ISysCheckItem::~ISysCheckItem()
{
}
//��ʼ����
void ISysCheckItem::StartCheck()
{
	qDebug() << "ISysCheckItem::StartCheck";
    /*
    QString reminderinformation_1="���Կ�ʼ";
    emit sig_reminderinformation1(reminderinformation_1);
    Sleep(1000);
    QString reminderinformation_2="�̵���ģ���ʼ����...";
    emit sig_reminderinformation2(reminderinformation_2);
    Sleep(100);
    QString reminderinformation_3="��·����ģ���ʼ����...";
    emit sig_reminderinformation3(reminderinformation_3);
    Sleep(100);
    QString reminderinformation_4="1553Bģ���ʼ����...";
    emit sig_reminderinformation4(reminderinformation_4);
    Sleep(100);
    QString reminderinformation_5="IOģ���ʼ����...";
    emit sig_reminderinformation5(reminderinformation_5);
    Sleep(100);
    QString reminderinformation_6="��ѹ��ģ���ʼ����...";
    emit sig_reminderinformation6(reminderinformation_6);


    Sleep(5000);
    */
/*
	if (_datatype == 4)//�ۺϵ�Դ 
	{
		ZHDY_Manager::getInstance()->RequestPowerControl(1, 1);
	}
	if (_datatype == 5)//������Ƶ��Դ
	{
		SXZPDY_Manager::getInstance()->RequestPowerStatus();
		Sleep(100);//�ȴ�100ms �ȴ�udp���ݷ��� ��Ϊ100ms��Ȼ����
	}
*/
	_tmid = startTimer(50);
	_lstindex = 0;
}

//���淢�����ݿ�����
void ISysCheckItem::timerEvent(QTimerEvent *event)
{
	int tmid = event->timerId();

	if (tmid == _tmid)
	{
		killTimer(_tmid);
		_tmid = 0;
        if(systemclass==1)
        {
            if (_lstindex >= pXL->m_lstSystemselftest[_datatype].size())
            {
                return;
                _stop = true;
            }
            AutoTestData& atd = pXL->m_lstSystemselftest[_datatype][_lstindex];
            emit AddTaskItem(atd);
            if (atd.tm == 0)
                _tmid_result = startTimer(20);
            else
                _tmid_result = startTimer(atd.tm * 1000);

            /*
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
            */
        }

        if(systemclass==0)
        {
            if (_lstindex >= pXL->m_lstAirtightnessinspection[_datatype].size())
            {
                return;
                _stop = true;
            }
            AutoTestData& atd = pXL->m_lstAirtightnessinspection[_datatype][_lstindex];
            emit AddTaskItem(atd);

            if (atd.tm == 0)
               _tmid_result = startTimer(20);
            else
               _tmid_result = startTimer(atd.tm * 1000);


            /*
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
            */
        }
        //_tmid_result = startTimer(50);
		return;
		
	}
	if (tmid == _tmid_result)
	{
		killTimer(_tmid_result);
		_tmid_result = 0;
        if(systemclass==1)
        {
            AutoTestData& atd = pXL->m_lstSystemselftest[_datatype][_lstindex];
            emit AddTaskItemResult(atd);
            if(atd.id==180)
            {
                Sleep(2000);
                emit sig_endTaskItem();
            }
            /*
            if (atd.id == 1)
            {
                MessageBoxDlg dlg(QString::fromLocal8Bit("�������豸"));
                dlg.exec();
            }
            if (atd.id == 133)
            {
                KJGXSMNQ_Manager::getInstance()->RequsetSelfCheck();

                MyToolTipDlg dlg(QString::fromLocal8Bit("��ʾ��Ϣ"),QString::fromLocal8Bit("����ģ�����Ƿ�������"));
                dlg.exec();
                _stop = true;
                return;
            }
            */
            _lstindex++;
            if (_lstindex >= pXL->m_lstSystemselftest[_datatype].size())
            {
                _stop = true;
                /*
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
                */
                return;
            }
        }

        if(systemclass==0)
        {
            AutoTestData& atd = pXL->m_lstAirtightnessinspection[_datatype][_lstindex];
            emit AddTaskItemResult(atd);
            if(atd.id==5)
            {
                Sleep(2000);
                emit sig_endTaskItem();
            }
            /*
            if (atd.id == 1)
            {
                MessageBoxDlg dlg(QString::fromLocal8Bit("�������豸"));
                dlg.exec();
            }
            if (atd.id == 188)
            {
                KJGXSMNQ_Manager::getInstance()->RequsetSelfCheck();

                MyToolTipDlg dlg(QString::fromLocal8Bit("��ʾ��Ϣ"),QString::fromLocal8Bit("����ģ�����Ƿ�������"));
                dlg.exec();
                _stop = true;
                return;
            }
            */
            _lstindex++;
            if (_lstindex >= pXL->m_lstAirtightnessinspection[_datatype].size())
            {
                _stop = true;
                /*
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
                */
                return;
            }
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
