#include <windows.h>
#include <Tlhelp32.h>
#include <stdio.h>
#include <conio.h>

typedef  DWORD (WINAPI *SUSPENDPROCESS)(HANDLE);
typedef  DWORD (WINAPI *RESUMEPROCESS)(HANDLE);

SUSPENDPROCESS SuspendProcess;
RESUMEPROCESS ResumeProcess;


int ProcProcess(LPSTR lpFillName)
{
    PROCESSENTRY32    stProcess;
    stProcess.dwSize = sizeof (PROCESSENTRY32);

    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (NULL == hSnapShot) {
        return 0; //创建进程快照失败
    }

    BOOL bLoop = Process32First(hSnapShot, &stProcess);
    while (bLoop)
    {
        CharLower(stProcess.szExeFile);
        if (0 == lstrcmp(lpFillName, stProcess.szExeFile))
        {
            //MessageBox(NULL, (LPCTSTR)TEXT("有进程"), (LPCTSTR)TEXT("信息"), MB_OK | MB_ICONINFORMATION);
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, stProcess.th32ProcessID);
            if (NULL == hProcess) {
                //打开进程失败
                return 0;
            }
            SuspendProcess(hProcess);
            int ret = MessageBox(NULL, (LPCTSTR)TEXT("目标进程是否关闭?"), (LPCTSTR)TEXT("询问"), MB_YESNO | MB_ICONQUESTION);
            if (IDYES == ret) {
                //关闭
                TerminateProcess(hProcess, 0);
            } else {
                //不关闭, 取消进程挂起状态
                lpFillName[0] = 0;
                ResumeProcess(hProcess);
            }

            CloseHandle(hProcess);

        }
        bLoop = Process32Next(hSnapShot, &stProcess);
    }

    CloseHandle(hSnapShot); //关闭进程快照
    return 1;
}

HINSTANCE InitDll()
{
    HINSTANCE    hDllInstance = LoadLibrary((LPCSTR)TEXT("NTDLL.DLL"));
    if (NULL == hDllInstance) {
        MessageBox(NULL,
            (LPCSTR)TEXT("NTDll.dll文件丢失或装载失败, 程序功能无法实现"),
            (LPCSTR)TEXT("失败"), MB_OK | MB_ICONERROR);
        return NULL;
    }
   
    SuspendProcess = (SUSPENDPROCESS)GetProcAddress(hDllInstance, (LPCSTR)TEXT

("ZwSuspendProcess"));
    if (NULL == SuspendProcess) {
        MessageBox(NULL,
            (LPCSTR)TEXT("ntdll.dll打不到函数ZwSuspendProcess"),
            (LPCSTR)TEXT("失败"), MB_OK | MB_ICONERROR);
        CloseHandle(hDllInstance);
        return NULL;
    }
   
    ResumeProcess = (RESUMEPROCESS)GetProcAddress(hDllInstance, (LPCSTR)TEXT

("ZwResumeProcess"));
    if (NULL == ResumeProcess) {
        MessageBox(NULL,
            (LPCSTR)TEXT("ntdll.dll打不到函数ResumeProcess"),
            (LPCSTR)TEXT("失败"), MB_OK | MB_ICONERROR);
        CloseHandle(hDllInstance);
        return NULL;
    }
    return hDllInstance;
}

void Exit(HINSTANCE hDllInstance)
{
    FreeLibrary(hDllInstance);
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    while (TRUE)
    {
        ProcProcess((LPSTR)lpParameter);
        Sleep(100);
    }
    return 0;
}


int main(int argc, char* argv[])
{
    TCHAR    lpFileName[MAX_PATH];
    printf("请输入进程名称(会转成小写):");
    scanf("%s", lpFileName);

    CharLower(lpFileName);    //转成小写
   
    HINSTANCE hDllInstance = InitDll();

    HANDLE hThread = CreateThread(NULL, 0, ThreadProc, (LPVOID)lpFileName, NULL, NULL);
    CloseHandle(hThread);
    Sleep(20000);
    Exit(hDllInstance);
    return 0;
}