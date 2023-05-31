// SysService.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <iostream>

#include <tchar.h>
#include <windows.h>
#include <winsock.h>
//#include "ServiceMsg.pb.h"
//using namespace ServiceMsg;
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define SERVICE_NAME "srv_demo"
SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hServiceStatusHandle;
int uaquit;
FILE* filelog;
SOCKET  s_server;
char recv_buf[1024] = { 0 };
#define PACKET_HEADER_DATALENGTH_SIZE     4
#define PACKET_HEADER_VERIFYCODE_SIZE     2
#define PACKET_HEADER_MSGID_SIZE          4
#define PACKET_HEADER_SIZE                10
DWORD WINAPI srv_core_thread(LPVOID para)
{
	int i = 0;
	while (1)
	{
		if (uaquit)
		{
			break;
		}
		int recv_len = recv(s_server, recv_buf, 1024, 0);
		if (recv_len < 0)
		{
			int nDataLen = 0;
			unsigned short nVerifyCode = 0;
			int nMsgId = 0;
			int npos = 0;
		//	fprintf(filelog, "srv_core_thread22 run time count:%d\n", i++);
			memcpy(&nDataLen, recv_buf + npos, PACKET_HEADER_DATALENGTH_SIZE);
			nDataLen = ntohl(nDataLen);
			npos += PACKET_HEADER_DATALENGTH_SIZE;
			memcpy(&nVerifyCode, recv_buf + npos, PACKET_HEADER_VERIFYCODE_SIZE);
			nVerifyCode = ntohs(nVerifyCode);
			npos += PACKET_HEADER_VERIFYCODE_SIZE;
			memcpy(&nMsgId, recv_buf + npos, PACKET_HEADER_MSGID_SIZE);
			nMsgId = ntohl(nMsgId);
			npos += PACKET_HEADER_MSGID_SIZE;

			fprintf(filelog, "srv_core_thread22 run time count:%d\n", nMsgId);
		}
		else
		{
		//	fprintf(filelog, "srv_core_thread11111 run time count:%d\n", i++);
		}
	}
	/*{
		if (uaquit)
		{
			break;
		}
		fprintf(filelog, "srv_core_thread run time count:%d\n", i++);
		Sleep(5000);
	}*/
	return NULL;
}

void WINAPI ServiceHandler(DWORD fdwControl)
{
	switch (fdwControl)
	{
	case SERVICE_CONTROL_STOP:
	case SERVICE_CONTROL_SHUTDOWN:
		ServiceStatus.dwWin32ExitCode = 0;
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		ServiceStatus.dwCheckPoint = 0;
		ServiceStatus.dwWaitHint = 0;
		uaquit = 1;
		//add you quit code here
		if (filelog != NULL)
			fclose(filelog);
		closesocket(s_server);
		break;
	default:
		return;
	};
	if (!SetServiceStatus(hServiceStatusHandle, &ServiceStatus))
	{
		DWORD nError = GetLastError();
	}
}
void initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
	}
	else {
		cout << "初始化套接字库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息

}
void WINAPI service_main(int argc, char** argv)
{
	ServiceStatus.dwServiceType = SERVICE_WIN32;
	ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE;
	ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;
	hServiceStatusHandle = RegisterServiceCtrlHandler(_T(SERVICE_NAME), ServiceHandler);
	if (hServiceStatusHandle == 0)
	{
		DWORD nError = GetLastError();
	}
	//add your init code here
	filelog = fopen("d:\\test.txt", "w");
	
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	initialization();
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(9000);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "服务器连接失败！" << endl;
		fprintf(filelog, "faied");
		WSACleanup();
	}
	else {
		cout << "服务器连接成功！" << endl;
		fprintf(filelog, "success");
	}
	

	//add your service thread here
	HANDLE task_handle = CreateThread(NULL, NULL, srv_core_thread, NULL, NULL, NULL);
	if (task_handle == NULL)
	{
		fprintf(filelog, "create srv_core_thread failed\n");
	}

	// Initialization complete - report running status 
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 9000;
	if (!SetServiceStatus(hServiceStatusHandle, &ServiceStatus))
	{
		DWORD nError = GetLastError();
	}
}
bool AddService()
{
	SERVICE_TABLE_ENTRY ServiceTable[2];

	ServiceTable[0].lpServiceName = (LPSTR)SERVICE_NAME;
	ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)service_main;

	ServiceTable[1].lpServiceName = NULL;
	ServiceTable[1].lpServiceProc = NULL;
	// 启动服务的控制分派机线程
	StartServiceCtrlDispatcher(ServiceTable);
	return true;
}

int main(int argc, const char *argv[])
{

	AddService();
	SC_HANDLE hSCManager = NULL; /*服务控制管理器句柄*/
	SC_HANDLE hService = NULL;     //服务句柄
	char szExePath[MAX_PATH] = "D:\\Working\\10_20T\\Code\\Debug\\SysService.exe";
	if ((hSCManager = OpenSCManager(NULL,  /*NULL表明是本地主机*/ NULL, /* 要打开的服务控制管理数据库，默认为空*/SC_MANAGER_CREATE_SERVICE/*创建权限*/)) == NULL)
	{
		std::cout << "openSCManager fail!" << std::endl;
		return 0;
	}
	//system("pause");
	//strcat_s(szExePath,sizeof("main.exe"),"main.exe");  //应用程序绝对路径
	if ((hService = CreateService(hSCManager,  //指向服务控制管理数据库的句柄
		(LPSTR)SERVICE_NAME,    //服务名
		"2222", //显示用的服务名
		SERVICE_ALL_ACCESS, //所有访问权限
		SERVICE_WIN32_OWN_PROCESS, //私有类型
		SERVICE_DEMAND_START, //自启动类型        
		SERVICE_ERROR_IGNORE, //忽略错误处理
		szExePath,  //应用程序路径
		NULL,
		NULL,
		NULL,
		NULL,
		NULL)) == NULL)
	{
		std::cout << " CreateService" << GetLastError() << std::endl;
		return 0;
	}
	if (StartService(hService, 0, NULL) == FALSE)
	{
		std::cout << "StartService failed:" << GetLastError() << std::endl;
		return 0;
	}
	std::cout << "Install service successfully" << std::endl;
	CloseServiceHandle(hService);  //关闭服务句柄
	CloseServiceHandle(hSCManager); //关闭服务管理数据库句柄
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
