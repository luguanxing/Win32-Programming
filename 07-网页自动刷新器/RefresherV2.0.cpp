#include <windows.h>
#include <iostream>
using namespace std;

HWND hwnd = NULL;
HWND hwnd2 = NULL;
HANDLE hthread = NULL;

void refreshchrome() {	//¸üÐÂchromeÍøÒ³
	::SetForegroundWindow(hwnd2);
	Sleep(5);
	::SendMessage(hwnd2, WM_KEYDOWN, VK_F5, 0);
	::SendMessage(hwnd2, WM_KEYUP, VK_F5, 0);
}

void checkwindow() {
	hwnd = NULL;	//ÕÒµ±Ç°¼ÇÊÂ±¾notepad++ÕýÔÚÐ´µÄ´úÂë
	hwnd = ::FindWindow("Notepad++", NULL);
	hwnd2 = NULL;
	hwnd2=FindWindow("Chrome_WidgetWin_1", NULL);
	hwnd2=GetParent(hwnd2);		//Òª´Ó×Ó´°¿Ú¾ä±úÕÒµ½¸¸´°¿Ú¾ä±ú
}

int main() {
	while (true) {
		checkwindow();
		char textname[250];
		GetWindowText(hwnd, textname, 250);		
		if (hwnd == NULL || hwnd2 == NULL || textname[0] != '*') {	//ÕÒ²»µ½´°¿Ú»òÎ´¸üÐÂÔòºöÂÔ
			Sleep(5);
			continue; 
		} else {	//ÕÒµ½ºó×Ô¶¯±£´æ²¢¸üÐÂchromeÍøÒ³
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
