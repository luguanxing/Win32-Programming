#include <windows.h>
#include <iostream>
using namespace std;

HWND hwnd = NULL;
HWND hwnd2 = NULL;
HANDLE hthread = NULL;

void refreshchrome() {
		hwnd = ::FindWindow(NULL, "计算器 - Google Chrome");
		::SetForegroundWindow(hwnd);
		Sleep(5);
		::SendMessage(hwnd, WM_KEYDOWN, VK_F5, 0);
		::SendMessage(hwnd, WM_KEYUP, VK_F5, 0);
}

int main() {
	while (true) {
			hwnd2 = NULL;	//找当前记事本notepad++正在写的CSS代码
			hwnd2 = ::FindWindow(NULL, "*C:\\Users\\Administrator\\Desktop\\calc\\style.css - Notepad++ [Administrator]");
			if (hwnd2 == NULL) {	//找不到忽略
				Sleep(5);
				continue; 
			} else {	//找到后自动保存并更新chrome网页
				::SetForegroundWindow(hwnd2);
				keybd_event(VK_CONTROL, 0, 0 ,0);
				keybd_event(83, 0, 0 ,0);
				keybd_event(83, 0, KEYEVENTF_KEYUP,0);
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP,0);
				refreshchrome();
				::SetForegroundWindow(hwnd2);
			}
	}
	return 0;
}
