#include "UDPTest.h"
#include <QtWidgets/QApplication>
void getcpuid(unsigned int CPUInfo[4], unsigned int InfoType);
void getcpuidex(unsigned int CPUInfo[4], unsigned int InfoType, unsigned int ECXValue);
QString get_cpuId();
#include <QMessageBox>
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
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
	QMessageBox::information(nullptr, "title", get_cpuId(), QMessageBox::Yes);
    UDPTest w;
    w.show();
    return a.exec();
}
