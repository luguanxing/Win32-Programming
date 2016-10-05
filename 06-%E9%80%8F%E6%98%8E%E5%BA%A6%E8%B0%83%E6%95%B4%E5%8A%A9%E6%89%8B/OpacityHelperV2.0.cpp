#define _WIN32_WINNT 0x0400
#include <windows.h>  
#include <iostream>
#include <vector> 
#include <algorithm>
#define LWA_ALPHA 2
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

void set() {
	SetWindowLong(hwnd,GWL_EXSTYLE, 0x80000); 
	if(hInst) {
		typedef BOOL (WINAPI *FUNC)(HWND, COLORREF, BYTE, DWORD);
		FUNC SetLayeredWindowAttributes = NULL;
		SetLayeredWindowAttributes = (FUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(SetLayeredWindowAttributes)
			SetLayeredWindowAttributes(hwnd, NULL, value, LWA_ALPHA);
	}
}

void get() {
	typedef BOOL (WINAPI *FUNC)(HWND, COLORREF*, BYTE*, DWORD);
	if(hInst) {
		FUNC GetLayeredWindowAttributes = NULL;
		GetLayeredWindowAttributes = (FUNC)GetProcAddress(hInst, "GetLayeredWindowAttributes");
		if(GetLayeredWindowAttributes)
			GetLayeredWindowAttributes(hwnd, NULL, &value, LWA_ALPHA);
	}
}


void change(bool status) {
	if (running) {
		hwnd = ::GetForegroundWindow();
		get();
		if (status) {
			if (value <= 255-2) {
				value += 2;
				set();
			}
		} else  {
			if (0+2 <= value) {
				value -= 2;
				set();
			}
		}
		
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
		if (key == 187 && running) {
			change(true);
			GetWindowText(hwnd, windowname, 250);
			cout << "Opacity of "<< windowname << " changed: " << (int)(BYTE)(value-2) << " +2 = "  << (int)value << endl;
		} else if (key == 189 && running) {	
			change(false);
			GetWindowText(hwnd, windowname, 250);
			cout << "Opacity of "<< windowname << " changed: " << (int)(BYTE)(value+2) << " -2 = " << (int)value << endl;
		} else if (key == 123)
			running = !running;
		else ;
	} else ;
	key = 0;
	return CallNextHookEx (hook, code, wparam, lparam);
 }

void messageloop() {
	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	};
}

void sethook() {
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