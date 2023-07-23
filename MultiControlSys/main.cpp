#include "MultiControlSys.h"
#include <QtWidgets/QApplication>
#include "SelectMissleDlg.h"
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "AutoTestDlg.h"
#include "HistoryDlg.h"
#include "UDPServer.h"
#include "DeviceOnlineManage.h"
#include "InsConfigDlg.h"
#include "GlobalManager.h"
#include "DeviceMgr/ZHDY_Manager.h"
#include "DeviceMgr/RYJCY_Manager.h"
#include "DeviceMgr/SXZPDY_Manager.h"
#include "DeviceMgr/SPQ_Manager.h"
#include "DeviceMgr/DHXHMNQ_Manager.h"
#include "DeviceMgr/KJGXSMNQ_Manager.h"
#include "DeviceMgr/LDGDB_Manager.h"
#include "DeviceMgr/Dan2_Manager.h"
#include "DeviceMgr/Dan_Manager.h"
#include "InputTemperatureDlg.h"
//#using "../Debug/Sharp7Library.dll"
//using namespace Sharp7;
#include "DeviceMgr/PLCManager.h"
#include "DeviceMgr/HecDataManager.h"
#pragma comment(lib,"snap7/snap7.lib")
#include "snap7.h"

#pragma region  CPU��ȡ
void getcpuid(unsigned int CPUInfo[4], unsigned int InfoType);
void getcpuidex(unsigned int CPUInfo[4], unsigned int InfoType, unsigned int ECXValue);
QString get_cpuId();

QString get_cpuId()
{
	QString cpu_id = "";
	unsigned int dwBuf[4] = { 0 };
	unsigned long long ret = 0;
	getcpuid(dwBuf, 1);
	ret = dwBuf[3];
	ret = ret << 32;

	QString str0 = QString::number(dwBuf[3], 16).toUpper();
	QString str0_1 = str0.rightJustified(8, '0');//��һ�����˼��ǰ�油0����������������������ﶼ������
	QString str1 = QString::number(dwBuf[0], 16).toUpper();
	QString str1_1 = str1.rightJustified(8, '0');//���������ǰ�油0�����򲻻���������
	//cpu_id = cpu_id + QString::number(dwBuf[0], 16).toUpper();
	cpu_id = str0_1 + str1_1;
	return cpu_id;
}

void getcpuid(unsigned int CPUInfo[4], unsigned int InfoType)
{
#if defined(__GNUC__)// GCC
	__cpuid(InfoType, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#elif defined(_MSC_VER)// MSVC
#if _MSC_VER >= 1400 //VC2005��֧��__cpuid
	__cpuid((int*)(void*)CPUInfo, (int)(InfoType));
#else //����ʹ��getcpuidex
	getcpuidex(CPUInfo, InfoType, 0);
#endif
#endif
}
void getcpuidex(unsigned int CPUInfo[4], unsigned int InfoType, unsigned int ECXValue)
{
#if defined(_MSC_VER) // MSVC
#if defined(_WIN64) // 64λ�²�֧���������. 1600: VS2010, ��˵VC2008 SP1֮���֧��__cpuidex.
	__cpuidex((int*)(void*)CPUInfo, (int)InfoType, (int)ECXValue);
#else
	if (NULL == CPUInfo)  return;
	_asm {
		// load. ��ȡ�������Ĵ���.
		mov edi, CPUInfo;
		mov eax, InfoType;
		mov ecx, ECXValue;
		// CPUID
		cpuid;
		// save. ���Ĵ������浽CPUInfo
		mov[edi], eax;
		mov[edi + 4], ebx;
		mov[edi + 8], ecx;
		mov[edi + 12], edx;
	}
#endif
#endif
}
#pragma endregion

int main(int argc, char *argv[])
{
	//qDebug() << get_cpuId();
#pragma region ��ʽ
	QApplication a(argc, argv);
	QFont f(QString::fromLocal8Bit("΢���ź�"), 12);

	a.setFont(f);
	//����qss�ļ�
	QFile qssFile(":/MultiControlSys/res/style.css");
	qssFile.open(QFile::ReadOnly); //��ֻ����ʽ��
	if (qssFile.isOpen())
	{
		QString qss = QLatin1String(qssFile.readAll());
		//QString paletteColor = qss.mid(20, 7);
		//qApp->setPalette(QPalette(QColor(paletteColor)));
		qApp->setStyleSheet(qss);
		qssFile.close();
	}
	a.setWindowIcon(QIcon(":/MultiControlSys/res/264.ico"));
	QStringList drivers = QSqlDatabase::drivers();

	QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
	drivers = QSqlDatabase::drivers();

	m_db.setDatabaseName(QApplication::applicationDirPath() + "/MultiControlsSys.db");//QApplication::applicationDirPath() + 
	if (!m_db.open()) {

		QSqlError err = m_db.lastError();

	}
#pragma endregion


	char buf[2] = { 0x01,0x00 };
	qDebug() << "==="<<buf[0];
	TCPClient::GetInstance();
	UDPServer::getInstance();
    DeviceOnlineManage::getInstance();
	//DHXHMNQ_Manager::getInstance()->RequestVersion();
//	LDGDB_Manager::getInstance()->RequestPowerControl(1500, 50);
	//LDGDB_Manager::getInstance()->RequestPowerControl(1000,80);
	//Dan_Manager::getInstance()->RequestLineInfo();
	//Dan_Manager::getInstance()->RequestSound(1);
	//Dan_Manager::getInstance()->RequestSound(2);
	//HecDataManager::getInstance()->GetHecData(200);//200ms��ʱ��ȡ
	//Dan_Manager::getInstance()->RequestPowerControl();
	//KJGXSMNQ_Manager::getInstance()->RequsetSelfCheck();

	//KJGXSMNQ_Manager::getInstance()->RequestPowerControl(1);

	//KJGXSMNQ_Manager::getInstance()->RequestPowerControl(2);
	//test 
	//Sleep(200);
	/*Dan_Manager::getInstance()->RequsetLamControl(1);
	Sleep(200);*/
	//Dan_Manager::getInstance()->RequsetLamControl(0);
	/*PLCManager::getInstance()->ReadZongYa();
	PLCManager::getInstance()->ReadJingYa();
	PLCManager::getInstance()->ReadDongYa();*/
	
	////test
	//for (int i = 0; i < 10; i++)
	//{
	//	ZHDY_Manager::getInstance()->RequestPowerControl(i+1, 0);
	//	Sleep(200);
	//}
#pragma region ����
	//AutoTestDlg dlg1(2);
	//dlg1.exec();
	SelectMissleDlg dlg;
	if (dlg.exec() == QDialog::Accepted)
	{
		MultiControlSys w;
		w.show();
		return a.exec();
	}
	else
	{
        TCPClient::GetInstance()->SendMsgID(eMsg_T_OnCloseApp);
		GlobalManager::getInstance()->SaveIni();
		exit(0);
		return 1;
	}

#pragma endregion

	

}
