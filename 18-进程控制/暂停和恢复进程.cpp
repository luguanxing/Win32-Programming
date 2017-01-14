#include <windows.h>
#include <Tlhelp32.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <string>
#include <iostream>

typedef  DWORD (WINAPI *SUSPENDPROCESS)(HANDLE);    //使用未公开API函数
typedef  DWORD (WINAPI *RESUMEPROCESS)(HANDLE);

SUSPENDPROCESS SuspendProcess;
RESUMEPROCESS ResumeProcess;


int ProcProcess(LPWSTR lpFillName) {
	PROCESSENTRY32	stProcess;
	stProcess.dwSize = sizeof (PROCESSENTRY32);
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot ==NULL ) {		 //创建进程快照失败
		return 0;
	}

	bool isfound = false;
	BOOL bLoop = Process32First(hSnapShot, &stProcess);
	while (bLoop) {
		CharLower(stProcess.szExeFile);
		if (0 == lstrcmp(lpFillName, stProcess.szExeFile)) {
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, stProcess.th32ProcessID);
			if (NULL == hProcess) {		 //打开进程失败
				return 0;
			}
			isfound = true;
			SuspendProcess(hProcess);
			::MessageBox(NULL,_T("目标已冻结"), _T("确认"), MB_ICONINFORMATION);
			::Sleep(5000);

			int ret = ::MessageBox(NULL,_T("如何处理选择目标进程?YES关闭NO恢复"), _T("确认"), MB_YESNO | MB_ICONQUESTION);		//冻结或恢复进程,这里好像如果不连着冻结马上恢复的话就恢复不了
			if (IDYES == ret) {				 //关闭
				TerminateProcess(hProcess, 0);
			} else {									 //不关闭, 恢复挂起状态
				lpFillName[0] = 0;
				ResumeProcess(hProcess);
			}
			CloseHandle(hProcess);
		}
		bLoop = Process32Next(hSnapShot, &stProcess);
	}
	if (!isfound)
		::MessageBox(NULL,_T("找不到目标"), _T("失败"), MB_ICONINFORMATION);
	CloseHandle(hSnapShot); //关闭进程快照
	return 1;
}

HINSTANCE InitDll() {
	HINSTANCE hDllInstance = LoadLibrary(_T("NTDLL.DLL"));	//加载nt.dll
	if (hDllInstance == NULL) {
		MessageBox(NULL, _T("NTDll.dll文件丢失或装载失败, 程序功能无法实现"), _T("失败"), MB_ICONERROR);
		return NULL;
	}
   
	SuspendProcess = (SUSPENDPROCESS)GetProcAddress(hDllInstance, "ZwSuspendProcess");	//加载SuspendProcess
	if (NULL == SuspendProcess) {
		MessageBox(NULL, _T("ntdll.dll打不到函数ZwSuspendProcess"), _T("失败"), MB_ICONERROR);
		CloseHandle(hDllInstance);
		return NULL;
	}
   
	ResumeProcess = (RESUMEPROCESS)GetProcAddress(hDllInstance, "ZwResumeProcess");	//加载ResumeProcess
	if (NULL == ResumeProcess) {
		MessageBox(NULL, _T("ntdll.dll打不到函数ResumeProcess"), _T("失败"), MB_ICONERROR);
		CloseHandle(hDllInstance);
		return NULL;
	}
	return hDllInstance;
}

void Exit(HINSTANCE hDllInstance) {
	FreeLibrary(hDllInstance);
}

int main() {
	WCHAR lpFileName[MAX_PATH];
	CHAR buff[MAX_PATH];

	printf("输入进程名称:\n");
	scanf("%s", buff);
	MultiByteToWideChar (CP_ACP, 0, buff, -1, lpFileName, MAX_PATH);

	CharLower(lpFileName);	//转成小写
   
	HINSTANCE hDllInstance = InitDll();

	ProcProcess(lpFileName);

	Exit(hDllInstance);
	return 0;
}
