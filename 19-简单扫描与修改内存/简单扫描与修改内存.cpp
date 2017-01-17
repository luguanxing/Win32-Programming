#include <windows.h>
#include <Tlhelp32.h>
#include <iostream>

#define MAXSIZE 5000

class CMemFinder {
	public:
		int m_dwlistnum;
		BOOL m_bfirst;
		HANDLE m_hprocess;
		DWORD m_dwlist[MAXSIZE];
		virtual BOOL ComparePage(DWORD dwBaseAddr, DWORD dwValue);

		CMemFinder();	//初始函数和析构函数
		CMemFinder(DWORD processid);
		CMemFinder(WCHAR *processname);
		CMemFinder(char &windowname);
		virtual ~CMemFinder();

		virtual void ShowList();	//操作方法
		virtual void set(DWORD processid);
		virtual void set(WCHAR *processname);
		virtual void set(char &windowname);
		virtual BOOL FindFirst(DWORD dwVaule);
		virtual BOOL FindNext(DWORD dwVaule);
		virtual BOOL modify(DWORD dwAddr, DWORD dwValue);
};

CMemFinder::CMemFinder() {
	m_dwlistnum = 0;
	m_hprocess = NULL;
}

CMemFinder::CMemFinder(DWORD processid) {		//根据进程id名寻找并打开进程
	m_dwlistnum = 0;
	m_hprocess = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	if (NULL ==m_hprocess) {
		printf( "打开进程失败\n");
		return;
	}
	printf( "打开进程成功\n");
}

CMemFinder::CMemFinder(WCHAR *processname) {		//根据进程名寻找并打开进程
	m_dwlistnum = 0;
	PROCESSENTRY32	stProcess;
	stProcess.dwSize = sizeof (PROCESSENTRY32);
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot ==NULL ) {
		return;
	}
	bool isfound = false;
	BOOL bLoop = Process32First(hSnapShot, &stProcess);
	while (bLoop && !isfound) {
		CharLower((LPWSTR)processname);
		CharLower(stProcess.szExeFile);
		if (0 == lstrcmp((LPCWSTR)processname, stProcess.szExeFile)) {
			m_hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, stProcess.th32ProcessID);
			if (NULL ==m_hprocess) {
				printf( "打开进程失败\n");
				return;
			}
			printf( "打开进程成功\n");
			isfound = true;
		}
		bLoop = Process32Next(hSnapShot, &stProcess);
	}
	if (!isfound)
		printf( "找不到目标\n");
}

CMemFinder::CMemFinder(char &windowname) {		//根据窗口名寻找并打开进程
	m_dwlistnum = 0;
	WCHAR wbuff[255];
	int dwNum=sizeof(windowname);
	MultiByteToWideChar (CP_ACP, 0, (LPCSTR)windowname, -1, wbuff, dwNum);
    HWND h = ::FindWindow(NULL, wbuff);	
    DWORD processid;
    GetWindowThreadProcessId(h, &processid);
    m_hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
	if (NULL ==m_hprocess) {
		printf( "打开进程失败\n");
		return;
	}
	printf( "打开进程成功\n");
}

CMemFinder::~CMemFinder() {

}

void CMemFinder::ShowList() {
	if (!m_dwlistnum)
		printf("无数据\n");
	for (int i = 0; i < m_dwlistnum; i++)
		printf("%08x\n", m_dwlist[i]);
}

void CMemFinder::set(DWORD processid) {
	CMemFinder ce(processid);
	this->m_hprocess = ce.m_hprocess;
}

void CMemFinder::set(WCHAR *processname) {
	CMemFinder ce(processname);
	this->m_hprocess = ce.m_hprocess;
}

void CMemFinder::set(char &windowname) {
	CMemFinder ce(windowname);
	this->m_hprocess = ce.m_hprocess;
}

BOOL CMemFinder::ComparePage(DWORD dwBaseAddr, DWORD dwValue) {	//按页读取内存
	BYTE arBytes[4096];
	if (!::ReadProcessMemory(m_hprocess, (LPCVOID)dwBaseAddr, arBytes, 4096, NULL))
		return false;		//不可读，返回失败
	DWORD *pdw;
	for (int i = 0; i < 4 * 1024 - 3; i++) {
		pdw = (DWORD*)&arBytes[i];
		if (pdw[0] == dwValue) {
			if (m_dwlistnum >= MAXSIZE)
				return false;
			m_dwlist[m_dwlistnum++] = dwBaseAddr + i;
		}
	}
	return true;
}

BOOL CMemFinder::FindFirst(DWORD dwValue) {
	const DWORD dwGB = 1<<30;
	const DWORD dwOnePage = 4*1024;
	if (m_hprocess == NULL)
		return false;
	//查看操作系统类型，决定开始地址
	DWORD dwBase;
	OSVERSIONINFO vi = {sizeof(vi)};
	::GetVersionEx(&vi);
	if (vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
		dwBase = 4*1024*1024;	//98系列4MB
	else
		dwBase = 640*1024;	//windowsNT系列64KB
	for(; dwBase < 2*dwGB; dwBase += dwOnePage)
		ComparePage(dwBase, dwValue);
	return true;
}

BOOL CMemFinder::FindNext(DWORD dwValue) {	//再次扫描
	int orgnum = m_dwlistnum;
	m_dwlistnum = 0;
	BOOL flag = false;	//假设失败
	DWORD dwReadValue;
	for (int i = 0; i < orgnum; i++)
		if (::ReadProcessMemory(m_hprocess, (LPVOID)m_dwlist[i], &dwReadValue, sizeof(DWORD),NULL))
			if (dwReadValue == dwValue) {
				m_dwlist[m_dwlistnum++] = m_dwlist[i];
				flag = true;
			}
	return flag;
}

BOOL CMemFinder::modify(DWORD dwAddr, DWORD dwValue) {
	return ::WriteProcessMemory(m_hprocess, (LPVOID)dwAddr, &dwValue, sizeof(DWORD), NULL);
}

int main() {
	WCHAR ws[]= TEXT("test.exe");
	CMemFinder ce(ws);	//从进程名查找
	printf("第一次查找=========\n");
	ce.FindFirst(100);
	ce.ShowList();
	printf("第二次查找=========\n");
	ce.FindNext(101);
	ce.ShowList();
	printf("修改=========\n");
	ce.modify(1638212, 200);
	return 0;
}
