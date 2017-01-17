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
