#define _WIN32_WINNT 0x0400
#include <windows.h>  
#include <iostream>
#include <vector> 
#include <algorithm>
using namespace std;

MSG msg;
BYTE value;
HHOOK hook = 0;
HWND hwnd = NULL;
DWORD processid = 0;
HANDLE hthread;
HINSTANCE hInst;
int key;
int check;
bool running;
vector<HWND> windows;
vector<BYTE> values;

void set() {	//设置透明度
	SetWindowLong(hwnd,GWL_EXSTYLE, 0x80000); 
	if(hInst) {
		typedef BOOL (WINAPI *MYFUNC)(HWND, COLORREF, BYTE,DWORD); 
		MYFUNC SetLayeredWindowAttributes = NULL; 
		SetLayeredWindowAttributes=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes"); 
		if(SetLayeredWindowAttributes)
			SetLayeredWindowAttributes(hwnd, 0, value, 2); 
	}
}

int checkwindowchanged(HWND hwnd) {
	if (find(windows.begin(), windows.end(), hwnd) == windows.end()) {		//未调整过的窗口进行登记，保存状态
		windows.push_back(hwnd);
		values.push_back(255);
		return -1;
	} else {	//调整过的窗口取出状态
		return find(windows.begin(), windows.end(), hwnd) - windows.begin(); 
	}
}

void change(bool status) {
	if (running) {
		hwnd = ::GetForegroundWindow();
		check = checkwindowchanged(hwnd);	//检测窗口是否登记过
		if (check == -1) {
			value = 255;
			check = checkwindowchanged(hwnd);
		}
		if (status) {	//调整状态+
			value = values[check];
			value += 20;
			values[check] += 20;
		} else {	//调整状态-
			value = values[check];
			value -= 20;
			values[check] -= 20;
		}
		set();
	}
}

LRESULT CALLBACK hookproc (int code, WPARAM wparam, LPARAM lparam) {
	bool flag = false;
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lparam;
	if (wparam == WM_KEYDOWN)
		flag = true;
	key = p->vkCode;
	if (flag) {
		char windowname[250];
		if (key == 107 && running) {	//检测到小键盘"+"则增加不透明度
			change(true);
			GetWindowText(hwnd, windowname, 250);
			cout << "Opacity of "<< windowname << " changed: " << (int)(BYTE)(values[check] - 20) << " + 20 = "  << (int)value << endl;
		} else if (key == 109 && running) {	//检测到小键盘"-"则减少不透明度
			change(false);
			GetWindowText(hwnd, windowname, 250);
			cout << "Opacity of "<< windowname << " changed: " << (int)(BYTE)(values[check] + 20)<< " - 20 = " << (int)value << endl;
		} else if (key == 118)		//检测到热键F7则助手关闭或开启
			running = !running;
		else ;
	} else ;
	key = 0;
	return CallNextHookEx (hook, code, wparam, lparam);
 }

void messageloop() {	//消息循环
	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	};
}

void sethook() {		//建立钩子检测键盘输入
	processid = GetCurrentThreadId();
	hook = SetWindowsHookEx (WH_KEYBOARD_LL, &hookproc, GetModuleHandle (NULL), 0);
	if (hook == NULL)
		exit(0);
}

int main() {
	running = true;
	hInst = LoadLibrary("User32.DLL"); 
	sethook();
	messageloop();
	return 0;
}  
