#include <windows.h>
#include <iostream>
using namespace std;

HWND hwnd = NULL;
HWND hwnd2 = NULL;
HANDLE hthread = NULL;

void refreshchrome() {	//更新chrome网页
	::SetForegroundWindow(hwnd2);
	Sleep(5);
	::SendMessage(hwnd2, WM_KEYDOWN, VK_F5, 0);
	::SendMessage(hwnd2, WM_KEYUP, VK_F5, 0);
}

void checkwindow() {	//找到当前记事本notepad++和浏览器chrome
	hwnd = NULL;
	hwnd = ::FindWindow("Notepad++", NULL);
	hwnd2 = NULL;
	hwnd2=FindWindow("Chrome_WidgetWin_1", NULL);
	hwnd2=GetParent(hwnd2);		//要从浏览器子窗口句柄找到父窗口句柄
}

int main() {
	while (true) {
		checkwindow();
		char textname[250];
		GetWindowText(hwnd, textname, 250);		
		if (hwnd == NULL || hwnd2 == NULL || textname[0] != '*') {	//找不到窗口或未更新则忽略
			Sleep(5);
			continue; 
		} else {	//找到则自动保存notepad++并更新chrome网页
			::SetForegroundWindow(hwnd);
			keybd_event(VK_CONTROL, 0, 0 ,0);
			keybd_event(83, 0, 0 ,0);
			keybd_event(83, 0, KEYEVENTF_KEYUP,0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP,0);
			refreshchrome();
			::SetForegroundWindow(hwnd);
		}
	}
	return 0;
}
